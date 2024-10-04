// Modified from code found in https://wokwi.com/projects/351764383409373773
// Modified to be digital, not analog, and 
// add pins for a TB6612FNG https://www.pololu.com/product/713

// See also L298N: https://wokwi.com/projects/410302035690579969
// and L298N: https://wokwi.com/projects/386822856593519617
// This progect TB6612FNG https://wokwi.com/projects/410323062531374081

/*
{
  "name": "TB6612FNG",
  "author": "David Forrest",
  "pins": [
    "GND",
    "VCC",
    "AO1",     
    "AO2",
    "BO2",
    "BO1",
    "VMOT",
    "GND",
    "GND",
    "PWMB",
    "BIN2",
    "BIN1",
    "nSTBY",
    "AIN1",
    "AIN2",
    "PWMA"
  ],
  "controls": [
    {
      "id": "Vs",
      "label": "External Voltage (V)",
      "type": "range",
      "min": 0,
      "max": 13.5,
      "step": 0.1
    }
  ]
}
*/

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  pin_t pin_AO1;
  pin_t pin_AO2;
  pin_t pin_BO1;
  pin_t pin_BO2;
  pin_t pin_AIN1;
  pin_t pin_AIN2;
  pin_t pin_BIN1;
  pin_t pin_BIN2;
  pin_t pin_nSTBY;
  pin_t pin_PWMA;
  pin_t pin_PWMB;
  uint32_t Vs_attr; 
} chip_state_t;



static void chip_pin_change(void *user_data, pin_t pin, uint32_t value);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  chip->pin_nSTBY = pin_init("nSTBY",INPUT_PULLDOWN);
  chip->pin_PWMA = pin_init("PWMA",INPUT);
  chip->pin_PWMB = pin_init("PWMB",INPUT);
  chip->pin_AIN1 = pin_init("AIN1",INPUT);
  chip->pin_AIN2 = pin_init("AIN2",INPUT);
  chip->pin_BIN1 = pin_init("BIN1",INPUT);
  chip->pin_BIN2 = pin_init("BIN2",INPUT);
  chip->pin_AO1 = pin_init("AO1",OUTPUT);
  chip->pin_AO2 = pin_init("AO2",OUTPUT);
  chip->pin_BO1 = pin_init("BO1",OUTPUT);
  chip->pin_BO2 = pin_init("BO2",OUTPUT);
  chip->Vs_attr = attr_init_float("Vs", 12.0);
  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };
  pin_watch(chip->pin_PWMA, &watch_config);
  pin_watch(chip->pin_PWMB, &watch_config);
  pin_watch(chip->pin_AIN1, &watch_config);
  pin_watch(chip->pin_AIN2, &watch_config);
  pin_watch(chip->pin_BIN1, &watch_config);
  pin_watch(chip->pin_BIN2, &watch_config);
  pin_watch(chip->pin_nSTBY, &watch_config);
}

void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  int PWMA = pin_read(chip->pin_PWMA);
  int PWMB = pin_read(chip->pin_PWMB);
  int AIN1 = pin_read(chip->pin_AIN1);
  int AIN2 = pin_read(chip->pin_AIN2);
  int BIN1 = pin_read(chip->pin_BIN1);
  int BIN2 = pin_read(chip->pin_BIN2);
  int nSTBY = pin_read(chip->pin_nSTBY);
  float Vs = attr_read_float(chip->Vs_attr);
  
  // motor A control
  if (AIN1 && nSTBY) 
   // pin_dac_write(chip->pin_out1,PWMA*Vs);
    pin_write(chip->pin_AO1,PWMA);
  else
    pin_write(chip->pin_AO1,0);
  if (AIN2 && nSTBY)
    pin_write(chip->pin_AO2,PWMA);
  else
    pin_write(chip->pin_AO2,0);
  //motor B control
  if (BIN1 && nSTBY) 
    pin_write(chip->pin_BO1,PWMB);
  else
    pin_write(chip->pin_BO1,0);
  if (BIN2 && nSTBY)
    pin_write(chip->pin_BO2,PWMB);
  else
    pin_write(chip->pin_BO2,0);
}
