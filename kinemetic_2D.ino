int chos;
int L1=30; //Length of L1
int L2=15; //Length of L2
float Q1,Q2,m; // Q1 & Q2 are the angles to calculate
float x,y,q1,q2;
int Q=50;
#include <Servo.h>
Servo moto1;
Servo moto2;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; // three columns
//define the symbols of the buttons inthe keypad
char hexakeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {' ','0',' '} 
};
byte rowPins[ROWS] = {A2, A3, A4, A5}; // connecting pins of rows
byte colPins[COLS] = {5, 6, 7}; // connecting pins of columns

//initialize an  instance of class Newkeypad
Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS);

#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // pins of lcd

void setup() {
  // put your setup code here, to run once:
  moto1.attach(3); // attaches the motor in pin 3
  moto2.attach(4); // attaches the motor in pin 4
  lcd.begin(16, 2);
  lcd.print(" Welcome to");
  lcd.setCursor(0, 1);  // go to next line
  lcd.println("control Arm");
  delay(3000);
}
int FI(){
  // this function to let the user choose type of control the arm forward/inverse kinematic
  char kp=0;
  moto1.write(0);
  moto2.write(0);
  lcd.clear();
  lcd.print("Press 1 (forward)");
  lcd.setCursor(0,1);
  lcd.print("or 2 (inverse)");
  while (kp==0){ kp = customKeypad.getKey();}
  kp=kp-48;
  if (kp==1){
    lcd.clear();
    lcd.print("Forward kinematic");
    lcd.setCursor(0,1);
    lcd.print(1);
    delay(2000);
    return 1;
    } else if (kp==2){
     lcd.clear();
    lcd.print("Inverse kinematic");
    lcd.setCursor(0,1);
    lcd.print(2);
    delay(2000);
    return 2;
    }
}
  void forward(){
    // this function to calculate Q1&Q2
    moto1.write(q1);
    moto2.write(q2);
    lcd.clear();
    Q1=q1*PI/180;
    Q2=q2*PI/180;
    x=(L1*cos(Q1))+(L2*cos(Q1+Q2));
    y=(L1*sin(Q1))+(L2*sin(Q1+Q2));
    lcd.print("End point of arm");
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(y);
    Serial.print("Q1");
    Serial.println(q1);
    Serial.print("Q2");
    Serial.println(q2);
    delay(7000);
  }
  void inverse(){
    // this function to determine ending point of arm depending on value of x ,y
    lcd.clear();
    m=(pow(x,2)+pow(y,2)-pow(L1,2)-pow(L2,2))/(2*L1*L2);
    q2=acos(m);
    Q2=q2*180/PI;
    Q1=Q-Q2;
    lcd.print("Angle of Arm");
    lcd.setCursor(8,1);
    lcd.print("&");
    lcd.setCursor(9,1);
    lcd.print("Q2=");
    lcd.print(Q2);
    Serial.print(Q1);
    moto1.write(Q1);
    moto2.write(Q2);
    delay(7000);
    
  }



void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear(); //clear word on lcd
  chos = FI();
  if (chos==1){
    int g1=0,g2=0;
    int h1=0,h2=0;
    lcd.clear();
    lcd.print("Enter angle Q1");
    while (g1==0) {g1=customKeypad.getKey();} //waiting the user for entering the number of Q1
    lcd.setCursor(0,1);
    g1=g1-48; //Change number ASCII code
    lcd.print(g1); //show the number on the LCD
    while (g2==0) {g2=customKeypad.getKey();} //waiting the user for entering the number of Q1
    g2=g2-48; //Change number ASCII code
    lcd.print(g2); //show the number on the LCD
    delay(500);
    q1 = g1 * 10 + g2; //the sum of g1 & g2
    lcd.clear();
    lcd.print("Enter angle Q2");
    while (h1==0) {h1=customKeypad.getKey();} //waiting the user for entering the number of Q1
    lcd.setCursor(0,1);
    h1=h1-48; //Change number ASCII code
    lcd.print(h1); //show the number on the LCD
    while (h2==0) {h2=customKeypad.getKey();} //waiting the user for entering the number of Q1
    h2=h2-48; //Change number ASCII code
    lcd.print(h2); //show the number on the LCD
    delay(500);
    q2 = h1*10 + h2;
    forward(); //call forward function
  } else if (chos==2){
    int u1=0,u2=0;
    int r1=0,r2=0;
    lcd.clear();
    lcd.print("Enter value of X");
    while (u1==0) {u1=customKeypad.getKey();} //waiting the user for entering the number of Q1
    lcd.setCursor(0,1);
    u1=u1-48; //Change number ASCII code
    lcd.print(u1); //show the number on the LCD
    while (u2==0) {u2=customKeypad.getKey();} //waiting the user for entering the number of Q1
    u2=u2-48; //Change number ASCII code
    lcd.print(u2); //show the number on the LCD
    delay(500);
    x = u1 * 10 + u2; //the sum of g1 & g2
    lcd.clear();
    lcd.print("Enter value of Y");
    while (r1==0) {r1=customKeypad.getKey();} //waiting the user for entering the number of Q1
    lcd.setCursor(0,1);
    r1=r1-48; //Change number ASCII code
    lcd.print(r1); //show the number on the LCD
    while (r2==0) {r2=customKeypad.getKey();} //waiting the user for entering the number of Q1
    r2=r2-48; //Change number ASCII code
    lcd.print(r2); //show the number on the LCD
    delay(500);
    y = r1 * 10 + r2;
    inverse(); //call inverse function 
  }

}

  
  
