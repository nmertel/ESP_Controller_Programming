#include "keypad.h"

char operation = 0;     // global variable;

char keypad_in() {
  volatile char *in_a = (char*)0x20;
  char temp_x = 0;
  if ((*in_a & 0x01) == 0x01) {
    temp_x = 1;
  } else if ((*in_a & 0x02) == 0x02) {
    temp_x = 2;
  } else if ((*in_a & 0x04) == 0x04) {
    temp_x = 4;
  } else if ((*in_a & 0x08) == 0x08) {
    temp_x = 8;
  }
  return temp_x;
}

char keypad_select() {
  char column;
  char raw = 0;
  char result = 0;

  while (raw == 0) {
    column = keypad_column_pins(0x01);
    out_control(column);
    raw = keypad_in();
    if (raw == 1) {
      result = '1';
      break;

    } else if (raw == 2) {
      result = '4';
      break;

    } else if (raw == 4) {
      result = '7';
      break;

    } else if (raw == 8) {
      result = 0;      
      break;
    }

    column = keypad_column_pins(0x02);
    out_control(column);
    raw = keypad_in();
    if (raw == 1) {
      result = '2';
      break;

    } else if (raw == 2) {
      result = '5';
      break;

    } else if (raw == 4) {
      result = '8';
      break;

    } else if (raw == 8) {
      result = '0';
      break;
    }

    column = keypad_column_pins(0x04);
    out_control(column);
    raw = keypad_in();
    if (raw == 1) {
      result = '3';
      break;

    } else if (raw == 2) {
      result = '6';
      break;

    } else if (raw == 4) {
      result = '9';
      break;

    } else if (raw == 8) {
      result = '=';
      break;
    }

    column = keypad_column_pins(0x08);
    out_control(column);
    raw = keypad_in();
    if (raw == 1) {
      result = '+';
      break;

    } else if (raw == 2) {
      result = '-';
      break;

    } else if (raw == 4) {
      result = '*';
      break;

    } else if (raw == 8) {
      result = '/';
      break;
    }
  }
  delay_ms(100);
  return result;
}

long get_first_num() {
  char first_symbol = 0;
  long first_num = 0;
  while (1) {
    first_symbol = keypad_select();
    if (first_symbol == '+' || first_symbol == '-' || first_symbol == '*' || first_symbol == '/' ) {
      write_data(first_symbol);
      operation = first_symbol;         // set operation value
      delay_ms(100);
      break;
    }
    first_num *= 10;                   // Get next digit
    first_num += (first_symbol - 48);  // ASCII symbol to integer
    write_data(first_symbol);
    delay_ms(100);
  }
  return first_num;
}

long get_second_num() {
  char second_symbol = 0;
  long second_num = 0;
  while (1) {
    second_symbol = keypad_select();
    if (second_symbol == '=' ) {
      delay_ms(100);
      break;
    }
    second_num *= 10;                     // Get next digit
    second_num += (second_symbol - 48);   // ASCII symbol to integer
    write_data(second_symbol);
    delay_ms(100);
  }
  return second_num;
}

long result(long first_num, long second_num) {
  long temp_x = 0;
    if (operation == '+') {
      temp_x = first_num + second_num;
    } else if (operation == '-') {
      temp_x = first_num - second_num;
    } else if (operation == '*') {
      temp_x = first_num * second_num;
    } else if (operation == '/') {
      temp_x = first_num / second_num;
    }
  return temp_x;
}

char keypad_column_pins(char out_data) {
  return out_data << 2;
}