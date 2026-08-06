#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

//====================================================
// Access Point Settings
//====================================================
const char* ap_ssid = "QuadrupedRobot";
const char* ap_password = "12345678";

WebServer server(80);

//====================================================
// Servo Objects
//====================================================

// Front Left
Servo FL_Hip1;
Servo FL_Hip2;
Servo FL_Knee;

// Front Right
Servo FR_Hip1;
Servo FR_Hip2;
Servo FR_Knee;

// Back Left
Servo BL_Hip1;
Servo BL_Hip2;
Servo BL_Knee;

// Back Right
Servo BR_Hip1;
Servo BR_Hip2;
Servo BR_Knee;

//====================================================
// Pin Mapping
//====================================================

// Leg 1 (Front Left)
#define FL_HIP1 4
#define FL_HIP2 16
#define FL_KNEE 15

// Leg 2 (Front Right)
#define FR_HIP1 5
#define FR_HIP2 3
#define FR_KNEE 2

// Leg 3 (Back Left)
#define BL_HIP1 6
#define BL_HIP2 12
#define BL_KNEE 11

// Leg 4 (Back Right)
#define BR_HIP1 7
#define BR_HIP2 8
#define BR_KNEE 9

//====================================================
// Stand Position
//====================================================
void standPosition()
{
  // Front Left
  FL_Hip1.write(120);
  FL_Hip2.write(120);
  FL_Knee.write(120);

  // Front Right
  FR_Hip1.write(120);
  FR_Hip2.write(120);
  FR_Knee.write(120);

  // Back Left
  BL_Hip1.write(120);
  BL_Hip2.write(120);
  BL_Knee.write(120);

  // Back Right
  BR_Hip1.write(120);
  BR_Hip2.write(120);
  BR_Knee.write(120);
}

//====================================================
// Sit Position
//====================================================
void sitPosition()
{
  // Front Left
  FL_Hip1.write(120);
  FL_Hip2.write(120);
  FL_Knee.write(45);

  // Front Right
  FR_Hip1.write(120);
  FR_Hip2.write(120);
  FR_Knee.write(45);

  // Back Left
  BL_Hip1.write(120);
  BL_Hip2.write(120);
  BL_Knee.write(45);

  // Back Right
  BR_Hip1.write(120);
  BR_Hip2.write(120);
  BR_Knee.write(45);
}

//====================================================
// Web Page
//====================================================
String htmlPage()
{
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Quadruped Robot</title>
<style>
body{
  text-align:center;
  font-family:Arial;
  margin-top:50px;
}
button{
  width:220px;
  height:80px;
  font-size:24px;
  margin:10px;
}
</style>
</head>
<body>

<h1>Quadruped Robot Control</h1>

<form action="/stand">
<button type="submit">STAND</button>
</form>

<form action="/sit">
<button type="submit">SIT</button>
</form>

</body>
</html>
)rawliteral";

  return page;
}

//====================================================
// Handlers
//====================================================
void handleRoot()
{
  server.send(200, "text/html", htmlPage());
}

void handleStand()
{
  standPosition();
  server.send(200, "text/html", htmlPage());
}

void handleSit()
{
  sitPosition();
  server.send(200, "text/html", htmlPage());
}

//====================================================
// Setup
//====================================================
void setup()
{
  Serial.begin(115200);

  // Attach Servos
  FL_Hip1.attach(FL_HIP1);
  FL_Hip2.attach(FL_HIP2);
  FL_Knee.attach(FL_KNEE);

  FR_Hip1.attach(FR_HIP1);
  FR_Hip2.attach(FR_HIP2);
  FR_Knee.attach(FR_KNEE);

  BL_Hip1.attach(BL_HIP1);
  BL_Hip2.attach(BL_HIP2);
  BL_Knee.attach(BL_KNEE);

  BR_Hip1.attach(BR_HIP1);
  BR_Hip2.attach(BR_HIP2);
  BR_Knee.attach(BR_KNEE);

  standPosition();

  // Start Access Point
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println();
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/stand", handleStand);
  server.on("/sit", handleSit);

  server.begin();
}

//====================================================
// Loop
//====================================================
void loop()
{
  server.handleClient();
}