#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <StringTokenizer.h>


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
int gpio2_pin = 2;
int gpio4_pin = 4;
int gpio5_pin = 5;
int gpio12_pin = 12;
int gpio13_pin = 13;
int gpio14_pin = 14;
int gpio15_pin =15;
int gpio16_pin = 16;

void setup(void){
 webPage += "<h1>ESP8266 Web Server</h1><p>User v028 #1 <a href=\"ledArgs?LED5=1&LED4=0&LED2=0&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>1</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=1&LED2=0&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>2</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED5=1&LED4=1&LED2=0&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>3</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=0&LED2=0&LED0=1&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>4</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED5=1&LED4=0&LED2=0&LED0=1&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>5</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=1&LED2=0&LED0=1&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>6</button></a></p>";
  webPage += "User v029 #2 <a href=\"ledArgs?LED5=0&LED4=0&LED2=1&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=0\"><button>1</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=0&LED2=0&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=1\"><button>2</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED5=0&LED4=0&LED2=1&LED0=0&LED12=0&LED13=0&LED14=0&LED16=0&LED15=1\"><button>3</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=0&LED2=0&LED0=0&LED12=0&LED13=1&LED14=0&LED16=0&LED15=0\"><button>4</button></a>&nbsp;";
  webPage += "<a href=\"ledArgs?LED5=0&LED4=0&LED2=1&LED0=0&LED12=0&LED13=1&LED14=0&LED16=0&LED15=0\"><button>5</button></a>&nbsp;<a href=\"ledArgs?LED5=0&LED4=0&LED2=0&LED0=0&LED12=0&LED13=1&LED14=0&LED16=0&LED15=1\"><button>6</button></a></p>";
  webPage += "<p><a href=\"ledArgs?LED5=0&LED4=0&LED0=0\"><button>OFF v028</button></a>&nbsp;<a href=\"ledArgs?LED2=0&LED13=0&LED15=0\"><button>OFF v029</button></a></p>";
    
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, 0);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, 0);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, 0);
  pinMode(gpio5_pin, OUTPUT);
  digitalWrite(gpio5_pin, 0);
   pinMode(gpio12_pin, OUTPUT);
  digitalWrite(gpio12_pin, 0);
   pinMode(gpio13_pin, OUTPUT);
  digitalWrite(gpio13_pin, 0);
   pinMode(gpio14_pin, OUTPUT);
  digitalWrite(gpio14_pin, 0);
   pinMode(gpio15_pin, OUTPUT);
  digitalWrite(gpio15_pin, 0);
   pinMode(gpio16_pin, OUTPUT);
  digitalWrite(gpio16_pin, 0);
  
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
}
 
void loop(void){ 
 server.handleClient();
} 

void handleSubmit() {
  // Actualise le GPIO / Update GPIO 
  int C1LED5,C1LED4,C1LED0,C2LED2,C2LED15,C2LED13,C3LED12,C3LED14,C3LED16;
  String sC1LED5,sC1LED4,sC1LED0,sC2LED2,sC2LED15,sC2LED13,sC3LED12,sC3LED14,sC3LED16;
  
  sC1LED5 = server.arg("LED5");  
  sC1LED4 = server.arg("LED4");
  sC1LED0 = server.arg("LED0");
  sC2LED15 = server.arg("LED15");
  sC2LED2 = server.arg("LED2");
  sC2LED13 = server.arg("LED13");
  sC3LED12 = server.arg("LED12");
  sC3LED14 = server.arg("LED14");
  sC3LED16 = server.arg("LED16");
  
  if(sC1LED5!="")
  {
     C1LED5 = sC1LED5.toInt();
    digitalWrite(gpio5_pin, C1LED5);
  }
  
  if(sC1LED4!="")
  {
     C1LED4 = sC1LED4.toInt();
   digitalWrite(gpio4_pin, C1LED4);
   
  }
  
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
  if(sC2LED15!="")
  {
     C2LED15 = sC2LED15.toInt();
   digitalWrite(gpio15_pin, C2LED15);
   }
  
if(sC2LED13!="")
  {
     C2LED13 = sC2LED13.toInt();
   digitalWrite(gpio13_pin,C2LED13);
   }
   
  if(sC3LED12!="")
  {
     C3LED12 = sC3LED12.toInt();
   digitalWrite(gpio12_pin,C3LED12);
  }
  if(sC3LED14!="")
  {
   C3LED14 = sC3LED14.toInt();
   digitalWrite(gpio14_pin, C3LED14);   
  }
  if(sC3LED16!="")
  {
   C3LED16 = sC3LED16.toInt();
   digitalWrite(gpio16_pin, C3LED16);   
  }
 
  server.send(200, "text/html", webPage);
    
  }

