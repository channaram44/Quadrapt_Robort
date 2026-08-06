#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiS3.h>

//================ OLED =================//
Adafruit_SSD1306 display(128, 64, &Wire, -1);

//================ WIFI =================//
const char* ssid = "Quadruped_Robot";
const char* password = "12345678";

WiFiServer server(80);

//================ SERVOS =================//
Servo servoB1, servoB2, servoB3, servoB4;
Servo servoH1, servoH2, servoH3, servoH4;
Servo servoKN1, servoKN2, servoKN3, servoKN4;

//================ PINS =================//
const int servoB1pin = 2;
const int servoB2pin = 3;
const int servoB3pin = 4;
const int servoB4pin = 5;

const int servoH1Pin = 6;
const int servoH2Pin = 7;
const int servoH3Pin = 8;
const int servoH4Pin = 9;

const int servoKN1Pin = 10;
const int servoKN2Pin = 11;
const int servoKN3Pin = 12;
const int servoKN4Pin = 13;

//================ ROBOT STATE =================//
String currentAction = "CENTER";

//================ OLED =================//
void updateOLED(String action)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.println("Quadruped Robot");
  display.println("----------------");
 

  display.print("Action: ");
  display.println(action);

  display.display();
}

//================ CENTER =================//
void CenterPose()
{
  servoB1.write(90);
  servoB2.write(90);
  servoB3.write(90);
  servoB4.write(90);

  servoH1.write(90);
  servoH2.write(90);
  servoH3.write(90);
  servoH4.write(90);

  servoKN1.write(90);
  servoKN2.write(90);
  servoKN3.write(90);
  servoKN4.write(90);
}

//=================================================
// SIT
//=================================================
void Sit() {
  for (int i = 90; i >= 0; i--) {
    servoH2.write(i);
    servoH3.write(i);

    servoKN2.write(constrain(i - 45, 0, 180));
    servoKN3.write(constrain(i - 45, 0, 180));

    servoH1.write(180 - i);
    servoH4.write(180 - i);
    
    servoKN1.write(constrain(230 - i, 0, 180));
    servoKN4.write(constrain(230 - i, 0, 180));

    delay(80);
  }
}

//=================================================
// STAND
//=================================================
void Stand() {
  for (int i = 0; i <= 90; i++) {
    servoH2.write(i);
    servoH3.write(i);

    servoKN2.write(constrain(i - 45, 0, 180));
    servoKN3.write(constrain(i - 45, 0, 180));

    servoH1.write(180 - i);
    servoH4.write(180 - i);
    
    servoKN1.write(constrain(230 - i, 0, 180));
    servoKN4.write(constrain(230 - i, 0, 180));

    delay(50);
  }
}
/**************** walk Forward ******************/
void walkForward() {
  // Repeat walking cycle
  for (int step = 0; step < 10; step++) {
    //---------------- STEP 1 ----------------//
    for (int i = 90; i >= 70; i--) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    // Lift Legs 1 & 4
    for (int k = 90; k >= 70; k--) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    // Lower Legs 1 & 4
    for (int k = 70; k <= 90; k++) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    //---------------- STEP 2 ----------------//
    for (int i = 70; i <= 110; i++) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    // Lift Legs 2 & 3
    for (int k = 90; k >= 70; k--) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }
    //---------------- Return Center ----------------//
    for (int i = 110; i >= 90; i--) {
      servoH1.write(i);
      servoH3.write(i);

      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }
  }

  delay(30);
}
  /**************** BACKWARD ****************/
