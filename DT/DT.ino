#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <StringTokenizer.h>


MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "iAstra";
const char* password = "singhisking";

//const char* ssid = "Ajio_Test";
//const char* password = "7411199997";

//const char* ssid = "JioFi2_7A843F";
//const char* password = "ubsm2is44s";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 0;
int gpio2_pin = 2;
int currGpio0=0;
int currGpio2=0;

void setup(void){
 webPage += "<h1>My Home</h1><p><a href=\"ledArgs?LED0=1\"><button>Button1 ON</button></a>&nbsp;<a href=\"ledArgs?LED0=0\"><button>Button1 OFF</button></a>&nbsp;</p>";
  webPage += "<a href=\"ledArgs?LED2=1\"><button>Button2 ON</button></a>&nbsp;<a href=\"ledArgs?LED2=0\"><button>Button2 OFF</button></a></p>";
    
  // preparing GPIOs
  pinMode(gpio0_pin,OUTPUT);
  digitalWrite(gpio0_pin, 0);
 // pinMode(gpio2_pin, OUTPUT);
  //digitalWrite(gpio2_pin, 0);
  
  delay(1000);
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA); 
  //WiFi.mode(WIFI_AP); 
  //WiFi.mode(WIFI_AP_STA); 
  Serial.print("Entering SSID,Password");
  WiFi.begin(ssid, password);
  Serial.println("Done.");

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
}
 
void loop(void){ 
 server.handleClient();
} 
void handleSubmit() {
  // Actualise le GPIO / Update GPIO 
  int C1LED0,C2LED2;
  String sC1LED0,sC2LED2;
  
  sC1LED0 = server.arg("LED0");
  sC2LED2 = server.arg("LED2");
    
  if(sC1LED0!="")
  {
     C1LED0 = sC1LED0.toInt();
     digitalWrite(gpio0_pin, C1LED0);   
     }
  
  if(sC2LED2!="")
  {
      C2LED2 = sC2LED2.toInt();
      digitalWrite(gpio2_pin, C2LED2);
    }
  server.send(200, "text/html", webPage);
  }

