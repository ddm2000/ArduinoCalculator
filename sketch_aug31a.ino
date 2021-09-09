#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <String.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);    //I2C address for PCF8574 is 0x20, lcd dimension is 16x2

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'7','8','9','/'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'c','0','=','+'},
};

byte rowPins[rows] = {0,1,2,3};
byte colPins[cols] = {4,5,6,7};

Keypad key(makeKeymap(keys),rowPins,colPins,rows,cols);

long int operation(long int a, long int b, char op)
{
  switch(op)
  {
    case '+':
      return a+b;
    case '-':
      return a-b;
    case 'x':
      return a*b;
    case '/':
      return a/b;
    default:
        return b;
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.init();    // initialize the lcd 
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  static String expr;
  static long int a,b;
  static char op;
  char keyVal = key.getKey();
  if(keyVal)
  {
    if(keyVal == 'c')
    {
      lcd.clear();
      expr = "";
      op = "";
      a = 0;
    }
    else if((keyVal=='+')||(keyVal=='-')||(keyVal=='x')||(keyVal=='/'))
    {
      a = expr.toInt();
      op = keyVal;
      lcd.clear();
      lcd.print(expr+op);
      expr = "";
    }
    else if(keyVal=='=')
    {
      b = expr.toInt();
      if((!b)&&(op=='/'))
      {
        lcd.clear();
        lcd.print("CANNOT DIVIDE");
        lcd.setCursor(0,1);
        lcd.print("BY ZERO");
      }
      else if(expr!="")
      {
        long int result = operation(a,b,op);
        String prevResult = String(result);
        lcd.setCursor(0,1);
        lcd.print(prevResult);
        expr = prevResult;
      }
      else
      {
        lcd.clear();
        lcd.print("INVALID");
      }
    }
    else
    {
      expr += keyVal;
      lcd.print(keyVal);
    }
  }
}
