# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Archivos fuente y objetos
SRC = main.cc variable.cc comment.cc comment.cc statement.cc functions.cc code_struc.cc
OBJ = $(SRC:.cc=.o)

# Ejecutable final
TARGET = p04_code_analyzer

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable y borrar los .o después
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm -f $(OBJ)

# Regla para compilar cada .cc a .o
%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

# Limpieza manual
clean:
	rm -f $(OBJ) $(TARGET)