#include <kernel.h>

#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

// Memory location of VGA Buffer, used to display text
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;


void term_init(void){
   for(size_t col = 0; col <= VGA_COLS ;col++){
       for(size_t row = 0; row <= VGA_ROWS ;row++){
          const size_t index = (VGA_COLS * row) + col;
          vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
       }
   }
}

void _print_char(char c){
  switch(c){
    case '\n':
      term_col = 0;
      term_row++;
      break;
    case '\t':
      term_col += 8; // Normally tab is 8 char long
      term_row = term_row;
      break;
    
    default:
      const size_t index = (VGA_COLS * term_row) + term_col;
      vga_buffer[index] = ((uint16_t)term_color << 8) | c;
      term_col++;
      break;
  }
  // Handle case when col >= 80 or when row >= 25;
  if(term_col >= VGA_COLS){
    term_col = 0;
    term_row++;
  }
  if(term_row >= VGA_ROWS){
    term_col = 0;
    term_row = 0;
  }
}

void _print(const char* text){
  for(size_t i = 0; text[i] != '\0'; i++){
    _print_char(text[i]);
  }
}

void kernel_start(void){
  term_init();
  _print("Kernel has started! \n");
  _print("Hello, World!");
  
}
