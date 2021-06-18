#include "LTC2944.h"

const unsigned int fullCapacity = 3200; // Maximum value is 22000 mAh

LTC2944 gauge(11); // Takes R_SENSE value (in milliohms) 

void setup() {
  Serial.begin(9600);
  Serial.println("LTC2944 Battery Readings Example");
  Serial.println();

  Wire.begin();

  while (gauge.begin() == false) {
    Serial.println("Failed to detect LTC2944!");
    delay(5000);
  }
  gauge.setBatteryCapacity(fullCapacity);
//  gauge.setBatteryToFull(); // Sets accumulated charge registers to the maximum value
////  gauge.setADCMode(ADC_MODE_MANUAL); 
////  gauge.configureALCC(ALCC_MODE_ALERT);//ALCC_MODE_CHG_COMPLETE
//////  gauge.setVoltageThresholds(13.0,9.0);
//////  gauge.setCurrentThresholds(0.100,-0.10);
//////  gauge.setTemperatureThresholds(60.0,10.0);
////  gauge.setRawAccumulatedCharge(0x1600);//
  gauge.startMeasurement();
}

void loop() {
  unsigned int raw = gauge.getRawAccumulatedCharge();
  Serial.print(F("Raw Accumulated Charge: "));
  Serial.println(raw, DEC);

  float capacity = gauge.getRemainingCapacity();
  Serial.print(F("Battery Capacity: "));
  Serial.print(capacity, 3);
  Serial.print(F(" / "));
  Serial.print(fullCapacity, DEC);
  Serial.println(F(" mAh"));

  float voltage = gauge.getVoltage();
  Serial.print(F("Voltage: "));
  Serial.print(voltage, 3);
  Serial.println(F(" V"));

  float temperature = gauge.getTemperature();
  Serial.print(F("Temperature: "));
  Serial.print(temperature, 2);
  Serial.println(F(" 'C"));


  float current = gauge.getCurrent();
  Serial.print(F("Current: "));
  Serial.print(current, 3);
  Serial.println(F(" 'Amps"));

  
  float rem_capicity = gauge.getRemainingCapacity();
  Serial.print(F("remanning_capicity: "));
  Serial.print(rem_capicity, 3);
  Serial.println(F(" 'mAh"));


  struct gauge_status my_status;
  struct gauge_status *data = &my_status;
  *((uint8_t*)data)  = gauge.getStatus();
  Serial.print("********Status reg**** ");
  Serial.print("\nUVLO               : " + String(data->UVLO_alrt) + 
               "\nvoltage_alrt       : " + String(data->voltage_alrt) +
               "\ncharge_high_alrt   : " + String(data->charge_high_alrt) + 
               "\ncharge_low_alrt    : " + String(data->charge_low_alrt) + 
               "\ncharge_low_alrt    : " + String(data->charge_low_alrt) + 
               "\nacc_chrg_high_low  : " + String(data->acc_chrg_high_low) + 
               "\ncurrent_alrt       : " + String(data->current_alrt) );
               
  
  Serial.println("\n\n");

  delay(5000);
}
