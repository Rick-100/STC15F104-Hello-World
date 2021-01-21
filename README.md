# STC15F104-Hello-World with SDCC compiler
Some basic programs for getting started with the STC15F104 and SDCC compiler

hello.c blinks an led on P3.3 every second and sends "HI" out P3.1 at 2400 baud with a 12 MHz clock selected.

hello_num_1.c is built on hello.c and adds functions to print numbers out P3.1 in various radix. It also reads the P3 port and prints it out in binary.

compile hello.c from Windows command line with:

sdcc -mmcs51  --iram-size 128 --xram-size 0 --code-size 4088 --verbose hello.c -o hello_bin.ihx

and then convert ihx file to hex with:

packihx hello_bin.ihx > hello.hex

compile hello_num_1.c with:


sdcc -mmcs51  --iram-size 128 --xram-size 0 --code-size 4088 --verbose hello_num_1.c -o hello_num_1.ihx

and then convert ihx file to hex with:

packihx hello_num_1.ihx > hello_num_1.hex

I just place the my_stc_.h file in the same folder as the Hello.c to keep things simple.

The serial port is bit banged with a delay loop. The delay loop is created with the STC-ISP program. The STC-ISP program can create delay loops in C if you use the Keil compiler but the timing is wrong if the code is compiled with SDCC. The STC-ISP program can generate delay loops in assembly language also. So the delay loop is in the form of inline assembly.

The programs also contain a function to set the IO pins to different modes. Each pin has 4 modes. The default mode 0 is the 8051 compatable quasi bi-directional mode. This mode sinks more current than it can source. Mode 1 is push pull mode. The data sheet has all the ugly details.

More to come.
