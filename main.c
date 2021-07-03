#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <gb/console.h>
#include <gb/drawing.h>

char hexbuf[3];
inline char numtohex(unsigned char value) {
    // printf("%d\n", value);
    value = value & 0xFF;
    if(value > 0xF) { 
        return 'X';
    }
    if(value < 10) {
        return '0' + value;
    }
    return 'A' + (value-10);
}

inline void hex(char value) {

    hexbuf[0] = numtohex(value & 0xF0) >> 4;
    hexbuf[1] = numtohex(value & 0x0f);;
    hexbuf[2] = 0;
}


void main(void)
{
    disable_interrupts();
    int addr = 0;
    unsigned char *ptr = (unsigned char*)addr;
    unsigned char buf[256];
    memcpy(buf, ptr, 256);

    // re-map bootrom
    __asm
	ld A,#01
	LD (#0xFF50),A
    __endasm;

    if(buf[0] == 0xFF) {
        puts("Failed to dump");
        puts("bootrom :((");
        while(1) {
            // wait_vbl_done();
        }
    }

    puts("Success!\n");
    while(1) {
        puts("Bootrom 1/2:");
        // while(1){}
        for(int i=0; i < 16; i++) {
            for(int j=0; j < 8; j++) {
                if(j == 4)
                    putchar(' ');
                unsigned char value = buf[(i * 8) + j];
                putchar(numtohex((value & 0xF0) >> 4));
                putchar(numtohex(value & 0x0F));
            }
            puts("");
        }
        delay(3000);
        // cls();
        puts("Bootrom 2/2:");
        // while(1){}
        for(int i=16; i < 32; i++) {
            for(int j=0; j < 8; j++) {
                if(j == 4)
                    putchar(' ');
                unsigned char value = buf[(i * 8) + j];
                putchar(numtohex((value & 0xF0) >> 4));
                putchar(numtohex(value & 0x0F));
            }
            puts("");
        }
        delay(3000);

    }

    while(1) {
        // wait_vbl_done();
    }
}
