`timescale 1 ns / 10 ps 
module microc_tb;

// declaración de variables
//...
reg clk;
reg reset;
reg s_inc;
reg s_inm;
reg we3;
reg wez;
reg [2:0] Op;
wire [5:0] Opcode;
wire z;

// instanciación del camino de datos
microc microc(Opcode, z, clk, reset, s_inc, s_inm, we3, wez, Op);
//...

// generación de reloj clk
//...
always
begin
  clk = 1'b1
  #5
  clk = 1'b0
  #5
end

// Reseteo y configuración de salidas del testbench
initial
begin
  $dumpfile("microc_tb.vcd");
  $dumpvars;
  _inc = 0;
  s_inm = 0;
  we3 = 0;
  wez = 0;
  Op = 3'b000;
  reset = 1;
  #10;
  reset = 0;
end

// Bloque simulación señales control por CICLO
initial
begin
// Esperamos a que termine el reset
    #10; 
    //CICLO 0
    #5; 
    s_inc = 0;      
    s_inm = 0;      
    we3 = 0;       
    wez = 0;        
    Op = 3'b000;    
    #5;  
    // CICLOS 1-4
    repeat(4)
    begin
    #5;
    s_inc = 1;    
    s_inm = 1;      
    we3 = 1;        
    wez = 0;        
    Op = 3'b000;  
    #5;
  end
  // CICLO 5
  #5;
  s_inc = 1;     
  s_inm = 1;    
  we3 = 1;      
  wez = 0;      
  Op = 3'b000;   
  #5;
  // CICLO 6
  #5;
  s_inc = 1;
  s_inm = 1;     
  we3 = 1;        
  wez = 0;
  Op = 3'b000;
  #5;
  // CICLO 7
  #5;
  s_inc = 1;
  s_inm = 1;
  we3 = 1;
  wez = 0;
  Op = 3'b000;
  #5;
  // CICLO 8
  #5;
  s_inc = 1;
  s_inm = 1;
  we3 = 1;
  wez = 0;
  Op = 3'b000;
  #5;
  // CICLO 9
  #5;
  s_inc = 1;    
  s_inm = 0;      
  we3 = 1;      
  wez = 1;        
  Op = 3'b010;   
  #5;
  // CICLO 10
  #5;
  s_inc = 1;
  s_inm = 0;    
  we3 = 1;        
  wez = 1;      
  Op = 3'b011;    
  #5;
  // CICLO 11
  #5;
  s_inc = (z == 0) ? 0 : 1;  
  s_inm = 0;
  we3 = 0;
  wez = 0;
  Op = 3'b000;
  #5;
  // CICLO 12
  #5;
  s_inc = 1;
  s_inm = 0;
  we3 = 1;
  wez = 1;
  Op = 3'b010;    
  #5;  
  // CICLO 13
  #5;
  s_inc = 1;
  s_inm = 0;
  we3 = 1;
  wez = 1;
  Op = 3'b011;    
  #5;
  // CICLO 14
  #5;
  s_inc = (z == 0) ? 0 : 1;  
  s_inm = 0;
  we3 = 0;
  wez = 0;
  Op = 3'b000;
  #5;
  // Terminamos la simulación
  $finish;
end

endmodule
