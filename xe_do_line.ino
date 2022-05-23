#define DL 4
#define PL 5
#define DR 7
#define PR 6
#define CBL A5
#define CBC A6
#define CBR A7
#define NUT2 2
#define NUT3 3
#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
//khai baso bien trang thai cai dat
int TT = 0;
// Khai báo biến lưu màu
int L1, L2, LTB;
int C1, C2, CTB;
int R1, R2, RTB;
// biến lưu giá trị hiện tại 
int L,R,C; 
void setup() {
  lcd.begin(16,02);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(NUT2, INPUT_PULLUP);
  // đọc giá trị ban đầu n
  L = analogRead(CBL);
  C = analogRead(CBC);
  R = analogRead(CBR);
  // khởi tạo cực đại cực tiểu
  L1 = L; L2 = L;
  R1 = R; R2 = R;
  C1 = C; C2 = C;
  // bắt đầu lấy mẫu và tính toán tự động
  while(digitalRead(NUT2)==1){
  Caidat();
  }
}
void loop() {
  // in giá trị thực lên màn hình
  lcd.setCursor(0,0);
  lcd.print(analogRead(CBL));
  lcd.setCursor(4,0);
  lcd.print(analogRead(CBC));
  lcd.setCursor(8,0);
  lcd.print(analogRead(CBR));
  //  trang den trang
  if(analogRead(CBL) > LTB && analogRead(CBC) < CTB && analogRead(CBR) > RTB){
    DONGCO(150,150);
    }
  // den trang trang
  if(analogRead(CBL) < LTB && analogRead(CBC) > CTB && analogRead(CBR) > RTB){
    DONGCO(0,150);
    }
  // trang trang den
  if(analogRead(CBL) > LTB && analogRead(CBC) > CTB && analogRead(CBR) < RTB){
    DONGCO(150,0);
    }
  // den den den
  if(analogRead(CBL) < LTB && analogRead(CBC) < CTB && analogRead(CBR) < RTB){
    DONGCO(0,0);
    }
}
void Caidat(){
  // cập nhật giá trị vào các biến lưu
  L = analogRead(CBL);
  C = analogRead(CBC);
  R = analogRead(CBR);
  // lấy max - min.
  if(L > L1){L1 = L;}
  if(L < L2){L2 = L;}
  if(C > C1){C1 = C;}
  if(C < C2){C2 = C;}
  if(R > R1){R1 = R;}
  if(R < R2){R2 = R;}
  // tính trung bình
  LTB = (L1 + L2)/2;
  CTB = (C1 + C2)/2;
  RTB = (R1 + R2)/2;
  // in lên LCD
  lcd.setCursor(0,0);
  lcd.print("CBL");
  lcd.setCursor(0,1);
  lcd.print(analogRead(LTB));
  lcd.setCursor(4,0);
  lcd.print("CBC");
  lcd.setCursor(4,1);
  lcd.print(analogRead(CTB));
  lcd.setCursor(8,0);
  lcd.print("CBR");
  lcd.setCursor(8,1);
  lcd.print(analogRead(RTB));
  }
// chương trình 2 động cơ
void DONGCO(int pL, int pR){
  MotoL(pL);
  MotoR(pR);
  }
// chương trình con cho động cơ bên trái
void MotoL(int pwm){
  if(pwm >= 0){
    digitalWrite(DL,0);
    analogWrite (PL,pwm);
    }
  if(pwm < 0){
    digitalWrite(DL,1);
    analogWrite (PL,255 + pwm);
    }  
  }
void MotoR(int pwm){
  if(pwm >= 0){
    digitalWrite(DR,0);
    analogWrite (PR,pwm);
    }
  if(pwm < 0){
    digitalWrite(DR,1);
    analogWrite (PR,255 + pwm);
    }  
  }
