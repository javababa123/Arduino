#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <StringTokenizer.h>
#include <Adafruit_NeoPixel.h>

#define PIN            0
#define NUMPIXELS      10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second
MDNSResponder mdns;

// Replace with your network credentials
//const char* ssid = "iAstra";
//const char* password = "singhisking";

//const char* ssid = "Ajio_Test";
//const char* password = "7411199997";

const char* ssid = "JioFi2_7A843F";
const char* password = "ubsm2is44s";

ESP8266WebServer server(80);

String webPage = "";
int gpio0_pin = 0;

void setup(void){
 webPage += "<h1>ESP8266 Web Server</h1><p>User v028 #1 <a href=\"ledArgs?LED0=0&RED=0&GREEN=0&BLUE=128\"><button>1</button></a>&nbsp;<a href=\"ledArgs?LED0=1&RED=0&GREEN=0&BLUE=128\"><button>2</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=2&RED=0&GREEN=0&BLUE=128\"><button>3</button></a>&nbsp;<a href=\"ledArgs?LED0=3&RED=0&GREEN=0&BLUE=128\"><button>4</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=4&RED=0&GREEN=0&BLUE=128\"><button>5</button></a>&nbsp;<a href=\"ledArgs?LED0=5&RED=0&GREEN=0&BLUE=128\"><button>6</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=6&RED=0&GREEN=0&BLUE=128\"><button>7</button></a>&nbsp;<a href=\"ledArgs?LED0=7&RED=0&GREEN=0&BLUE=128\"><button>8</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=8&RED=0&GREEN=0&BLUE=128\"><button>9</button></a>&nbsp;<a href=\"ledArgs?LED0=9&RED=0&GREEN=0&BLUE=128\"><button>10</button></a></p>";

 webPage += "User v029 #2 <a href=\"ledArgs?LED0=0&RED=0&GREEN=128&BLUE=0\"><button>1</button></a>&nbsp;<a href=\"ledArgs?LED0=1&RED=0&GREEN=128&BLUE=0\"><button>2</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=2&RED=0&GREEN=128&BLUE=0\"><button>3</button></a>&nbsp;<a href=\"ledArgs?LED0=3&RED=0&GREEN=128&BLUE=0\"><button>4</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=4&RED=0&GREEN=128&BLUE=0\"><button>5</button></a>&nbsp;<a href=\"ledArgs?LED0=5&RED=0&GREEN=128&BLUE=0\"><button>6</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=6&RED=0&GREEN=128&BLUE=0\"><button>7</button></a>&nbsp;<a href=\"ledArgs?LED0=7&RED=0&GREEN=128&BLUE=0\"><button>8</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED0=8&RED=0&GREEN=128&BLUE=0\"><button>9</button></a>&nbsp;<a href=\"ledArgs?LED0=9&RED=0&GREEN=128&BLUE=0\"><button>10</button></a>";

  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, 0);
  delay(1000);
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA); 
  //WiFi.mode(WIFI_AP); 
  //WiFi.mode(WIFI_AP_STA); 
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
 // WiFi.softAP("Jio_Put_To_Light", "ranveer1992");  //Start HOTspot removing password will disable security

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Configuring access point...");

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on ( "/ledArgs", handleSubmit );
  server.begin();
  Serial.println("HTTP server started");
  pixels.begin(); // This initializes the NeoPixel library.
  for(int i=0;i<NUMPIXELS;i++){
  pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright red color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  
}
 
void loop(void){ 
 server.handleClient();
} 

void handleSubmit() {
  // Actualise le GPIO / Update GPIO 
  String sSORT,sLED0,sLED1,sLED2,sLED3,sLED4,sRed,sGreen,sBlue;  
  sSORT = server.arg("SORTCOMPLETED");
  sLED0 = server.arg("LED0");
  sLED1 = server.arg("LED1");
  sLED2 = server.arg("LED2");
  sLED3 = server.arg("LED3");
  sLED4 = server.arg("LED4");
  sRed = server.arg("RED");
  sGreen = server.arg("GREEN");
  sBlue = server.arg("BLUE");
  if(sSORT=="Y")
  {
  if(sLED0!="")
  {
  pixels.setPixelColor(sLED0.toInt(), pixels.Color(125,0,0)); // Moderately bright red color.
  }
   if(sLED1!="")
  {
  pixels.setPixelColor(sLED1.toInt(), pixels.Color(125,0,0)); // Moderately bright red color.
  }
   if(sLED2!="")
  {
  pixels.setPixelColor(sLED2.toInt(), pixels.Color(125,0,0)); // Moderately bright red color.
  }
   if(sLED3!="")
  {
  pixels.setPixelColor(sLED3.toInt(), pixels.Color(125,0,0)); // Moderately bright red color.
  }
   if(sLED4!="")
  {
  pixels.setPixelColor(sLED4.toInt(), pixels.Color(125,0,0)); // Moderately bright red color.
  }
  }else{
  pixels.setPixelColor(sLED0.toInt(), pixels.Color(sRed.toInt(),sGreen.toInt(),sBlue.toInt())); 
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  server.send(200, "text/html", webPage);
    
  }

