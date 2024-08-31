#include "firmware.h"

void init_port() {
  volatile char *dir_f = (char*)0x30;
  volatile char *dir_k = (char*)0x107;
  volatile char *dir_a = (char*)0x21;
  *dir_f = 0xFF;                   // OUTPUT
  *dir_k = 0x03 + 0x08;            // OUTPUT
  *dir_a = 0x00;                   // INPUT
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
  for (temp_x = 0; temp_x < time_ms * 428; temp_x++);   // Need to optimize
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

char* int_to_str(long number, char* result) {
  char i = 0;
  char j;
  char len = 0;
  char temp_x[20];
  char is_negative = 0;

  // special case for negative value
  if (number < 0) {
    number *= -1;
    is_negative = 1;
  }

  // special case for zero 
  if(number == 0){
    result[i++] = '0';
    result[i] = '\0';
    return result;
  }

  while (number != 0) {
    result[i++] = (number % 10) + '0';      // integer to symbol conversion
    number /= 10;
    len++;                                  // length of the number
  }

  if (is_negative == 1) {
    i += 1;         // if the result is negative, assign the reversed array starting from index 1, since index 0 will be '-'
  } else {
    i = 0;
  }
  j = len - 1;

  // Reverse the string
  while (j >= 0) {
    temp_x[i++] = result[j--];
  }

  // Copy the reversed string back to the result
  // Add a minus sign beginning of the array if the result is negative
  for (i = 0; i < len; i++) {
    if (is_negative == 1) {
      result[i++] = '-';
      len++;
      is_negative = 0;
    }
    result[i] = temp_x[i];
  }

  result[i] = '\0';  // Ensure result is null-terminated

  return result;
}