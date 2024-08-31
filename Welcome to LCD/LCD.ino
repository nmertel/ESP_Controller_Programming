#include "LCD.h"

void next_line() {
  out_data(0x80 + 0x40);
  out_control(0x00);
  delay_ms(3);
  out_control(0x01);          // Enable signal
  delay_ms(3);
}

void clear_display() {
  out_data(0x01);
  delay_ms(3);
  out_control(0x00);
  delay_ms(3);
  out_control(0x01);          // Enable signal
  delay_ms(3);
}

void LCD_control_write() {
  out_control(0x01);          // Enable signal
  delay_ms(3);
  out_control(0x00);
  delay_ms(3);
}

void init_LCD() {
  out_data(0x3F);             // Function Set
  LCD_control_write();
  out_data(0x0C);             // Display ON - OFF Control
  LCD_control_write();
  out_data(0x06);             // Entry mode set
  LCD_control_write();
}