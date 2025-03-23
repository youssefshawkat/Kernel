#include "keyboard.h"
#include "source.h"
#include <sys/io.h>



void keyboard_driver(unsigned char scancode) {
    static unsigned char last_scancode = 0;  
    static int shift_pressed = 0;  


    // Ignore break codes (release events)
    if (scancode & 0x80) {
        unsigned char make_code = scancode & 0x7F;

        // Check if Shift key is released
        if (make_code == 0x2A || make_code == 0x36) {
            shift_pressed = 0;
        }

        last_scancode = 0;
        return;
    }

    // Ignore repeated key presses
    if (scancode == last_scancode) {
        return;
    }
    last_scancode = scancode;

    // Detect Shift key press
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }

    unsigned char character = '?';

    switch (scancode) {
        // Number row (0-9) and Shift symbols
        case 0x02: character = shift_pressed ? '!' : '1'; break;
        case 0x03: character = shift_pressed ? '@' : '2'; break;
        case 0x04: character = shift_pressed ? '#' : '3'; break;
        case 0x05: character = shift_pressed ? '$' : '4'; break;
        case 0x06: character = shift_pressed ? '%' : '5'; break;
        case 0x07: character = shift_pressed ? '^' : '6'; break;
        case 0x08: character = shift_pressed ? '&' : '7'; break;
        case 0x09: character = shift_pressed ? '*' : '8'; break;
        case 0x0A: character = shift_pressed ? '(' : '9'; break;
        case 0x0B: character = shift_pressed ? ')' : '0'; break;

        // Alphabet keys
        case 0x1E: character = shift_pressed ? 'A' : 'a'; break;
        case 0x30: character = shift_pressed ? 'B' : 'b'; break;
        case 0x2E: character = shift_pressed ? 'C' : 'c'; break;
        case 0x20: character = shift_pressed ? 'D' : 'd'; break;
        case 0x12: character = shift_pressed ? 'E' : 'e'; break;
        case 0x21: character = shift_pressed ? 'F' : 'f'; break;
        case 0x22: character = shift_pressed ? 'G' : 'g'; break;
        case 0x23: character = shift_pressed ? 'H' : 'h'; break;
        case 0x17: character = shift_pressed ? 'I' : 'i'; break;
        case 0x24: character = shift_pressed ? 'J' : 'j'; break;
        case 0x25: character = shift_pressed ? 'K' : 'k'; break;
        case 0x26: character = shift_pressed ? 'L' : 'l'; break;
        case 0x32: character = shift_pressed ? 'M' : 'm'; break;
        case 0x31: character = shift_pressed ? 'N' : 'n'; break;
        case 0x18: character = shift_pressed ? 'O' : 'o'; break;
        case 0x19: character = shift_pressed ? 'P' : 'p'; break;
        case 0x10: character = shift_pressed ? 'Q' : 'q'; break;
        case 0x13: character = shift_pressed ? 'R' : 'r'; break;
        case 0x1F: character = shift_pressed ? 'S' : 's'; break;
        case 0x14: character = shift_pressed ? 'T' : 't'; break;
        case 0x16: character = shift_pressed ? 'U' : 'u'; break;
        case 0x2F: character = shift_pressed ? 'V' : 'v'; break;
        case 0x11: character = shift_pressed ? 'W' : 'w'; break;
        case 0x2D: character = shift_pressed ? 'X' : 'x'; break;
        case 0x15: character = shift_pressed ? 'Y' : 'y'; break;
        case 0x2C: character = shift_pressed ? 'Z' : 'z'; break;

        // Space
        case 0x39: character = ' '; break;

        // Punctuation keys and their Shift symbols
        case 0x0C: character = shift_pressed ? '_' : '-'; break;
        case 0x0D: character = shift_pressed ? '+' : '='; break;
        case 0x1A: character = shift_pressed ? '{' : '['; break;
        case 0x1B: character = shift_pressed ? '}' : ']'; break;
        case 0x2B: character = shift_pressed ? '|' : '\\'; break;
        case 0x27: character = shift_pressed ? ':' : ';'; break;
        case 0x28: character = shift_pressed ? '"' : '\''; break;
        case 0x29: character = '`'; break;  // No Shift mapping for `
        case 0x33: character = shift_pressed ? '<' : ','; break;
        case 0x34: character = shift_pressed ? '>' : '.'; break;
        case 0x35: character = shift_pressed ? '?' : '/'; break;

        // Special keys
        case 0x0E:  // Backspace
            backspace_routine();
            return;
        case 0x1C:  // Enter
            enter_routine();
            return;
        case 0x0F:  // Tab
            
            return;
        case 0x4B:
                
                move_cursor_left();
                return;
        case 0x4D:
                move_cursor_right();
                return;   
    }

    if (character != '?') {
        print_char(character, YELLOW);
    }


}