#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>

Servo myservo;
int pos=0;
int readPIR=0;
int motionflag=0;
int pirPin = 8; 

LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows=4;
const byte cols=3;

char key[rows][cols]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'},
};

byte rowPins[rows]={0,1,2,3};
byte colPins[cols]={4,5,6};
Keypad keypad = Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="7255";
int currentposition=0;

int red = 12;
int green = 13;
int buzzer = 10;
int blue = 19;
int wrong = 0;
int pir=0;
int total = 0;


void setup() {
    lcd.begin(16,2);    
    pinMode(8, INPUT);
    //pinMode(9, OUTPUT);
    //digitalWrite(9, HIGH); 
    //pinMode(2, INPUT);
    //pinMode(3, OUTPUT);
    //digitalWrite(3, HIGH);
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(19,OUTPUT);
    myservo.attach(9);
    lcd.begin(16,2);
    lcd.print("HOME SECURITY");
    lcd.setCursor(0,1);
    lcd.print("SYSTEM");
    lcd.setCursor(0,2);
    delay(3000);
    lcd.clear();
    readPIR = digitalRead(pirPin); 

    if (readPIR == 1){ 
      motion_detected_1();
    }
    else{
      motion_detected_2();
    }
}

void loop() {
   if(currentposition==0){
    displayscreen();
  }
  int n;
  char code=keypad.getKey();
  if(code!=NO_KEY){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
    for(n=0;n<=currentposition;++n){
      lcd.print("*");
    }

    if(code==password[currentposition]){
      ++currentposition;
    }
    else if(code != password[currentposition]){
      wrong++;
      currentposition++;
    }
    if(currentposition==4){

        if(wrong > 0){
          total++;
          wrong = 0;
          currentposition = 0;
          incorrect();
        }

        else if(currentposition==4 && wrong == 0){
          currentposition = 0;
          wrong = 0;
          unlockdoor();
        }
        if(total == 3){
          total = 0;
          buzzer_beep();
          delay(500);
          motion_detected_2();
        }
    }
    
  }

}

void motion_detected_1()
{
  
  if (readPIR == 1) {
    motionflag=0;
    lcd.home();
    //digitalWrite(readPIR,HIGH);
    lcd.println("Someone Here");
    delay(500);
    lcd.clear();
    
    loop();
    delay(500);
    lcd.clear();
   
  }
  
}

void motion_detected_2()
{
  readPIR = digitalRead(pirPin); 
   
  if (readPIR==0&&motionflag== 0) {
    
    lcd.clear();
    lcd.println("No one here..");
    //motionflag=1;
    delay(1000);
    
    setup();

  } 
  else{
    if (readPIR == 1){
      if(motionflag== 0){
        lcd.clear();
        lcd.println("No one here..");
        delay(1000);
        //motion_detected_2();
         setup();
      }
      else{
        motion_detected_1();  
      }
      
    }
  }
}


void displayscreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("ENTER THE CODE");
  lcd.setCursor(1,1);
  lcd.println("TO OPEN DOOR!!");
}

void incorrect(){
  digitalWrite(red,HIGH);
  delay(1000);
  digitalWrite(red,LOW);
  delay(500);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("CODE");
  lcd.setCursor(6,0);
  lcd.print("INCORRECT");
  lcd.println(" ");
  lcd.setCursor(3,1);
  lcd.println("GET AWAY!!!");
  delay(1000);
  lcd.clear();
  displayscreen();
}

void unlockdoor(){

  
  digitalWrite(green,HIGH);
  delay(2000);
  digitalWrite(green,LOW);
  delay(1000);

  lcd.setCursor(0,0);
  lcd.println(" ");
  lcd.setCursor(1,0);
  lcd.print("Access Granted");
  lcd.setCursor(4,1);
  lcd.println("WELCOME!!");
  lcd.setCursor(16,1);
  lcd.println(" ");
  lcd.setCursor(15,1);
  lcd.println(" ");
  lcd.setCursor(14,1);
  lcd.println(" ");
  lcd.setCursor(13,1);
  lcd.println(" ");
  
  for(pos = 0; pos<=180; pos += 5){
    myservo.write(pos);
    delay(5);
  }
  delay(2000);
  delay(1000);
  counterbeep();

  delay(1000);

  for(pos = 180; pos >= 0; pos -= 5){
    myservo.write(pos);
    delay(15);
    currentposition=0;
    lcd.clear();
    displayscreen();
  }
}

void counterbeep(){
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  delay(200);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1);
  lcd.print("5");
  delay(200);
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN::");
  delay(1000);
  
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1);
  lcd.print("4");
  delay(200);
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN::");
  delay(1000);


  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1);
  lcd.print("3");
  delay(200);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN::");
  delay(1000);

  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1);
  lcd.print("2");
  delay(200);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN::");
  delay(1000);

  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1);
  lcd.print("1");
  delay(200);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN::");
  delay(1000);

  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN");
  lcd.setCursor(4,1);
  lcd.print("0");
  delay(200);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN");
  delay(1000);
  
  delay(40);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("RE-LOCKING");
  delay(500);
  lcd.setCursor(12,0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(13,0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(14,0);
  lcd.print(".");
  delay(400);
  lcd.setCursor(5,0);
  lcd.print("LOCKED!");
  delay(440);
  digitalWrite(red,HIGH);
  delay(2000);
  digitalWrite(red,LOW);
  delay(1000);

  motionflag=1;
  motion_detected_2();
  
}

void buzzer_beep(){
  lcd.clear();
  lcd.print("WARNING!!");
  lcd.setCursor(0,1);
  lcd.print("Access Denied");
  lcd.setCursor(0,2);
  motionflag=0;
  for(int i=0;i<3;i++){
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(buzzer,LOW);
    delay(1000);
  }
}
