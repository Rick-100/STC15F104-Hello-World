rem set PATH="C:\SDCC_compiler\bin";%PATH%

sdcc -mmcs51  --iram-size 128 --xram-size 0 --code-size 4088 --verbose hello.c -o hello_bin.ihx
packihx hello_bin.ihx > hello.hex

pause
