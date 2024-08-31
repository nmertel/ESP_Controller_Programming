#include "LCD.h"

void first_line_adress_counter(char number){
  out_data(0x80 + number);
  LCD_control_write();
}

void next_line() {
  out_data(0x80 + 0x40);
  LCD_control_write();
}

void clear_display() {
  out_data(0x01);
  delay_ms(3);
  LCD_control_write();
}

void return_to_home(){
  out_data(0x02);
  delay_ms(3);
  LCD_control_write();
}

void LCD_control_write() {
  out_control(0x00);
  delay_ms(3);
  out_control(0x01);          // Enable signal
  delay_ms(3);
}

void init_LCD_without_cursor() {
  out_data(0x3F);             // Function Set
  LCD_control_write();
  out_data(0x0C);             // Display ON - OFF Control
  LCD_control_write();
  out_data(0x06);             // Entry mode set
  LCD_control_write();
}

void init_LCD_with_cursor() {
  out_data(0x3F);             // Function Set
  LCD_control_write();
  out_data(0x0F);             // Display ON - OFF Control
  LCD_control_write();
  out_data(0x06);             // Entry mode set
  LCD_control_write();
}