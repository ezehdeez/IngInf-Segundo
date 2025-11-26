module preprocess(output wire [3:0] AMod, output wire [3:0] BMod, input wire [3:0] A, input wire [3:0] B, input wire [2:0] Op);
  wire [3:0] mux1_to_mux2, mux3_to_compl1;
  wire add1, op1_A, op2_B, cpl;
  assign add1 = 1'b1; 
  assign op1_A = Op[2] | (~Op[1] & ~Op[0]);
  assign op2_B = Op[2] | (~Op[1] & ~Op[0]) | (Op[1] & Op[0]);
  assign cpl = ~Op[2] & Op[1];
  mux2_4 mux24_1(mux1_to_mux2, 4'b0000, 4'b0001, add1);
  mux2_4 mux24_2(AMod, mux1_to_mux2, A, op1_A);
  mux2_4 mux24_3(mux3_to_compl1, A, B, op2_B);
  compl1 compl1_1(BMod, mux3_to_compl1, cpl);
endmodule