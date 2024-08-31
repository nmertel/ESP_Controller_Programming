#include "firmware.h"
#include "keypad.h"
#include "LCD.h"
#define NULL ((void*)0)

long first_num = 0, second_num = 0;
long calculation_result = 0;
char string_buffer[20];
char* string_result = NULL;                             // the pointer does not point to any valid memory address

void setup() {
  init_port();
  init_LCD_without_cursor();
  first_line_adress_counter(2);
  write_string("Hello World!");
  delay_ms(800);
  clear_display();
}

void loop() {
  init_LCD_with_cursor();
  first_num = get_first_num();                          // operation value stored at the last step of get_first_num()
  second_num = get_second_num();
  calculation_result = result(first_num, second_num);   // operation value included
  string_result = int_to_str(calculation_result, string_buffer);          
  next_line();
  write_string(string_result);                          // use string_result buffer
  while(1){
    if(keypad_select() != 0){
      clear_display();
      break;
    }
  }
}