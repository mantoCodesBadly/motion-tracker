#include <hidboot.h>
#include <usbhub.h>

int Xmovement = 0;
int Ymovement = 0;

class MouseRptParser : public MouseReportParser
{
protected:
    void OnMouseMove(MOUSEINFO *mi);
    void OnLeftButtonUp(MOUSEINFO *mi);
    void OnLeftButtonDown(MOUSEINFO *mi);
    void OnRightButtonUp(MOUSEINFO *mi);
    void OnRightButtonDown(MOUSEINFO *mi);
    void OnMiddleButtonUp(MOUSEINFO *mi);
    void OnMiddleButtonDown(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
    Xmovement = mi->dX;
    Ymovement = mi->dY;
};
void MouseRptParser::OnLeftButtonUp(MOUSEINFO *mi){};
void MouseRptParser::OnLeftButtonDown(MOUSEINFO *mi){};
void MouseRptParser::OnRightButtonUp(MOUSEINFO *mi){};
void MouseRptParser::OnRightButtonDown(MOUSEINFO *mi){};
void MouseRptParser::OnMiddleButtonUp(MOUSEINFO *mi){};
void MouseRptParser::OnMiddleButtonDown(MOUSEINFO *mi){};

USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);
MouseRptParser Prs;

void setup()
{
    Serial.begin(9600);
    Serial.print("");

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    delay(200);

    HidMouse.SetReportParser(0, &Prs);
}

void loop()
{
    Usb.Task();

    // rileva a 100Hz circa
    delay(10);

    Serial.print(Xmovement);
    Serial.print(",");
    Serial.println(-Ymovement);

    Xmovement = 0;
    Ymovement = 0;
}
