
#include <Sipeed_ST7789.h>
#include <lcd.h>
#include "charlotte.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define GPIO_OUTPUT 4


#define RGB2COLOR(r, g, b) ((((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)))
#define RGB2COLORINT(RGB) (((( ((RGB>> 16) & 0xFF)   >> 3) << 11) | ((((RGB>> 8) & 0xFF) >> 2) << 5) | ((RGB & 0xFF) >> 3)))

SPIClass spi_(SPI0); // MUST be SPI0 for Maix series on board LCD
Sipeed_ST7789 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, spi_);


uint8_t* data;
int depth = 2;

static int mqrquee_x = 0;

void drawCharlotteMarquee(int x, int y, int color) {
  int i, j;
  int k, l;
  int zoom = 3;
  lcd.fillRect(0, y, SCREEN_WIDTH, 7*zoom, COLOR_RED);  
  for (i = 0; i < 7*zoom; i+=zoom) {
    for (j = 0; j < 94*zoom; j+=zoom) {
      if (CHARLOTTE[94*i/zoom+j/zoom] == 1) {
        for (k = 0; k < zoom; k++) {
          for (l = 0; l < zoom; l++) {
            lcd.drawPixel(j + x + l, i + y + k, color);            
          }
        }
      }
    }
  }
}

void drawHeart(int x, int y, int color)
{
  int i, j;
  for (i = 0; i < 30; i++) {
    for (j = 0; j < 40; j++) {
      if (HEART[i*40+j] == 1) {
        lcd.drawPixel(j + x, i + y, color);
      }
    }
  }
}

void drawCharlotteImage() {
  int i, j;

  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH* depth; j+= depth) {
      uint8_t pixel_r = (CHARLOTTE_IMG[ i * SCREEN_WIDTH + j/depth] >> 16) & 0xFF ;
      uint8_t pixel_g = (CHARLOTTE_IMG[ i * SCREEN_WIDTH + j/depth] >> 8) & 0xFF ;
      uint8_t pixel_b = CHARLOTTE_IMG[ i * SCREEN_WIDTH + j/depth] & 0xFF ;

      unsigned short rgb565 = RGB2COLOR(pixel_r, pixel_g, pixel_b);
      *(data + i * SCREEN_WIDTH * depth + j) = (rgb565 & 0xFF00) >> 8;
      *(data + i * SCREEN_WIDTH * depth + j + 1) = rgb565 & 0xFF;
    }
  }
  lcd.drawImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (uint16_t*)data);
}




void func()
{
  lcd.fillScreen(COLOR_RED);
  //lcd.drawRect(20, 20, 50, 50, COLOR_WHITE);
  //lcd.fillCircle(100, 100, 40, COLOR_WHITE);
  //lcd.fillTriangle(10, 200, 300, 200, 300, 150, COLOR_WHITE);
  
  lcd.setTextSize(3);
  lcd.setTextColor(COLOR_WHITE);
  lcd.setCursor(40, 30);
  lcd.println("Happy Birthday");
  
  lcd.setTextSize(5);
  //lcd.setCursor(30, 90);
  //lcd.println("Charlotte");
  lcd.setCursor(100, 150);
  lcd.println("Peng");

  lcd.setTextSize(2);
  lcd.setCursor(100, 210);
  lcd.println("2022-02-20");

  drawHeart(30, 150, COLOR_WHITE);
  
  drawHeart(250, 150, COLOR_WHITE);

}


void setup() {
  lcd.begin(15000000, COLOR_RED);
  randomSeed(analogRead(0));
  data = (uint8_t*) malloc(SCREEN_WIDTH * SCREEN_HEIGHT * depth * sizeof(uint8_t));
  
  func();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mqrquee_x == -50) {
    mqrquee_x = SCREEN_WIDTH;
    drawCharlotteImage();
    delay(3000);
    func();
  }
  drawCharlotteMarquee(mqrquee_x,100,COLOR_WHITE);
  mqrquee_x -=10;
  delay(300);

  
}
