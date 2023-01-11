#include <HID.h>

#include <hid.h>                           //Add to Oleg Mazurov code to Bar Code Scanner
#include <hiduniversal.h>                  //Add to Oleg Mazurov code to Bar Code Scanner
#include <usbhub.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
////#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <hidboot.h>
#define DISPLAY_WIDTH 16
//#define BOTON 8
 #include "HX711.h"
 
// Pin de datos y de reloj
byte pinData = 5;
byte pinClk = 6;
 
 int green = 4;
int red = 7;

HX711 bascula;
float peso = 0;
float pesar = 0;
//long adc_lecture;

float factor_calibracion = 90000.1;
//initialize the LCD library with the numbers of the interface pins//

//LiquidCrystal lcd(7, 6, 5, 8, 3, 2);
////LiquidCrystal lcd(8, 9, 10, 11, 3, 2);
LiquidCrystal_I2C lcd(0x27,16,2);  
String Code="";
String Waffle = "5901234123457" , Cereal = "9788492808274" , Borra = "123456789012";
int i=0 , Eliminar = 1;
int Total = 0;
USB     Usb;
USBHub     Hub(&Usb);                                          //I enable this line
HIDUniversal      Hid(&Usb);                                  //Add this line so that the barcode scanner will be recognized, I use "Hid" below 
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    Keyboard(&Usb);


 
class KbdRptParser : public KeyboardReportParser
{
        void PrintKey(uint8_t mod, uint8_t key);             // Add this line to print character in ASCII
protected:
  virtual void OnKeyDown  (uint8_t mod, uint8_t key);
  virtual void OnKeyPressed(uint8_t key);
};
 
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)  
{
    uint8_t c = OemToAscii(mod, key);
 
    if (c)
        OnKeyPressed(c);
}
 
