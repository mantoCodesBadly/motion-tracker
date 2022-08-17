#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

int uppin = 4;
int downpin = 5;
int leftpin = 6;
int rightpin = 7;

int up = 0;
int down = 0;
int left = 0;
int right = 0;
int Xmovement = 0;
int Ymovement = 0;

void resetpins()
{
  digitalWrite(uppin, HIGH);
  digitalWrite(downpin, HIGH);
  digitalWrite(leftpin, HIGH);
  digitalWrite(rightpin, HIGH);
}

void neutral()
{
  // neutral
  up = 0;
  down = 0;
  left = 0;
  right = 0;  
}


class MouseRptParser : public MouseReportParser
{
  protected:
    void OnMouseMove	(MOUSEINFO *mi);
    void OnLeftButtonUp	(MOUSEINFO *mi);
    void OnLeftButtonDown	(MOUSEINFO *mi);
    void OnRightButtonUp	(MOUSEINFO *mi);
    void OnRightButtonDown	(MOUSEINFO *mi);
    void OnMiddleButtonUp	(MOUSEINFO *mi);
    void OnMiddleButtonDown	(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{

  Xmovement = mi->dX;

  Ymovement = mi->dY;
  
 
};
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)
{
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)
{
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)
{
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi)
{
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)
{
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi)
{
};



USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

MouseRptParser Prs;


void setup()
{
  Serial.begin( 9600 );
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidMouse.SetReportParser(0, &Prs);

  pinMode(uppin, OUTPUT);
  pinMode(downpin, OUTPUT);
  pinMode(leftpin, OUTPUT);
  pinMode(rightpin, OUTPUT);

  Serial.print("dX,dY");

  resetpins();

}

void loop()
{
  Usb.Task();
  //showpins();
  delay(20);
  Serial.print(Xmovement);
  Serial.print(",");
  Serial.println(Ymovement);
  Xmovement = 0;
  Ymovement = 0;
  resetpins();
}

/*void showpins()
{
  if (left)
  {
    digitalWrite(leftpin, LOW);
      left -=1;
  }

  if (right)
  {
    digitalWrite(rightpin, LOW);
      right -=1;
  }

  if (up)
  {
    digitalWrite(uppin, LOW);
      up -=1;
  }

  if (down)
  {
    digitalWrite(downpin, LOW);
      down -=1;
  }

}*/
