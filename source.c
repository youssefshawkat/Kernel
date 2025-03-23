#include "source.h"
#include <stdint.h>  
#include <sys/io.h>

#define VGA_ADDRESS 0xB8000 

#define BLACK 0
#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE_COLOR 15


unsigned short* terminal_buffer;
unsigned int vga_index;
unsigned int line_count = 1;



void clear_screen(void)
{   
    int index = 0;
    while (index < 80 * 25 * 2) {
        terminal_buffer[index] = ' ';
        index += 2;
    }
}

void print_string(char* str, unsigned char color)
{
    int index = 0;
    while (str[index]) {
        terminal_buffer[vga_index] = (unsigned short)str[index] | (unsigned short)color << 8;
        index++;
        vga_index++;
    }
}

void print_char(char str, unsigned char color)
{
    int index = 0;
    
    terminal_buffer[vga_index] = str | (unsigned short)color << 8;
    index++;
    vga_index++;
    if(vga_index % 80 == 0){
        line_count++;
    }
 
    
}
void backspace_routine(){

    if (vga_index > 80) {  // Ensure cursor is not at the start
        vga_index--;  // Move cursor back
        terminal_buffer[vga_index] = ' ' | (unsigned short)WHITE_COLOR << 8; // Overwrite with space
    }
}
void enter_routine(){
    line_count++;
    vga_index=line_count*80;
}

void move_cursor_left(){
    vga_index--;
}

void move_cursor_right(){
    vga_index++;
}

unsigned char get_scancode() {
    return inb(0x60);
}