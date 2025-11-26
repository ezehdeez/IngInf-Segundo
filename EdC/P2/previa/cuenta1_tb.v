`timescale 1 ns / 10 ps

module cuenta1_tb;

reg test_clk, test_start;
reg [2:0] test_Valor;
wire [3:0] test_Cuenta;
wire test_fin;

cuenta1 cuenta1(test_Valor, test_start, test_clk, test_Cuenta, test_fin);

// Señal de reloj
always
begin
  test_clk = 1;
  #20;
  test_clk = 0;
  #20;
end

initial
begin
  $monitor;
  $dumpfile("cuenta1.vcd");
  $dumpvars;
  test_Valor = 3'b101;
  test_start = 1'b1;
  #5;
  test_start = 1'b0;
  $finish;
end
endmodule