#include <xparameters.h>
#include <xgpio.h>
#include <xstatus.h>
#include <xil_printf.h>

#define GPIO_DEVICE_ID_LEDS XPAR_LED_DEVICE_ID
#define GPIO_DEVICE_ID_SWB XPAR_SWB_DEVICE_ID
#define WAIT_VAL 10000000 //for 100mhz

int delay(void) { //clock divider
	volatile int delay_count = 0; 
	while (delay_count < WAIT_VAL) {
		delay_count++;
	}
	return (0);
}

int main() {
	int count = 0;
	int count_masked = 0;
	XGpio leds; 
	XGpio swb; //switches & buttons
	int statusOutput;

	statusOutput = XGpio_Initialize(&leds, GPIO_DEVICE_ID_LEDS);
	XGpio_SetDataDirection(&leds, 1, 0); 
	if (statuso != XST_SUCCESS) {
		xil_printf("Initialization failed for LEDs");
	}

	XGpio_Initialize(&swb, GPIO_DEVICE_ID_SWB);
	XGpio_SetDataDirection(&swb, 1, 1);
	int switchValue = 0;
//initialize variables
	bool b0 = false;
	bool b1 = false;
	bool b2 = false;
	bool b3 = false;

	while (true) { 
		bool button0 = (0x01 & XGpio_DiscreteRead(&swb, 1) == 0x01) 
			&& !((XGpio_DiscreteRead(&swb, 1) & 0x04) == 0x04) //NOT button2
			&& !((XGpio_DiscreteRead(&swb, 1) & 0x08) == 0x08); //NOT button3

		bool button1 = ((XGpio_DiscreteRead(&swb, 1) & 0x02) == 0x02) 
			&& !((XGpio_DiscreteRead(&swb, 1) & 0x04) == 0x04) //NOT button2
			&& !((XGpio_DiscreteRead(&swb, 1) & 0x08) == 0x08); //NOT button3

		bool button2 = ((XGpio_DiscreteRead(&swb, 1) & 0x04) == 0x04); //button 2 

		bool button3 = ((XGpio_DiscreteRead(&swb, 1) & 0x08) == 0x08); //button 3 
		if (!button2 && !button3) XGpio_DiscreteWrite(&leds, 1, 0); 

		if (button0) { //bitwise AND with 1 to find value of the last bit
			if (!b0) { xil_printf("Button[0] has been pressed!\n"); b0 = true; }
			if (b1) { b1 = false; xil_printf("Button[1] has been released!\n"); }
			if (b2) { b2 = false; xil_printf("Button[2] has been released!\n"); }
			if (b3) { b3 = false; xil_printf("Button[3] has been released!\n"); }
			count++;
			count_masked = count & 0xF;
			xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
			delay();
		}
		else if (button1) {
			count--;
			
			//check
			if (!b1) { b1 = true; xil_printf("Button[1] has been pressed!\n"); }
			if (b0) { b0 = false; xil_printf("Button[0] has been released!\n"); }
			if (b2) { b2 = false; xil_printf("Button[2] has been released!\n");  }
			if (b3) { b3 = false; xil_printf("Button[3] has been released!\n");  }

			count_masked = count & 0xF;
			xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
			delay();
		}

		else if (button2) { /*button 2 pressed (show switches)*/
			if (b1) { b1 = false; xil_printf("Button[1] has been released!\n"); }
			if (b0) { b0 = false; xil_printf("Button[0] has been released!\n"); }
			if (!b2) { b2 = true; xil_printf("Button[2] has been pressed!\n"); }
			if (b3) { b3 = false; xil_printf("Button[3] has been released!\n");}

			if ((XGpio_DiscreteRead(&swb, 1) & 0xF0) != switchValue) {
				switchValue = XGpio_DiscreteRead(&swb, 1) & 0xF0;
				xil_printf("You moved a switch. Value: %d\n", switchValue >> 4);
			}
			XGpio_DiscreteWrite(&leds, 1, switchValue >> 4);
			//display leds with switch values

			if ((XGpio_DiscreteRead(&swb, 1) & 0x01) == 0x01) { //button2 is pressed AND button0 is pressed
				if (!b0) { b0 = true; xil_printf("Button[0] has been pressed!\n"); }
				count++;
				count_masked = count & 0xF;
				xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
				delay();
			}
			else if ((XGpio_DiscreteRead(&swb, 1) & 0x02) == 0x02) { //button2 is pressed AND button1 is pressed
				if (!b1) { b2 = true; xil_printf("Button[1] has been pressed!\n"); }
				count--;
				count_masked = count & 0xF;
				xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
				delay();
			}

		}
		else if (button3) {
			if (b1) { b1 = false; xil_printf("Button[1] has been released!\n"); }
			if (b0) { b0 = false; xil_printf("Button[0] has been released!\n"); }
			if (b2) { b2 = false; xil_printf("Button[2] has been released!\n");}
			if (!b3) { b3 = true; xil_printf("Button[3] has been pressed!\n"); }

			if ((XGpio_DiscreteRead(&swb, 1) & 0x01) == 0x01) {
				count++;
				count_masked = count & 0xF;
				XGpio_DiscreteWrite(&leds, 1, count_masked);
				xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
				delay();
			}
			else if ((XGpio_DiscreteRead(&swb, 1) & 0x02) == 0x02) { //btn3 and btn1
				if (!b1) { b1 = true; xil_printf("Button[1] has been pressed!\n"); }
				count--;
				count_masked = count & 0xF;
				XGpio_DiscreteWrite(&leds, 1, count_masked);
				xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
				delay();
			}
			else { //btn3
				XGpio_DiscreteWrite(&leds, 1, count_masked);
			}

		}
	}
}
