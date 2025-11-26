module microc(output wire [5:0] Opcode, output wire z, input wire clk, reset, s_inc, s_inm, we3, wez, input wire [2:0] Op);
//Microcontrolador sin memoria de datos de un solo ciclo
  // PC
  wire [9:0] PC_actual, nuevo_PC;
  registro #(10) PC(PC_actual, clk, reset, nuevo_PC);
  // SALTO
  wire [9:0] res_sum;
  sum sum1(w1, PC_actual, 10'b0000000001);
  mux2 #(10) mux_pc(nuevo_PC, instruccion [9:0], s_inc);
  // MEMORIA DE PROGRAMA
  wire [15:0] instruccion;
  memprog mem(instruccion, clk, PC_actual);
  // BANCO REGISTROS
  wire [7:0] RD1, RD2, WD3;
  regfile banco_registros(RD1, RD2, clk, we3, instruccion [11:8], instruccion [7:4], instruccion [3:0], WD3);
  // ALU
    // FLAG ZERO
  ffd flag_zero(clk, reset, zALU, wez, z);
  wire [7:0] salida_alu;
  wire zAlu;
  alu alu(salida_alu, zAlu, RD1, RD2, Op);
  // MUX WD3
  mux2 mux_wd3(WD3, salida_alu, instruccion [11:4], s_inm);
  assign Opcode = instruccion [15:10];
endmodule
