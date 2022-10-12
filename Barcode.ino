#include <HID.h>

#include <hid.h>                           //Add to Oleg Mazurov code to Bar Code Scanner
#include <hiduniversal.h>                  //Add to Oleg Mazurov code to Bar Code Scanner
#include <usbhub.h>
//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <hidboot.h>
#define DISPLAY_WIDTH 16
 
//initialize the LCD library with the numbers of the interface pins//

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
// LiquidCrystal_I2C lcd(0x27,16,2);  
String Code="";
String Disco = "5901234123457" , Gel = "9788492808274" , Borra = "123456789012";
int i=0;
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

    if(Code == Disco)
    {
      Serial.print('\n');
      Serial.print("Disco");
      Serial.print('\n');
      Serial.print("Precio:$300");
      Serial.print('\n');
      Code ="";
      Total += 300;
      Serial.print("Total: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.print("Disco");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$300");
      delay(3000);
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);

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

    if(Code == Gel)
    {
      Serial.print('\n');
      Serial.print("Gel");
      Serial.print('\n');
      Serial.print("Precio:$100");
      Serial.print('\n');
      Code ="";
     Total += 100;
      Serial.print("Total de compra: $");
      Serial.print(Total);
      Serial.print('\n');
      lcd.print("Gel");
      delay(3000);
      lcd.clear();
      lcd.print("Precio:$100");
      delay(3000);
      lcd.clear();
      lcd.print("Total:");
      lcd.print(Total);
    }
    
    if(Code == Borra)
    {
      Serial.print('\n');
      Total = Total*0;
      Serial.print("Total de compra: $");
      Serial.print(Total);
      Serial.print('\n');
      
      
      Code = "";
    }
  
    

  

};
 
KbdRptParser Prs;
 
void setup()
{
    Serial.begin( 9600 );
    Serial.println("LISTO");
    


    if (Usb.Init() == -1) {
      Serial.println("OSC did not start.");
    }
 
    delay( 200 );
 
       Hid.SetReportParser(0, (HIDReportParser*)&Prs);        //Here I change  "Keyboard" for "Hid"
   //  set up the LCD's number of columns and rows: 
     lcd.begin(DISPLAY_WIDTH, 2);
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
    


     

}
 
void loop()
{
 
  Usb.Task();
 
 
}
