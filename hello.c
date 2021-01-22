// hello world or "HI" program
// prints HI to serial pin P3.1 (physical pin 6) at 2400 baud once a second
// toggles led on P3.3 each time

#include "my_stc_.h"	// converted header file

/* 
Windows bat file for compiling. Put in same folder as this source file and my_stc_.h

sdcc -mmcs51  --iram-size 128 --xram-size 0 --code-size 4088 --verbose hello.c -o hello_bin.ihx
packihx hello_bin.ihx > hello.hex
pause

 */
 
#define led  P3_3
#define txLine  P3_1

#define TX_HIGH txLine = 1
#define TX_LOW txLine = 0


void setPortMode(unsigned char port,unsigned char bitNum, unsigned char mode)	// sets mode of an IO pin / only works on ports 0, 3 for now
{
	unsigned char tmp1 = 0;
	unsigned char tmp2 = 0;
	unsigned char tmp3 = 0;
	unsigned char tmp4 = 0;
	
		if(mode & 0x01){
			tmp1 = 1 << bitNum;
		}
		if(mode & 0x02){
			tmp2 = 1 << bitNum;
		}

	switch(port){
		case 1 :
			tmp3 = (P1M0 & ~tmp1) | tmp1;
			tmp4 = (P1M1 & ~tmp1) | tmp2;

			P1M0 = tmp3;
			P1M1 = tmp4;
			break;
		case 3 :
			tmp3 = (P3M0 & ~tmp1) | tmp1;
			tmp4 = (P3M1 & ~tmp1) | tmp2;

			P3M0 = tmp3;
			P3M1 = tmp4;
			break;
	}	
	
}



void Delay2400(){	// 1 bit time for 2400 baud at 12 MHz
	__asm
		push 0x30
		push 0x31
		mov 0x30,#4
		mov 0x31,#220
NEXT:
		djnz 0x31,NEXT
		djnz 0x30,NEXT
		pop 0x31
		pop 0x30
	__endasm;
}


void sendChar(unsigned char c)	//send an ASCII character
{
	unsigned char mask = 1;	//bit mask
	unsigned char i;
         
	Delay2400();// wait 2 Stop bits before sending the char to give a stop bit if routine is called again before a stop bit time period has passed
	Delay2400();

	TX_LOW;              // low the line for start bit

	Delay2400();	//wait 1 bit time for start bit

	for (i=0; i<8 ;i++){
		if (c & mask){
			TX_HIGH;
		}
		else{
			TX_LOW;
		}
		mask <<= 1;
		Delay2400();
	}
	TX_HIGH;            //Return TXDATA pin to "1".
}


void sendCRLF(void)
{
	sendChar(13);
	sendChar(10);
}


void main()
{

	unsigned int delayCtr;
	
	
	// commented out so pins are default mode 0
	//setPortMode(3,3,1);		//this should make bit 3 on P3 a push pull output
	//setPortMode(3,4,1);		//this should make bit 4 on P3 a push pull output
	//setPortMode(3,5,1);		//this should make bit 5 on P3 a push pull output
	
	led = 0;

	sendChar('H');
	sendChar('I');
	sendChar(13);
	sendChar(10);
	
    while(1)
    {
		for(delayCtr = 2400;delayCtr > 0;delayCtr--)	//wait 1 second
		{
			Delay2400();
		}
		led = !led;	//toggle led
		sendChar('H');
		sendChar('I');
		sendChar(13);
		sendChar(10);
    }		
}	  
