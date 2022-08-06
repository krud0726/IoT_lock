#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {            //학교종이 땡땡땡의 음을 나타내는 배열
 NOTE_B7,                 
  NOTE_B7,                 
  NOTE_B7,                  
  NOTE_B7
};
int durations[] = {      //음 길이를 나타내는 배열
  1, 1, 1, 1
};

uint8_t id;

uint8_t k = 0;

int state = 0;

uint8_t getFingerprintEnroll();

int getFingerprintIDez();

char val;


SoftwareSerial mySerial(10, 11);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
//LED 핀설정

 
//스위치 핀설정
int sw1 = 5;
int sw2 = 6;
int sw3 = 7;

//충격 핀설정
#define SHOCK 8 

// 블루투스 모듈의 TXD 핀과 연결된 2번을 T 라는 변수로,
// 블루투스 모듈의 RXD 핀과 연결된 3번을 R 이라는 변수로 선언한다.

// LED 가 연결된 4번 핀을 LED 라는 변수로 선언한다.

// serial1 라는 이름의 블루투스 객체를 선언하는데,
// 이 블루투스 객체는 T 와 R 에 의해 제어된다.

void setup() {
  // 블루투스 통신을 시작한다.
   Serial1.begin(9600);
  //시리얼 모니터
  Serial.begin(9600); 
  //지문인식 속도
    finger.begin(576600);
//13번 릴레이 모듈을 출력으로
  pinMode(13,OUTPUT);
  
  //9번 피에조 출력
  pinMode(9,OUTPUT);
  
  //SW 1,2를 설정, 아두이노 풀업저항 사용
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  
    pinMode(SHOCK, INPUT);
    //shock 핀을 입력 핀으로 설정한다.

  //sw1 on setup
  if(digitalRead(sw1)==LOW && digitalRead(sw2)==HIGH && digitalRead(sw3)==HIGH) // sw1이 low 일시 작동
  {
    while (!Serial);  // For Yun/Leo/Micro/Zero/...
    delay(500);
  
    Serial.println("Adafruit Fingerprint sensor enrollment");

    // set the data rate for the sensor serial port
 
   if (finger.verifyPassword()) {       // 비밀번호 확인
    Serial.println("Found fingerprint sensor!");
  } 
  else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
 }
 
 //sw2 on setup
 else if(digitalRead(sw1)==HIGH && digitalRead(sw2)==LOW && digitalRead(sw3)==HIGH) {  // sw2이 low 일시 작동

  Serial.println("fingertest");

  // set the data rate for the sensor serial port

  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
 }
}

 uint8_t readnumber(void) {
  uint8_t num = 0;
  boolean validnum = false; 
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    if (isdigit(c)) {
       num *= 10;
       num += c - '0';
       validnum = true;
    } else if (validnum) {
      return num;
    }
  }
}

void loop() {
  digitalWrite(9,HIGH);       // 피에조 스피커 작동

   if(Serial1.available())
  // 만약 어떤 입력이 존재한다면
  {
     val = Serial1.read();
    // 휴대폰 어플로 입력한 문자를 받아와서 val 에 저장한다.
  
    if (val == '0')
    // 만약 읽어온 문자가 R 이라면, 
    {
    k=1;
    Serial.println("open");
      // LED 를 작동시킨다.
    }

   else if(val == '1')
    // 만약 읽어온 문자가 N 이라면,
    {
      Serial.println("close");
       k=0;
      // LED 를 끈다.
    }
  }
    if (digitalRead(SHOCK ) == HIGH) {
    Serial.println("SHOCK!!!!");
    Serial1.println("shock!!!");
    delay(1000);
    for (int number = 0; number < 4; number++) {
    int duration = 250 * durations[number];
    tone(9, melody[number], duration);
    delay(duration);
    noTone(9);
  }
  }
  
//if문을 이용해 충격감지센서가 HIGH가 되면 pc모니터와 bluetooth를 이용해 핸드폰화면에 알림이 뜬다
//k=1이면 문이 열리고 0이면 문이 닫힌다
  if(k == 0)
  {
     digitalWrite(13,HIGH);
  }
   else if(k == 1)
   {
     digitalWrite(13,LOW);
   }
 
  //SW1 ON, SW2 OFF => LED1 ON, LED2 OFF
  if((digitalRead(sw1)==LOW && digitalRead(sw2)==HIGH && digitalRead(sw3)==HIGH) && k==1) 
  {
     Serial.println("Ready to enroll a fingerprint! Please Type in the ID # you want to save this finger as...");
     id = readnumber();
     Serial.print("Enrolling ID #");
     Serial.println(id);
  
     while (!  getFingerprintEnroll() );
       Serial.println("SW1 ON");
  //SW1 OFF, SW2 ON => LED1 OFF, LED2 ON  
  }
  
  else if(digitalRead(sw1)==HIGH && digitalRead(sw2)==LOW && digitalRead(sw3)==HIGH) 
  {
    if(state==0){
      state=1;
      delay(500);
     }
     else if(state==1){
      state=0;
      delay(500);
     }
      Serial.println(state);
      Serial.println("SW2 ON");
     getFingerprintID();
  //SW1 ON, SW2 ON => LED1 ON, LED2 ON  
  }
  
  else if(digitalRead(sw1)==HIGH && digitalRead(sw2)==HIGH && digitalRead(sw3)==LOW)
  {

    k=0;
    
    Serial.println("SW3 ON");
    delay(50);
  //SW1 OFF, SW2 OFF => LED1 OFF, LED2 OFF    
  }
  
   if(state==1)
       {
          getFingerprintIDez();
          
          delay(50);            //don't ned to run this at full speed.  
       }
}



// -------------------------------------------loop문 끝----------------------------------------
uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
 // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {

  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  k=1;
  state=0;
  return finger.fingerID; 
}
