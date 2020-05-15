#include <U8glib.h>
#include <SoftwareSerial.h>
#include <dht.h>


#define DHT11_PIN 3                     // Sets the pin of the DHT module.
#define BT_SERIAL_TX 11                 //Sets pins of the BT module.
#define BT_SERIAL_RX 12
#include <SparkFun_Bio_Sensor_Hub_Library.h>  // Adds the heart rate monitor library
#include <Wire.h>

int resPin = 4;
int mfioPin = 5;

SparkFun_Bio_Sensor_Hub bioHub(resPin, mfioPin); 
bioData body;


dht DHT;
U8GLIB_SH1106_128X64 u8g(4, 5, 6, 7);  // Sets up the LCD display with the relevant pins.

String users[] = {"a","b","c","d"};     // Creates an array of the users for the project. 
int i = 0;

int buttonPin = 2;                      //Sets the button that switches users.

SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);

void u8g_prepare(void) {                // Sets the intial display settings.  
  u8g.setFont(u8g_font_7x13r);
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
  u8g.setPrintPos(0,0);
}

void drawUser(void) {                   // Updates the user when the button is clicked (or when facial recognition detects new user).
  u8g_prepare();
  u8g.print("User: ");
  u8g.print(users[i]);
}

void draw(void) {                       // Outputs the current vital signs and user when button is pressed.
  u8g_prepare();
  u8g.print("User: ");
  u8g.print(users[i]);
  u8g.println();
  u8g.setPrintPos(0,10);
  u8g.println("Temperature=");
  u8g.print(DHT.temperature);
  u8g.setPrintPos(0,20);
  if (DHT.temperature > 37.20 || DHT.temperature < 36.10) {     //Outputs different messages depending on temperature read by the thermometer.
        u8g.println("You may be unwell");
      }
  else {
        u8g.println("You are healthy");
  }
  u8g.setPrintPos(0,30);
  u8g.println("Heart Rate=");
  Wire.begin();
  //u8g.println(bioData.readBpm());
  
}

void setup() {
  Serial.begin(9600);
  u8g.setRot180();                                          // flips screen
  BluetoothSerial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);         
  
  
}

void waitForBluetooth() {                               // Waits for Bluetooth response
  delay(1000);
  while (BluetoothSerial.available()) {
   Serial.write(BluetoothSerial.read());
}
} 

void loop()
{
  u8g.firstPage();
  int tempUpdate = DHT.read11(DHT11_PIN);
  int buttonValue = digitalRead(buttonPin);
  
  if (buttonValue == LOW) {                                  //iterates through the users and reverts i (current user) back to 0 when the end of the array of users is complete
      
    i++;
    Serial.println(users[i]);
    do {
        drawUser();
      }
      while ( u8g.nextPage() );
    if (i == 4) {
      i = 0;
    }
    
    delay(1000);
  }
  if (DHT.temperature != -999) {              // Temperature reads at -999 unless button is pressed due to the button completing the circuit.
    
      Serial.print("Temperature = ");
      Serial.println(DHT.temperature);
      if (DHT.temperature > 37.20 || DHT.temperature < 36.10) {
        Serial.println("You may be unwell");
      }
      BluetoothSerial.print("Temperature: ");
      BluetoothSerial.println(DHT.temperature);
      
      do {
        draw();
      }
      while ( u8g.nextPage() );
            
  }
}
