`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2023 10:45:34 AM
// Design Name: 
// Module Name: jackpot
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


module jackpot(output [3:0] LEDS, input CLOCK, 
    input RESET, input [3:0] SWITCHES 
    );
    
    clockdivider div(CLOCK, slowClock, RESET);
    
    reg [3:0] LEDS_REG;
    
    always@(posedge slowClock) begin
		
        if (RESET) begin 
            LEDS_REG <= 4'b1000;
        end
        
        else begin
		
            if (LEDS_REG == 4'b1000 & ~SWITCHES[3]) begin
                LEDS_REG <= 4'b0100;
            end
            else if (LEDS_REG == 4'b0100 & ~SWITCHES[2]) begin
                LEDS_REG <= 4'b0010;
            end
            else if (LEDS_REG == 4'b0010 & ~SWITCHES[1]) begin
                LEDS_REG <= 4'b0001;
            end
            else if (LEDS_REG == 4'b0001 & ~SWITCHES[0]) begin
                LEDS_REG <= 4'b1000;
            end
            else begin 
                LEDS_REG <= 4'b1111;
            end 
        end
    end
endmodule
