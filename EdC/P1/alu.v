module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, 
input wire [2:0] Op);
  wire [3:0] op1, op2, sum_to_mux, ul_to_mux;
  preprocess preprocess(op1, op2, A, B, Op);
  sum4_v2 sum4(sum_to_mux, carry, op1, op2, c_in); 
  ul4 ul4(ul_to_mux, op1, op2, Op[1:0]);
  mux2_4 mux24(R, sum_to_mux, ul_to_mux, Op[2]);
  assign zero = (R == 4'b0000) ? 1 : 0;
  assign sign = R[3];
endmodule