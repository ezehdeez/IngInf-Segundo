/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file backup-server.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-02
 * @brief 
 */

#include "../includes/functions.h"

std::atomic<bool> quit_requested{false};

// modificacion: si backup-server recibe la señal SIGUSR2, cancelara la copia que se este llevando a cabo en ese momento.
std::expected<void, std::system_error> create_fifo(const std::string& fifo_path) {
  int fd = mkfifo(fifo_path.c_str(), 0666);
  if(fd == -1) {
    if(errno == EEXIST) {
      if(unlink(fifo_path.c_str()) == -1) {
        int error = errno;
        return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al desvincular la FIFO que ya estaba creada"));
      }
      fd = mkfifo(get_fifo_path().c_str(), 0666);
    } else {
      int error = errno;
      return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al crear la FIFO"));
    }
  }
  return {};
}

std::expected<void, std::system_error> write_pid_file(const std::string& pid_file_path) {
  int fd = open(pid_file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if(fd == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al abrir el archivo del PID"));
  }
  std::string pid = std::to_string(getpid()) + '\n';
  ssize_t bytes_written = write(fd, pid.data(), pid.size());
  if(bytes_written == -1) {
    int error = errno;
    close(fd);
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al escribir el PID"));
  }
  close(fd);
  return {};
}

void termination_handler(int signum) {
  const char msg[] = "backup-server: Señal de terminación recibida, cerrando...\n";
  write(STDERR_FILENO, msg, sizeof(msg) - 1); 
  quit_requested = true;
}

std::expected<void, std::system_error> setup_signal_handler() {
  sigset_t signal_set;
  struct sigaction sa;
  if(sigemptyset(&signal_set) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al vaciar el SignalSet"));
  }
  if(sigaddset(&signal_set, SIGUSR1) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al añadir al SignalSet SIGUSR1"));
  }
  if(sigprocmask(SIG_BLOCK, &signal_set, NULL) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al bloquear el SignalSet"));
  }
  sa.sa_handler = termination_handler;
  if (sigemptyset(&sa.sa_mask) == -1) { // No bloqueamos ninguna señal extra en el manejador 
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en sigemptyset para sa_mask"));
  }
  sa.sa_flags = 0;
  if(sigaction(SIGTERM, &sa, NULL) ||
     sigaction(SIGHUP, &sa, NULL) ||
     sigaction(SIGQUIT, &sa, NULL) ||
     sigaction(SIGINT, &sa, NULL)) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en al asignacion de comportamiento (sigaction()) de las señales"));
  }
  return {};
}

std::expected<std::string, std::system_error> read_path_from_fifo(int fifo_fd) {
  std::string path_buffer;
  char c;
  ssize_t bytes_read;
  while(path_buffer.size() < PATH_MAX) {
    bytes_read = read(fifo_fd, &c, 1);
    if(bytes_read == 1) {
      if(c == '\n') {
        break; // FIN del mensaje
      }
      path_buffer += c;
    } else if(bytes_read == 0) {
      break; // EOF
    } else {
      if (errno == EINTR) {
        continue; // Reintentar si fue interrumpido por señal
      }
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR]: Error de lectura en read_path_from_fifo"));
    }
  }
  return path_buffer;
}

std::expected<void, std::system_error> run_server(int fifo_fd, const std::string& backup_dir) {
  sigset_t sigset;
  siginfo_t siginfo;
  if((sigemptyset(&sigset) || sigaddset(&sigset, SIGUSR1)) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en la configuración del sigset de SIGUSR1"));
  }
  while(!quit_requested) {
    int sign = sigwaitinfo(&sigset, &siginfo);
    if(sign == -1) {
      int error = errno;
      if(error == EINTR) {
        continue; // Interrumpido por señal asíncrona, hacemos continue para revisar quit_requested
      }
      return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en la espera de SIGUSR1"));
    }
    if(sign == SIGUSR1) {
      auto path_result = read_path_from_fifo(fifo_fd);
      if (!path_result.has_value()) {
        std::cerr << "[WARNING]: Fallo al leer la ruta desde la FIFO." << std::endl;
        continue;
      }
      std::string src_path = path_result.value();
      if (src_path.empty()) {
        std::cerr << "[WARNING]: La ruta leída está vacía." << std::endl;
        continue;
      }
      std::string final_path = backup_dir + '/' + get_filename(src_path);
      auto copy_result = copy_file(src_path, final_path, 0644);
      if(!copy_result.has_value()) {
        const std::system_error& error = copy_result.error();
        std::cerr << "[WARNING]: Error al hacer backup de " << src_path << ": " << error.what() << std::endl;
      } else {
        std::cout << "[DONE]: Backup completado: " << src_path << " -> " << final_path << std::endl;
      }
    }
  }
  return {};
}

int main(int argc, char* argv[]) {
  
}
