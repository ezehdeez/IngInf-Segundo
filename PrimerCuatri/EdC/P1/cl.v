module cl(output wire out, input wire a, b, input wire [1:0] S);

  wire and_result, or_result, xor_result, not_result;
  and and1(and_result, a, b);
  or or1(or_result, a, b);
  xor xor1(xor_result, a, b);
  not not1(not_result, a);
  mux4_1 mux4_1(out, and_result, or_result, xor_result, not_result, S);

endmodule