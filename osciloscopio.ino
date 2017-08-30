#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
 
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define GENIAL  0x8888

float tensao;
 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
 
void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
 
  #ifdef USE_ADAFRUIT_SHIELD_PINOUT
    Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
  #endif
 
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
 
  tft.reset();
 
  uint16_t identifier = 0x9341;    //Need hardcode here (IC)
 
  Serial.println(F("Found ILI9341 LCD driver"));
 
  tft.begin(identifier);
 
  Serial.println(F("Benchmark                Time (microseconds)"));
 
  Serial.print(F("Text                     "));
  delay(3000);

  tft.setRotation(1);
  Serial.print("Width: ");
  Serial.println(tft.width());
  Serial.print("Height: ");
  Serial.println(tft.height());
}


 
void loop(void) {
    //limpando a tela
    tft.fillScreen(WHITE);

    const int SEPARATOR = 20;

    for(int y = 0; y <= tft.height(); y += SEPARATOR)
      tft.drawLine(0, y, tft.width(), y, BLACK);
    
    for(int x = 0; x < tft.width(); x += SEPARATOR)
      tft.drawLine(x, 0, x, tft.height(), BLACK);
    
    tensao = analogRead(A5)*5.0/1023.0;

    float x0, y0;
    float x1, y1;

    x0 = 0;
    y0 = ((tensao * 100) / 5.0) + 100;

    //enviando para o console da leitura obtida
    Serial.print(x0);
    Serial.print(",");
    Serial.println(tensao);

    int DIVISION = 100;

    for(int i = 1; i <= DIVISION; i++) {
        delay(90);
        tensao = analogRead(A5)*5.0/1023.0;

        x1 = (tft.width()*i)/DIVISION;
        y1 = ((tensao * 100) / 5.0) + 100;

        tft.drawLine(x0, y0, x1, y1, RED);

        Serial.print(x1);
        Serial.print(",");
        Serial.println(tensao);
        x0 = x1;
        y0 = y1;
    }
}
