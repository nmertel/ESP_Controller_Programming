#include "firmware.h"

void init_port() {
  volatile char *dir_f = (char*)0x30;
  volatile char *dir_k = (char*)0x107;
  *dir_f = 0xFF;                   // OUTPUT
  *dir_k = 0x03;                   // OUTPUT
}

void out_data(char out_data) {
  volatile char *out_f = (char*)0x31;
  *out_f = out_data;
}

void out_control(char out_data) {
  volatile char *out_k = (char*)0x108;
  *out_k = out_data;
}

void delay_ms(long time_ms) {
  volatile long temp_x;
  for (temp_x = 0; temp_x < time_ms * 428; temp_x++);
}

void write_data(char wr_data) {
  out_data(wr_data);
  out_control(0x02);          // Register Select
  delay_ms(3);
  out_control(0x01);          // Enable signal
  delay_ms(3);
}

void write_string(char *ptr) {
  while (*ptr != 0) {
    write_data(*ptr);
    ptr++;
  }
}