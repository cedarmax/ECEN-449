`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2023 09:34:54 AM
// Design Name: 
// Module Name: clockdivider
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////   
module clockdivider(clock_in,clock_out, RESET
    );
input clock_in, RESET; 
output reg clock_out; 
reg[31:0] counter=32'd0;

always @(posedge clock_in)
begin
 if(counter==(25000000-1))begin
  counter <= 32'd0;
  clock_out <= 1;
 end
 else begin
   counter <= counter+1;
   clock_out = 0;
  end
end 
 
endmodule
