#include "source.h"
#include "keyboard.h"




void main(void)
{

    terminal_buffer = (unsigned short*)VGA_ADDRESS;
    vga_index = 0;

    clear_screen();
    
    print_string("----------------------------- WELCOME TO METRO OS ------------------------------", YELLOW);

    vga_index = 80;

 
  
    while (1) {

            keyboard_driver(get_scancode());
    }

    return;
}





