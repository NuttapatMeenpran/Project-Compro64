#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo ServoMotor;
int position =0;
int Servoposition =90;
const byte rows =4;
const byte cols =4;
char pass[6];
char unlock[6];
char keys[rows][cols]= {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {13,12,11,10};
byte colPins[cols] = {9,8,7,6};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols);
char key;
void setup()
{
  ServoMotor.attach(3);
  lcd.init();
  lcd.backlight();
}
void loop()
{
  if(Servoposition==90&&position==0){
    do{
      position=0;
      lcd.setCursor(0,0);
      lcd.print("Press Enter ");
      lcd.setCursor(0,1);
      lcd.print("Anykey to Lock");
    }while(keypad.getKey()==NO_KEY);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SetPassword 6DIT");
    while(position<6){
      lcd.setCursor(position,1);
      key = keypad.getKey();
      if (key != NO_KEY){
        pass[position]=key;
        lcd.print("*");
        position ++;
      }
    }
    Servoposition = 10;
  }
  ServoMotor.write(Servoposition);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Password");
  if (Servoposition == 10){
    int num =0;
    while(num<6){
      lcd.setCursor(num,1);
      key = keypad.getKey();
      if (key != NO_KEY){
        unlock[num]=key;
        lcd.print("*");
        num++;
      }
    }
    int chk=0;
    while(chk<6){
      if(unlock[chk]==pass[chk]){
        chk++;
      }
      else{
        num=0;
        chk=7;
        Servoposition=10;
        lcd.clear();
        lcd.print("ERROR");
        delay(1000);
        lcd.clear();
      }
    }
    if(chk==6){
      Servoposition = 90;
      ServoMotor.write(Servoposition);
      position = 0;
    }
  }
}