#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int resetPin = 12;
const int startPos = 2;

const int startingS = 0;
const int startingM = 15;


int S = startingS; // count seconds
int M = startingM; // count minutes
int H = 00; // count hours

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

unsigned long lastSecond;

boolean stopCounting = false;

signed short minutes, secondes;
char timeline[16];

uint8_t customChars[4][8] = {
  {0x1f, 0x1f, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x1f, 0x1f},
  {0x1f, 0x1f, 0x1f, 0x0, 0x0, 0x1f, 0x1f, 0x1f},
  {0x0, 0x0, 0xe, 0xe, 0xe, 0xe, 0x0, 0x0}
};


byte bigNums[10][2][3] = {
  {
    {255, 0, 255},
    {255, 1, 255}
  }, {
    {0, 255, 254},
    {1, 255, 1}
  }, {
    {2, 2, 255},
    {255, 1, 1}
  }, {
    {0, 2, 255},
    {1, 1, 255}
  }, {
    {255, 1, 255},
    {254, 254, 255}
  }, {
    {255, 2, 2},
    {1, 1, 255}
  }, {
    {255, 2, 2},
    {255, 1, 255}
  }, {
    {0, 0, 255},
    {254, 255, 254}
  }, {
    {255, 2, 255},
    {255, 1, 255}
  }, {
    {255, 2, 255},
    {254, 254, 255}
  }
};

void printBigChar (int digit, int col, int row) {
  for (int x = 0; x < 2; x++) {
    lcd.setCursor(col, row + x);
    for (int y = 0; y < 3; y++) {
      lcd.write(bigNums[digit][x][y]);
    }
  }
}

void printBigColon (int col, int row) {
  lcd.setCursor(col, row);
  lcd.write(3);
  lcd.setCursor(col, row + 1);
  lcd.write(3);
}

void addBigChars() {
  for (int x = 0; x < sizeof(customChars) / sizeof(customChars[0]); x++) {
    lcd.createChar(x, customChars[x]);
  }
}

void setup()
{
  lcd.begin();
  lcd.backlight();
  addBigChars();
  
  pinMode(resetPin, INPUT);
  lastSecond = millis();

}
void loop()
{
  if (!stopCounting) {
    lcd.setCursor(2, 0);
    lcd.print ("STEAL AND ESCAPE");

    if (millis() - lastSecond >= 1000) {
      S--;
      lastSecond = millis();
    }

    if (S < 0)
    {
      M--;
      S = 59;
    }
    if (M < 0)
    {
      H--;
      M = 59;
    }
    if (H < 0) {
      H = 23;
      M = 59;
      S = 59;
    }

    if (M > 9)
    {
      printBigChar((M / 10U) % 10, 0 + startPos, 2);
      printBigChar((M / 1U) % 10, 4 + startPos, 2);
      printBigColon(8 + startPos, 2);
    }
    else
    {
      printBigChar(0, 0 + startPos, 2);
      printBigChar(M, 4 + startPos, 2);
      printBigColon(8 + startPos, 2);
    }

    if (S > 9)
    {
      printBigChar((S / 10U) % 10, 10 + startPos, 2);
      printBigChar((S / 1U) % 10, 14 + startPos, 2);
    }
    else
    {
      printBigChar(0, 10 + startPos, 2);
      printBigChar((S / 1U) % 10, 14 + startPos, 2);
    }

    /* if (H > 9)
      {
       lcd.setCursor(4, 1);
       lcd.print (H);
      }
      else
      {
       lcd.setCursor(4, 1);
       lcd.print("0");
       lcd.setCursor(5, 1);
       lcd.print(H);
       lcd.setCursor(6, 1);
       lcd.print(":");
      }
    */
    if (M >= 59) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print ("STEAL AND ESCAPE");
      lcd.setCursor(5, 2);
      lcd.print("GAME OVER");
      stopCounting = true;
    }
  }



  if (digitalRead(resetPin)) {
    S = startingS; // count seconds
    M = startingM; // count minutes
    H = 0; // count hours
    stopCounting = false;
    lcd.clear();
  }
}

