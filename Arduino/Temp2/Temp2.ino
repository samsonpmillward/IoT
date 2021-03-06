#include <U8glib.h>

#include <dht.h>

dht DHT;
U8GLIB_SH1106_128X64 u8g(4, 5, 6, 7);  // SW SPI Com: SCK = 4, MOSI = 5, CS = 6, A0 = 7 (new blue HalTec OLED)

String users[] = {"a","b","c","d"};
int i = 0;

int buttonPin = 2;

#define DHT11_PIN 3

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
  u8g.setPrintPos(0,0);
}

void drawUser(void) {
  u8g_prepare();
  u8g.print("User: ");
  u8g.print(users[i]);
}

void draw(void) {
  u8g_prepare();
  u8g.print("User: ");
  u8g.print(users[i]);
  u8g.println();
  u8g.setPrintPos(0,20);
  u8g.println("Temperature = ");
  u8g.print(DHT.temperature);
  
}

void setup() {
  Serial.begin(9600);
  
  // flip screen, if required
  u8g.setRot180();

  
  pinMode(buttonPin, INPUT_PULLUP);           
  //digitalWrite(13, HIGH);  
}


void loop()
{
  u8g.firstPage();
  int chk = DHT.read11(DHT11_PIN);
  int buttonValue = digitalRead(buttonPin);
  
  if (buttonValue == LOW) {
    Serial.println(users[i]);
    do {
        drawUser();
      }
      while ( u8g.nextPage() );
    if (i == 4) {
      i = 0;
    }
    i++;
    delay(1000);
  }
  if (DHT.temperature != -999) {
    
      //int chk = DHT.read11(DHT11_PIN);
      Serial.print("Temperature = ");
      Serial.println(DHT.temperature);
      Serial.print("Humidity = ");
      Serial.println(DHT.humidity);
      
      do {
        draw();
      }
      while ( u8g.nextPage() );
      
      //u8g.print(DHT.temperature);
      //delay(1000);
      
  }
}
