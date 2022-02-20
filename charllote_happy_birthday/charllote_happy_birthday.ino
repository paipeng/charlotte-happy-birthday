
#include <Sipeed_ST7789.h>
#include <lcd.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define GPIO_OUTPUT 4


SPIClass spi_(SPI0); // MUST be SPI0 for Maix series on board LCD
Sipeed_ST7789 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, spi_);


uint8_t* data;
int depth = 2;


void func()
{
  lcd.fillScreen(COLOR_RED);
  //lcd.drawRect(20, 20, 50, 50, COLOR_WHITE);
  //lcd.fillCircle(100, 100, 40, COLOR_WHITE);
  //lcd.fillTriangle(10, 200, 300, 200, 300, 150, COLOR_WHITE);
  
  lcd.setTextSize(3);
  lcd.setTextColor(COLOR_WHITE);
  lcd.setCursor(30, 30);
  lcd.println("Happy Birthday");
  
  lcd.setTextSize(5);
  lcd.setCursor(30, 90);
  lcd.println("Charlotte");
  lcd.setCursor(100, 150);
  lcd.println("Peng");

  lcd.setTextSize(2);
  lcd.setCursor(100, 210);
  lcd.println("2022-02-20");
}


void setup() {
  lcd.begin(15000000, COLOR_RED);
  randomSeed(analogRead(0));
  data = (uint8_t*) malloc(SCREEN_WIDTH * SCREEN_HEIGHT * depth * sizeof(uint8_t));
}

void loop() {
  // put your main code here, to run repeatedly:

  func();
  delay(100000);
}
