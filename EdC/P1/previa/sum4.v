//Sumador de 4 bits 
module sum4(output wire[3:0] S, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);
	// Contenido
	wire c0, c1, c2;

	fa_v1 fa0(S[0], c0, A[0], B[0], c_in);
	fa_v1 fa1(S[1], c1, A[1], B[1], c0);
	fa_v1 fa2(S[2], c2, A[2], B[2], c1);
	fa_v1 fa3(S[3], c_out, A[3], B[3], c2);
	
endmodule