void walkBackward() {

  for (int step = 0; step < 10; step++) {

    //---------------- STEP 1 : Shift Hips ----------------//
    for (int i = 90; i <= 110; i++) {
      servoH1.write(i);
      servoH3.write(i);

      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    //---------------- Lift Legs 1 & 3 ----------------//
    for (int k = 90; k <= 110; k++) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    //---------------- Lower Legs 1 & 3 ----------------//
    for (int k = 110; k >= 90; k--) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    //---------------- STEP 2 : Shift Hips ----------------//
    for (int i = 110; i >= 70; i--) {
      servoH1.write(i);
      servoH3.write(i);

      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    //---------------- Lift Legs 2 & 4 ----------------//
    for (int k = 90; k <= 110; k++) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }

    //---------------- Lower Legs 2 & 4 ----------------//
    for (int k = 110; k >= 90; k--) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }

    //---------------- Return Center ----------------//
    for (int i = 70; i <= 90; i++) {
      servoH1.write(i);
      servoH3.write(i);

      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }
  }

  delay(30);
}
  void Rightmove() {
  for (int step = 0; step < 5; step++) {

    for (int i = 70; i <= 110; i++) {
      servoB1.write(90);
      servoB3.write(i);
      servoKN2.write(i);
      servoB2.write(180 - i);
      servoB4.write(90);

      delay(50);
    }

    for (int i = 110; i >= 70; i--) {
      servoB1.write(90);
      servoB3.write(i);
      servoKN2.write(i);
      servoB2.write(180 - i);
      servoB4.write(90);

      delay(50);
    }
  }

void Leftmove() {
  for (int step = 0; step < 5; step++) {

    for (int i = 110; i >= 70; i--) {
      servoB3.write(90);
      servoB1.write(i);
      servoKN4.write(i);
      servoB4.write(180 - i);
      servoB2.write(90);

      delay(80);
    }

    for (int i = 70; i <= 110; i++) {
      servoB3.write(90);
      servoB1.write(i);
      servoKN1.write(i);
      servoB4.write(180 - i);
      servoB2.write(90);

      delay(80);
    }
  }
}
    void Handshake() {
      servoB2.write(120);
      servoB3.write(60);
      servoB4.write(90);

      servoH1.write(80);
      servoH2.write(150);
      servoH3.write(130);
      servoH4.write(80);

      servoKN1.write(90);
      servoKN3.write(90);
      servoKN4.write(90);

      for (int i = 0; i < 10; i++) {
        servoB1.write(70);
        delay(300);

        servoB1.write(90);
        delay(300);

        servoKN2.write(40);
        delay(200);

        servoKN2.write(70);
        delay(200);
      }

      CenterPose();
      updateOLED("CENTER");
    }
//================ WEB PAGE =================//
void sendWebPage(WiFiClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type:text/html");
  client.println();

  client.println("<html><body>");
  client.println("<h1>Quadruped Robot</h1>");

  client.println("<a href='/FORWARD'><button>FORWARD</button></a><br><br>");
  client.println("<a href='/BACKWARD'><button>BACKWARD</button></a><br><br>");
  client.println("<a href='/LEFT'><button>LEFT</button></a><br><br>");
  client.println("<a href='/RIGHT'><button>RIGHT</button></a><br><br>");
  client.println("<a href='/SIT'><button>SIT</button></a><br><br>");
  client.println("<a href='/STAND'><button>STAND</button></a><br><br>");
  client.println("<a href='/HANDSHAKE'><button>HANDSHAKE</button></a><br><br>");
  client.println("<a href='/CENTER'><button>CENTER</button></a><br><br>");

  client.println("</body></html>");
}

//================ SETUP =================//
void setup()
{
  Serial.begin(115200);

  servoB1.attach(servoB1pin);
  servoB2.attach(servoB2pin);
  servoB3.attach(servoB3pin);
  servoB4.attach(servoB4pin);

  servoH1.attach(servoH1Pin);
  servoH2.attach(servoH2Pin);
  servoH3.attach(servoH3Pin);
  servoH4.attach(servoH4Pin);

  servoKN1.attach(servoKN1Pin);
  servoKN2.attach(servoKN2Pin);
  servoKN3.attach(servoKN3Pin);
  servoKN4.attach(servoKN4Pin);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  CenterPose();
  updateOLED("READY");

  WiFi.beginAP(ssid, password);

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");
 updateOLED(ip.toString());

  server.begin();
}

//================ LOOP =================//
void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    String req = client.readStringUntil('\r');

    if(req.indexOf("/FORWARD") >= 0)
    {
      updateOLED("FORWARD");
      walkForward();
    }

    if(req.indexOf("/BACKWARD") >= 0)
    {
      updateOLED("BACKWARD");
      walkBackward();
    }

    if(req.indexOf("/LEFT") >= 0)
    {
      updateOLED("LEFT");
      Leftmove();
    }

    if(req.indexOf("/RIGHT") >= 0)
    {
      updateOLED("RIGHT");
      Rightmove();
    }

    if(req.indexOf("/SIT") >= 0)
    {
      updateOLED("SIT");
      Sit();
    }

    if(req.indexOf("/STAND") >= 0)
    {
      updateOLED("STAND");
      Stand();
    }

    if(req.indexOf("/HANDSHAKE") >= 0)
    {
      updateOLED("HANDSHAKE");
      Handshake();
    }

    if(req.indexOf("/CENTER") >= 0)
    {
      updateOLED("CENTER");
      CenterPose();
    }

    sendWebPage(client);

    delay(1);
    client.stop();
  }
}