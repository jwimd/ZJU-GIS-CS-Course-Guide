module dffre (
    d, en, r, clk, q
);
    parameter n = 1;
    input en,r,clk;
    input [n-1:0] d;
    output [n-1:0] q;
    reg [n-1:0] q;
    always @(posedge clk) begin
        if(r) q = {n{1'b0}};
        else if(en) q = d;
            else q = q;
    end
endmodule