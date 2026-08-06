// ArduinoGraphics must be included BEFORE Arduino_LED_Matrix
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include <WiFiS3.h>

char ssid[] = "Telezer_J";
char pass[] = "Telezer12";

WiFiServer server(80);

const int ledPin = LED_BUILTIN;

ArduinoLEDMatrix matrix;

// Stores IP address as text
String ipString;

//---------------- LED Matrix ----------------//
void matrix_setup() {
  matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_5x7);
  matrix.textScrollSpeed(50);
  matrix.endDraw();
}

void displayText(const char *text) {
  matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);

  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);

  matrix.endDraw();
}

//---------------- Setup ----------------//
void setup() {

  Serial.begin(115200);

  matrix_setup();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to WiFi");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("Connected!");

  server.begin();

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");
  Serial.println(ip);

  ipString = ip.toString();      // Convert IP to text
}

//---------------- Loop ----------------//
void loop() {

  // Scroll the current IP address
  displayText(ipString.c_str());

  WiFiClient client = server.available();

  if (client) {

    Serial.println("New Client");

    String request = "";

    while (client.connected()) {

      if (client.available()) {

        char c = client.read();
        request += c;

        if (c == '\n') {

          if (request.indexOf("GET /ON") >= 0) {
            digitalWrite(ledPin, HIGH);
            Serial.println("LED ON");
          }

          if (request.indexOf("GET /OFF") >= 0) {
            digitalWrite(ledPin, LOW);
            Serial.println("LED OFF");
          }

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Arduino UNO R4 WiFi LED Control</title>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("</head>");

          client.println("<body style='text-align:center;font-family:Arial;'>");
          client.println("<h1>Arduino UNO R4 WiFi</h1>");
          client.println("<h2>Built-in LED Control</h2>");

          client.println("<p><a href=\"/ON\"><button style='width:150px;height:60px;font-size:20px;background:green;color:white;'>LED ON</button></a></p>");

          client.println("<p><a href=\"/OFF\"><button style='width:150px;height:60px;font-size:20px;background:red;color:white;'>LED OFF</button></a></p>");

          client.println("<p><b>IP Address:</b> ");
          client.println(ipString);
          client.println("</p>");

          client.println("</body>");
          client.println("</html>");

          break;
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected");
  }
}