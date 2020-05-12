void setup() {
        int VCC = 3.3;  // NodeMCU on board 3.3v vcc
        int R2 = 10000;  // 10k ohm series resistor
        int adc_resolution = 1023; // 10-bit adc
      
      // thermistor equation parameters
      int A = 0.001129148; 
      int B = 0.000234125;
      int C1 = 8.76741;
      int C2 = pow(10, -8); 
      int C = C1*C2;
      int x; 
      
      // initiating button
      //buttonPin = 2
      //gpio.mode(buttonPin, gpio.INPUT)
      //gpio.write(buttonPin, gpio.LOW)
      
}      
int ln(int x) {     //natural logarithm function for x>0 real values
          int y = (x-1)/(x+1);
          int sum = 1; 
          int val = 1;
      // we are using limited iterations to acquire reliable accuracy.
      // here its upto 10000 and increased by 2
          for (int i = 3; i < 10000; i=i+2) {
              val = val*(y*y);
              sum = sum + (val/i);
          }
          return 2*y*sum;
}

void loop() {
  while (true) {

    int Vout, Rth, temperature;
    //int adc_value = adc.read(0);
    int adc_value = analogRead(0);
    Vout = (adc_value * VCC) / adc_resolution
    Rth = (VCC * R2 / Vout) - R2
    
    temperature = (1 / (A + (B * ln(Rth)) + (C * (ln(Rth))^3)))   // Temperature in kelvin
    temperature = temperature - 273.15  // Temperature in degree celsius
        //if (temperature != -273) {
        //pinMode(A0, OUTPUT)
       // digitalWrite(A0, HIGH)
    print(string.format("Temperature = %0.3g °C",temperature));
        //print(digitalRead(A0))
    tmr.delay(100000);
        //}
  // put your main code here, to run repeatedly:
  }
}






   
