#include "firmware.h"
#include "LCD.h"

void setup() {
  init_port();
  init_LCD();
  write_string("Welcome to");
  next_line();
  write_string("ECEN academy");
}

void loop() {

}