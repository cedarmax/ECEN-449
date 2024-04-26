`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/01/2023 09:23:45 AM
// Design Name: 
// Module Name: 4-bit-counter
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


module fourbitcounter(CLOCK, BTN0, BTN1, LEDS);
    input CLOCK;
    input BTN0;
    input BTN1;
    output [3:0] LEDS;
    
    reg [3:0] count;
clockdivider clockdivider(CLOCK, clockdivided);
    
    always@(posedge clockdivided)
    
    begin
        
        if(BTN0)
            count <= count + 4'b0001;
        else if(BTN1)
            count <= count - 4'b0001;
        else
            count <= count;
    end    
    assign LEDS = count[3:0];   
    
endmodule
