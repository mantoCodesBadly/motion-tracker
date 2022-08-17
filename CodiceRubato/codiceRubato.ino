#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

int firepin = 3;
int uppin = 4;
int downpin = 5;
int leftpin = 6;
int rightpin = 7;
int sensitivity =12;

bool fire = false;
bool sticky = false;
int up = 0;
int down = 0;
int left = 0;
int right = 0;
int Xmovement = 0;
int Ymovement = 0;

void resetpins()
{
  digitalWrite(firepin, HIGH);
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
  // left
  if (Xmovement < -sensitivity)
  {
      left = abs(Xmovement);
      right = 0;
      Serial.println("Left");
  }

  else if ((Xmovement < -sensitivity/2) && right)
  {
    left= 0;
    right=0;
  }

  // right
  if (Xmovement > sensitivity)
  {
    right = abs(Xmovement);
    left = 0;
    Serial.println("Right");
  }
  else if ((Xmovement > sensitivity/2) && left)
  {
    right=0;
    left = 0;
  }


  // down
  Ymovement = mi->dY;

  if (Ymovement > sensitivity)
  {
    down = abs(Ymovement);
    up = 0;
    Serial.println("Down alot");
  }
  else if ((Ymovement > sensitivity/2) && up)
  {
    up = 0;
    down = 0;
  }

  // up
  if (Ymovement < -sensitivity)
  {
    up = abs(Ymovement);
    down = 0;
    Serial.println("Up alot");
  }
  else if ((Ymovement < -sensitivity/2) && down)
  {
    up = 0;
    down = 0;
  }

};
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)
{
  Serial.println("L Butt Up");
  fire = false;
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)
{
  Serial.println("L Butt Dn");
  fire = true;
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)
{
  neutral();
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi)
{
  sticky =!sticky;
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)
{
  Serial.println("M Butt Up");
  fire = false;
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi)
{
  Serial.println("M Butt Dn");
  fire = true;
};



USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

MouseRptParser Prs;


void setup()
{
  Serial.begin( 115200 );
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidMouse.SetReportParser(0, &Prs);

  pinMode(firepin, OUTPUT);
  pinMode(uppin, OUTPUT);
  pinMode(downpin, OUTPUT);
  pinMode(leftpin, OUTPUT);
  pinMode(rightpin, OUTPUT);

  resetpins();

}

void loop()
{
  Usb.Task();
  showpins();
  delay(5);
  if (sticky)
  {
    delay(15);
  }
  resetpins();
}

void showpins()
{
  if (left)
  {
    digitalWrite(leftpin, LOW);
    if (!sticky)
    {
      left -=1;
    }
  }

  if (right)
  {
    digitalWrite(rightpin, LOW);
    if (!sticky)
    {
      right -=1;
    }
  }

  if (up)
  {
    digitalWrite(uppin, LOW);
    if (!sticky)
    {
      up -=1;
    }
  }

  if (down)
  {
    digitalWrite(downpin, LOW);
    if (!sticky)
    {
      down -=1;
    }
  }

  if (fire)
  {
    digitalWrite(firepin, LOW);
  }

}
