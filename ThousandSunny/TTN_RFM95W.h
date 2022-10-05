#ifndef _TTN_RFM95W_H
  #define _TTN_RFM95W_H
  
  //#define MCI_MSP430FR5969
  #define MCI_MSP430F5529
   
  #ifdef MCI_MSP430FR5969
    //PIN MAP MSP430FR5969  
    /* RFM95W SPI      BMP085 y CCS811 I2C    SHT10          PPD42NS           MQ-131
       Vcc a 3.3V          Vcc a 3.3V        Vcc a 5V      Pin3 Vcc a 5V      Vcc a 5v
       SCLK   P2.2         SCL a P3.5        SCK a P1.2    Pin2 P2 a P1.2     AO a P4.2
       MISO   P1.7         SDA a P3.6        DAT a P2.6    Pin4 P1 a P3.0
       MOSI   P1.6    
    */
    #define RFM95_RST   5   //P4.3
    #define RFM95_CS    11  //P1.3
    #define RFM95_DIO0  12  //P1.4
    #define RFM95_DIO1  13  //P1.5
    //#define P1        19  //P1.2 (particles size over 1um)
    //#define P2        8  //P3.0 (particles size over 2.5um)
  
  #endif
  
  #ifdef  MCI_MSP430F5529
    //PIN MAP MSP430F5529
    /* RFM95W SPI      BMP085 y CCS811 I2C    SHT10          PPD42NS           MQ-131
       Vcc a 3.3V          Vcc a 3.3V        Vcc a 5V      Pin3 Vcc a 5V      Vcc a 5V
       SCLK   P3.2         SCL a P4.2        SCK a P3.3    Pin2 P2 a P1.2     AO a P6.5
       MISO   P3.2         SDA a P4.1        DAT a P3.4    Pin4 P1 a P1.3
       MOSI   P3.0    
    */  
    #define RFM95_RST   17  //P7.4
    #define RFM95_CS    18  //P2.2
    #define RFM95_DIO0  5   //P1.6
    #define RFM95_DIO1  30  //P3.5
    //#define P1          36  //P1.3 (particles size over 1um)
    //#define P2          35  //P1.2 (particles size over 2.5um)
  
  #endif
  
  // LoRaWAN NwkSKey, network session key (MSB format)
  static const PROGMEM u1_t NWKSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  
  // LoRaWAN AppSKey, application session key (MSB format)
  static const u1_t PROGMEM APPSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  
  // LoRaWAN end-device address (DevAddr)
  static const u4_t DEVADDR = 0x00000000 ; 

#endif
