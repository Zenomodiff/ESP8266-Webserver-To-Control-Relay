/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 12:28 AM - date 10 june 2021
 * Github Link :-- https://github.com/Zenomodiff/ESP8266-Webserver-To-Control-Relay
 */

#include <ESP8266WiFi.h>

const char* ssid     = "PASTE THE WIFI NAME";
const char* password = "PASTE THE WIFI PASSWORD";

WiFiServer server(80);

String header;

String output5State = "off";
String output4State = "off";
String output0State = "off";
String output2State = "off";
String output14State = "off";
String output12State = "off";
String output13State = "off";

const int output5 = 5;
const int output4 = 4;
const int output0 = 0;
const int output2 = 2;
const int output14 = 14;
const int output12 = 12;
const int output13 = 13;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);  

  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output13, LOW);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){

  WiFiClient client = server.available(); 

  if (client) {                         
    Serial.println("New Client.");      
    String currentLine = "";              
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();         
      if (client.available()) {          
        char c = client.read();            
        Serial.write(c);               
        header += c;
        if (c == '\n') 
        {                  
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);  
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }  else  if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW); //here
            }else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            }  else  if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } 
            else  if (header.indexOf("GET /13/on") >= 0)
            {
              Serial.println("GPIO 0 on");
              Serial.println("GPIO 2 on");
              Serial.println("GPIO 4 on");
              Serial.println("GPIO 5 on");
              Serial.println("GPIO 12 on");
              Serial.println("GPIO 14 on");
              
              output0State = "on";
              output2State = "on";
              output4State = "on";
              output5State = "on";
              output12State = "on";
              output14State = "on";
              output13State = "on";

              digitalWrite(output0, HIGH);
              digitalWrite(output2, HIGH);
              digitalWrite(output4, HIGH);
              digitalWrite(output5, HIGH);
              digitalWrite(output12, HIGH);
              digitalWrite(output14, HIGH);
            } 
            else if (header.indexOf("GET /13/off") >= 0)
            {
              Serial.println("GPIO 0 off");
              Serial.println("GPIO 2 off");
              Serial.println("GPIO 4 off");
              Serial.println("GPIO 5 off");
              Serial.println("GPIO 12 off");
              Serial.println("GPIO 14 off");

              output0State = "off";
              output2State = "off";
              output4State = "off";
              output5State = "off";
              output12State = "off";
              output14State = "off";
              output13State = "off";
              
              digitalWrite(output0, LOW);
              digitalWrite(output2, LOW);
              digitalWrite(output4, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output12, LOW);
              digitalWrite(output14, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            client.println("<style>html { font-family: verdana; display: inline-block; margin: 0px auto; text-align: center;}");    
            client.println(".button { background-color: #D26429; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #68625E;}</style></head>");
            

            client.println("<body><h1>Zeno Modiff ESP8266 Web Server</h1>");
            
            client.println("<p>GPIO 0 - State " + output0State + "</p>");
     
            if (output0State=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
                 
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
      
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

               client.println("<p>GPIO 4 - State " + output4State + "</p>");
      
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

              client.println("<p>GPIO 5 - State " + output5State + "</p>");
      
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

              client.println("<p>GPIO 12 - State " + output12State + "</p>");
     
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

               client.println("<p>GPIO 14 - State " + output14State + "</p>");
               
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

             client.println("<p>" + output13State + "</p>");
               
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">All ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">All OFF</button></a></p>");
            }
            client.println("</body></html>");
          
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;    
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
