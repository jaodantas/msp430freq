comp:
	msp430-gcc -Os -mmcu=msp430g2553 freq.c -o freq.elf -std=c99
debug:
	sudo mspdebug rf2500