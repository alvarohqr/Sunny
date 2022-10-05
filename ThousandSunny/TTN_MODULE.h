#ifndef _TTN_MODULE_H_
#define _TTN_MODULE_H_

  //! Códigos fuente
  #include <SHT1x.h>
  #include "Adafruit_CCS811.h"
  #include "Adafruit_BMP085.h"
  #include <MQ131.h>
  
  //Reloj y datos SHT1X (R10k Vcc-Data)
  #define dataPin     3   //! P3.4 MSP430F5529LP
  #define clockPin    4   //! P3.3 MSP430F5529LP
  #define pinO3       2
  #define P1         36   //P1.3 (particles size over 1um)
  #define P2         35   //P1.2 (particles size over 2.5um)
  
  //! Objeto y direcciones
  SHT1x sht1x(dataPin, clockPin);
  Adafruit_CCS811 ccs;
  Adafruit_BMP085 bmp;
  
  //! Variables globales externas
  extern float temp , hum, temp_i, prsn, O3_ppm, O3_ug, R0;
  extern uint16_t eCO2, TVOC;
  //--------
  unsigned long duration = 0, duration2 = 0, starttime, sampletime_ms = 30000;
  unsigned long lowpulseoccupancy = 0, lowpulseoccupancy2 = 0;
  float ratio = 0, ratio2 = 0, concentration = 0, concentration2 = 0;
  //! Para conversión de pcs/0.01ft3 a ugm/m3
  float densidad = 0, R2_5 = 0, R10 = 0, V2_5 = 0, V10 = 0, m2_5 = 0, m10 = 0;
  extern float con_ugm3, con2_ugm3;
  
  //! Prototipado de funciones
  void read_sht();
  void setup_ccs811();
  void read_ccs811();
  void setup_bmp();
  void read_bmp();
  void setup_o3();
  void read_o3();
  void setup_ppd42ns();
  void read_ppd42ns();
  void pcs_to_ugm3(float c1, float c2);

#endif
