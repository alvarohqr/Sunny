#include "TTN_MODULE.h"

void read_sht() {
  // Read values from the sensor
  temp = sht1x.readTemperatureC();
  hum = sht1x.readHumidity();

}

void setup_ccs811() {
  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1);
  }
  //Calibracion en base al SHT10
  while (!ccs.available()); 
  
}

void read_ccs811() {
  if (ccs.available()) {
    ccs.setEnvironmentalData(hum, temp);
    if (!ccs.readData()) {
      eCO2 = ccs.geteCO2(); 
      TVOC = ccs.getTVOC();  
    }
    else {
      Serial.println("ERROR!");
      while (1);
    }
  }
}

void setup_bmp() {
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}

void read_bmp() {
  temp_i  =  bmp.readTemperature();
  prsn    =  bmp.readPressure()/100;
  //alt     =  bmp.readAltitude();
}

void setup_o3() {
  //MQ131.begin(0, pinO3, LOW_CONCENTRATION, 100000, (Stream *)&Serial); //! Debug
  MQ131.begin(0, pinO3, LOW_CONCENTRATION, 100000);
  //MQ131.calibrate();
  Serial.println("Calibration parameters");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");
}

void read_o3() {
  Serial.println("Sampling...");
  MQ131.sample();
  O3_ppm = MQ131.getO3(PPM);
  O3_ug = MQ131.getO3(UG_M3);
  delay(1000);
}

void setup_ppd42ns(){
  pinMode(P1, INPUT); //PM2.5
  pinMode(P2, INPUT); //PM10
  starttime = millis();
}

void read_ppd42ns(){
  duration = pulseIn(P1, LOW);
  duration2 = pulseIn(P2, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;
  lowpulseoccupancy2 = lowpulseoccupancy2 + duration2;

  if ((millis() - starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0); // Integer percentage 0=>100
    concentration = 1.1 * powf(ratio, 3) - 3.8 * powf(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
    ratio2 = lowpulseoccupancy2 / (sampletime_ms * 10.0); // Integer percentage 0=>100
    concentration2 = 1.1 * powf(ratio2, 3) - 3.8 * powf(ratio2, 2) + 520 * ratio2 + 0.62; // using spec sheet curve
    pcs_to_ugm3(concentration, concentration2);
    Serial.print("Concentration PM2.5(umg/m3): ");
    Serial.println(con_ugm3);
    Serial.println("--------------------------------------------------------------------");
    Serial.print("Concentration2 PM10 (umg/m3): ");
    Serial.println(con2_ugm3);
    Serial.println("--------------------------------------------------------------------");
    lowpulseoccupancy = 0;
    lowpulseoccupancy2 = 0;
    starttime = millis();
  }
}

//! Conversión
//Puede modificarse teniendo como argumentos el tipo de PM y su radio
void pcs_to_ugm3(float c1, float c2) {
  //Asumiendo que todas las particulas son esféricas con densidad de1.65E12 μg/m3:
  densidad  =   1.65 * powf(10, 12);
  R2_5      =   0.44 * powf(10, -6); // Radio PM2.5
  R10       =   2.60 * powf(10, -6); // Radio PM2.5
  // Volumen de una esfera = 4/3 * pi * r3
  V2_5      =   4 / 3 * PI * powf(R2_5, 3);
  V10       =   4 / 3 * PI * powf(R10, 3);
  //masa    =   densidad * volumen
  m2_5      =   densidad * V2_5;
  m10       =   densidad * V10;
  // 0.01ft3 a m3 = 3531.5
  con_ugm3  =   c1 * 3531.5 * m2_5;
  con2_ugm3 =   c2 * 3531.5 * m10;
}
