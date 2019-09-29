int lightbulb = A0;
int  sun = A1;
int telephone = A2;
int window = A3;
int flashlight = A4;
int fire = A5;



int TL = A8;
int TM = A11;
int TR = A13;
int MR = A14;
int MM = A12;
int ML = A9;
int BL = A12;
int BM = A13;
int BR = A10;

int first[] = {TR, MR, BR};
int second[] = {TR, TL, ML, MM, ML, BR};
int third[] = {TR, TM, TL, ML, MM, ML, BR};

const int resetPin = 12;

boolean resetState = false;
unsigned long resetStartTime = 0;




void setup() {
  Serial.begin(9600);
  /*
    for(int i=0;i<3;i++)
      {
        pinMode(first[i], OUTPUT);
        pinMode(second[i], OUTPUT);
        pinMode(third[i], OUTPUT);
      }
     for(int x=0;x<6;x++)
      {
        pinMode(second[x], OUTPUT);
      }
  */
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  pinMode(TL, OUTPUT);
  pinMode(TM, OUTPUT);
  pinMode(TR, OUTPUT);
  pinMode(ML, OUTPUT);
  pinMode(MM, OUTPUT);
  pinMode(MR, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(BM, OUTPUT);
  pinMode(BR, OUTPUT);

  pinMode(resetPin, OUTPUT);

  /*
    digitalWrite(TL, HIGH);
    digitalWrite(TM, HIGH);
    digitalWrite(TR, HIGH); //TL 8
    digitalWrite(ML, HIGH); //TM 11
    digitalWrite(MM, HIGH); //BR 10
    digitalWrite(MR, HIGH); //ML 9
    digitalWrite(BR, HIGH); //MR 14
  */
  //digitalWrite(BL, HIGH); //MM 12 nOTHING
  // digitalWrite(BM, HIGH); //TR 13



}

void loop() {
  /*
    digitalWrite(TL, HIGH);
    delay(500);
    digitalWrite(TM, HIGH);
    delay(500);
    digitalWrite(TR, HIGH); //TL 8
    delay(500);
    digitalWrite(ML, HIGH); //TM 11
    delay(500);
    digitalWrite(MM, HIGH); //BR 10
    delay(500);
    digitalWrite(MR, HIGH); //ML 9
    delay(500);
    digitalWrite(BR, HIGH); //MR 14
    delay(500);
    digitalWrite(A7, HIGH);
    digitalWrite(TL, LOW);
    digitalWrite(TM, LOW);
    digitalWrite(TR, LOW); //TL 8
    digitalWrite(ML, LOW); //TM 11
    digitalWrite(MM, LOW); //BR 10
    digitalWrite(MR, LOW); //ML 9
    digitalWrite(BR, LOW); //MR 14
    digitalWrite(A7, LOW);
  */



  int lightbulbRead = analogRead(lightbulb);
  int sunRead = analogRead(sun);
  int telephoneRead = analogRead(telephone);
  int windowRead = analogRead(window);
  int fireRead = analogRead(fire);
  int flashlightRead = analogRead(flashlight);

  Serial.print("LIGHT: ");
  Serial.println(lightbulbRead);
  //delay(500);
  Serial.print("SUN: ");
  Serial.println(sunRead);
  //delay(500);
  Serial.print("TELEPHONE: ");
  Serial.println(telephoneRead);
  //delay(500);
  Serial.print("WINDOW: ");
  Serial.println(windowRead);
  //delay(500);
  Serial.print("FIRE: ");
  Serial.println(fireRead);
  //delay(500);
  Serial.print("flashlight: ");
  Serial.println(flashlightRead);


  //SUN AND LIGHTBULB - 1 - TR/MR/ML

  if (sunRead <= 100 && lightbulbRead <= 100)
  {
    digitalWrite(TR, HIGH);
    digitalWrite(MR, HIGH);
    digitalWrite(BR, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(TR, LOW);
    digitalWrite(MR, LOW);
    digitalWrite(BR, LOW);
  }



  //PHONE AND WINDOW - 4 - TR/TL/ML/MM/ML/BR

  if (telephoneRead <= 100 && windowRead <= 100)
  {
    digitalWrite(TR, HIGH);
    digitalWrite(TL, HIGH);
    digitalWrite(ML, HIGH);
    digitalWrite(MM, HIGH);
    digitalWrite(MR, HIGH);
    digitalWrite(BR, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(TR, LOW);
    digitalWrite(TL, LOW);
    digitalWrite(ML, LOW);
    digitalWrite(MM, LOW);
    digitalWrite(MR, LOW);
    digitalWrite(BR, LOW);
  }

  //FIRE AND FLASHLIGHT - 9 - TR/TM/TL/ML/MM/ML/BR

  if (fireRead <= 100 && flashlightRead <= 100)
  {
    digitalWrite(TR, HIGH);
    digitalWrite(TM, HIGH);
    digitalWrite(TL, HIGH);
    digitalWrite(ML, HIGH);
    digitalWrite(MM, HIGH);
    digitalWrite(MR, HIGH);
    digitalWrite(BR, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(TR, LOW);
    digitalWrite(TM, LOW);
    digitalWrite(TL, LOW);
    digitalWrite(ML, LOW);
    digitalWrite(MM, LOW);
    digitalWrite(MR, LOW);
    digitalWrite(BR, LOW);
  }

  if (fireRead <= 100 && sunRead <= 100 && windowRead <= 100 && flashlightRead >= 100 &&  telephoneRead >= 100 && lightbulbRead >= 100) {
    if (!resetState) {
      resetState = true;
      resetStartTime = millis();
    }
    else {
      if (millis() - resetStartTime > 10000) {
        digitalWrite(resetPin, HIGH);
        delay(1000);
        digitalWrite(resetPin, LOW);
      }
    }
  }
  else {
    resetState = false;
  }


}
