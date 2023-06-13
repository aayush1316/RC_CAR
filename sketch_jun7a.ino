#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "TP-Link_F9FA";
const char* password = "96241411";
//remote
 #define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
// Motor control pins
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

AsyncWebServer server(80);

void setup() {
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);

  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String htmlPage = "<html><body>";
    htmlPage += "<h1>Remote Control Car</h1>";
    htmlPage += "<p><a href=\"/forward\"><button style=\"font-size:24px\">Forward</button></a></p>";
    htmlPage += "<p><a href=\"/backward\"><button style=\"font-size:24px\">Backward</button></a></p>";
    htmlPage += "<p><a href=\"/left\"><button style=\"font-size:24px\">Left</button></a>";
    htmlPage += " <a href=\"/right\"><button style=\"font-size:24px\">Right</button></a></p>";
    htmlPage += " <a href=\"/stop\"><button style=\"font-size:24px\">Stop</button></a></p>";
    htmlPage += "</body></html>";
    request->send(200, "text/html", htmlPage);
  });

  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, speedCar);
    delay(100);
    request->redirect("/stop");
  });

  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, speedCar);
    delay(100);
    request->redirect("/stop");
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
  
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, speedCar);
    delay(100);
    request->redirect("/stop");
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, speedCar);
    delay(100);
    request->redirect("/stop");
  });
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, speedCar);
    request->redirect("/");
  });
  server.begin();
}

void loop() {
  
}