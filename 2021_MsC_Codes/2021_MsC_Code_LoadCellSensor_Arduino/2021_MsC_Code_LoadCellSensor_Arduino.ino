/*  Version: V1
 *  Date: March 2021
 *  By: Mario De Los Santos
 *  
 *  INAOE: https://www.inaoep.mx/
 *  
 *  Licensing: GNU General Public License v3.0
 *  Reference: FSR testing www.ladyada.net/learn/sensors/fsr.html */
 
 /*Note: You have available to use the ports: A2, A3, A4, A5.
  Circuit relation:
  PC2 -> A2
  PC3 -> A3
  PC4 -> A4 -> SDA
  PC5 -> A5 -> SCL

  The circuit brights you the possibility to use I2C devices
  */
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
long fsrForce;       // Finally, the resistance converted to force
void setup(void) {
  Serial.begin(115200);   // We'll send debugging information via the Serial monitor
} 
void loop(void) {
  fsrReading = analogRead(fsrPin);  
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  //Serial.print("Voltage reading in mV = ");
  //Serial.println(fsrVoltage);  
 
  if (fsrVoltage == 0) {
    Serial.println(0);  
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V  yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;;
 
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
    // Use the two FSR guide graphs to approximate the force(check the link in the description)
    
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      //Force in Newtons
      Serial.println(fsrForce);      
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.println(fsrForce);            
    }
  }
  delay(250);
}