/* what to do when symbol arrives */
void KbdRptParser::OnKeyPressed(uint8_t key)  
{
static uint32_t next_time = 0;      //watchdog
static uint8_t current_cursor = 0;  //tracks current cursor position  

    if( millis() > next_time ) {
     lcd.clear();
      current_cursor = 0;
      delay( 5 );  //LCD-specific 
      lcd.setCursor( 0,0 );
    }//if( millis() > next_time ...
 
    next_time = millis() + 200;  //reset watchdog
 
    if( current_cursor++ == ( DISPLAY_WIDTH + 1 )) {  //switch to second line if cursor outside the screen
    lcd.setCursor( 0,1 );
    }

 
  Serial.print((char) key );      //Add char to print correct number in ASCII
//   lcd.init();
//   lcd.setCursor( 0,0 );
 //lcd.print( (char)key );          //Add char to print correct number in ASCII
// delay(5000);
// lcd.print("Hola Mundo");

   Code += (char)key;
    
    
    //Serial.print('\n');
    // Serial.print(Disco);
    // Serial.print('\n');
  if (Eliminar == 1)
  {
    pesar = bascula.get_units(10), 3;
    Serial.print("PESAR");
    Serial.print(pesar);

   // Serial.print("rojo");
  //digitalWrite(red, HIGH);
    if(Code == Waffle)
    {
      Serial.print('\n');
      Serial.print("Waffle");
      Serial.print('\n');
      Serial.print("Precio:$300");
      Serial.print('\n');
      Code ="";
      Total += 300;
      Serial.print("Total: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.print("Waffle");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$300");
      delay(3000);
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);


 delay(1000);
  Serial.print("Leyendo: ");
  Serial.print(bascula.get_units(10), 3);
  Serial.print(" kgs");
  //float peso;
  peso = bascula.get_units(10), 3;
  // adc_lecture = bascula.get_units(1);
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();
  Serial.print("peso: ");
  Serial.print(peso);


if(peso<=pesar){
  digitalWrite(green, LOW);
  Serial.print("rojo");
  digitalWrite(red, HIGH);
          delay(5000);
          //digitalWrite(red, LOW);
}else{
  digitalWrite(red, LOW);
  Serial.print("verde");
  digitalWrite(green, HIGH);
          delay(5000);
          //digitalWrite(green, LOW);
}

//      lcd.setCursor(0,0);
 //     lcd.print("Disco");
//      lcd.setCursor(0,1);
 //     lcd.print("Precio:$300");
//      delay(500);
//      lcd.setCursor(0,0);
//      lcd.print("Total de compra");
//      lcd.setCursor(0,1);
//      lcd.print("Tolta: $");
//      lcd.print(Total);
      
    }

    if(Code == Cereal)
    {
      Serial.print('\n');
      Serial.print("Cereal");
      Serial.print('\n');
      Serial.print("Precio:$100");
      Serial.print('\n');
      Code ="";
     Total += 100;
      Serial.print("Total de compra: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.print("Cereal");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$100");
      delay(3000);
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);


      delay(1000);
  Serial.print("Leyendo: ");
  Serial.print(bascula.get_units(10), 3);
  Serial.print(" kgs");
  //float peso;
  peso = bascula.get_units(10), 3;
  // adc_lecture = bascula.get_units(1);
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();
  Serial.print("peso: ");
  Serial.print(peso);


if(peso<=pesar){
  digitalWrite(green, LOW);
  Serial.print("rojo");
  digitalWrite(red, HIGH);
          delay(5000);
          //digitalWrite(red, LOW);
}else{
  digitalWrite(red, LOW);
  Serial.print("verde");
  digitalWrite(green, HIGH);
          delay(5000);
          //digitalWrite(green, LOW);
}
    }

  }
    /*if(Code == Borra)
    {
      Serial.print('\n');
      Total = Total*0;
      Serial.print("Total de compra: $");
      Serial.print(Total);
      Serial.print('\n');
      
      
      Code = "";
    } */

    //if(digitalRead(BOTON) == HIGH)
    
    if(Code == Borra)
     {
       if(Total > 0)
       {
         Eliminar = 0;
         Code = "";
       }
       else
       {
        lcd.clear();
        lcd.print("Sin productos");
       delay(3000);
      
       lcd.clear();
       lcd.print("Ingrese un producto");
       delay(3000);
       lcd.clear();
       Code="";
       }
     }


    if (Eliminar == 0)
    
  {
    

    lcd.print("Ingrese producto");
pesar = bascula.get_units(10), 3;
    Serial.print("PESAR");
    Serial.print(pesar);
    if(Code == Waffle)
    {
      lcd.clear();
        lcd.print("Waffle");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$300");
      delay(3000);
      lcd.clear();
      lcd.print("Prod. Eliminado");
      delay(3000);
      lcd.clear();
      Serial.print('\n');
      Serial.print("Waffle");
      Serial.print('\n');
      Serial.print("Precio:$300");
      Serial.print('\n');
      Code ="";
      Total -= 300;
      Serial.print("Total: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);
      Eliminar ++;


      
 delay(1000);
  Serial.print("Leyendo: ");
  Serial.print(bascula.get_units(10), 3);
  Serial.print(" kgs");
  //float peso;
  peso = bascula.get_units(1), 3;
  // adc_lecture = bascula.get_units(1);
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();
  Serial.print("peso: ");
  Serial.print(peso);


if(peso>=pesar){
  digitalWrite(green, LOW);
  Serial.print("rojo");
  digitalWrite(red, HIGH);
          delay(5000);
          //digitalWrite(red, LOW);
}else{
  digitalWrite(red, LOW);
  Serial.print("verde");
  digitalWrite(green, HIGH);
          delay(5000);
          //digitalWrite(green, LOW);
}

//      lcd.setCursor(0,0);
 //     lcd.print("Disco");
//      lcd.setCursor(0,1);
 //     lcd.print("Precio:$300");
//      delay(500);
//      lcd.setCursor(0,0);
//      lcd.print("Total de compra");
//      lcd.setCursor(0,1);
//      lcd.print("Tolta: $");
//      lcd.print(Total);
      
    }

    if(Code == Cereal)
    {
      lcd.clear();
      lcd.print("Cereal");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$100");
      delay(3000);
      lcd.clear();
      lcd.print("Prod. Eliminado");
      delay(3000);
      lcd.clear();
      Serial.print('\n');
      Serial.print("Cereal");
      Serial.print('\n');
      Serial.print("Precio:$100");
      Serial.print('\n');
      Code ="";
     Total -= 100;
      Serial.print("Total de compra: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);
      Eliminar ++;



      
 delay(1000);
  Serial.print("Leyendo: ");
  Serial.print(bascula.get_units(10), 3);
  Serial.print(" kgs");
  //float peso;
  peso = bascula.get_units(10), 3;
  // adc_lecture = bascula.get_units(1);
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();
  Serial.print("peso: ");
  Serial.print(peso);


if(peso>=pesar){
  digitalWrite(green, LOW);
  Serial.print("rojo");
  digitalWrite(red, HIGH);
          delay(5000);
          //digitalWrite(red, LOW);
}else{
  digitalWrite(red, LOW);
  Serial.print("verde");
  digitalWrite(green, HIGH);
          delay(5000);
          //digitalWrite(green, LOW);
}
    }

  }
  
    

  

};
 
KbdRptParser Prs;
 
void setup()
{
    Serial.begin( 9600 );
    //pinMode(BOTON, INPUT);
    Serial.println("LISTO");
    
    pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);


    if (Usb.Init() == -1) {
      Serial.println("OSC did not start.");
    }
 
    delay( 200 );
 
       Hid.SetReportParser(0, (HIDReportParser*)&Prs);        //Here I change  "Keyboard" for "Hid"
   //  set up the LCD's number of columns and rows: 
     //lcd.begin(DISPLAY_WIDTH, 2);
    lcd.init();
    
    // Paso 4
    lcd.backlight();
    
    // Paso 5
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.noAutoscroll();
     lcd.print("Listo");
     delay(3000);
    /* if(  Code == Disco){
       lcd.print("Disco");
     lcd.print("Precio:$300");
     }
  /*lcd.clear();
   lcd.print("Disco");
   lcd.print(Code);
    delay( 200 ); */
      
  Serial.println("HX711 programa de calibracion");
  Serial.println("Quita cualquier peso de la bascula");
  Serial.println("Una vez empiece a mostrar informacion de medidas, coloca un peso conocido encima de la bascula");
  Serial.println("Presiona + para incrementar el factor de calibracion");
  Serial.println("Presiona - para disminuir el factor de calibracion");
 
  // Iniciar sensor
  bascula.begin(pinData, pinClk);
 
  // Aplicar la calibración
  bascula.set_scale();
  // Iniciar la tara
  // No tiene que haber nada sobre el peso
  bascula.tare();
 
  // Obtener una lectura de referencia
  long zero_factor = bascula.read_average();
  // Mostrar la primera desviación
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);


     

}
 
void loop()
{
 
  Usb.Task();
 

 bascula.set_scale(factor_calibracion);
 //pesar = bascula.get_units(), 3;
// Serial.print("PESAR");
 //Serial.print(pesar);
 
  // Mostrar la información para ajustar el factor de calibración
  /*delay(3000);
  Serial.print("Leyendo: ");
  Serial.print(bascula.get_units(), 3);
  Serial.print(" kgs");
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();*/
 
}
  