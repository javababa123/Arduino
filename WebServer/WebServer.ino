#include<SoftwareSerial.h>
SoftwareSerial client(0,1); //RX, TX
String webpage="";
int i=0,k=0;
String readString;
int x=0;
boolean No_IP=false;
String IP="";
char temp1='0';
String name="<p>Circuit Digest</p>";   //22
String dat="<p>Data Received Successfully.....</p>";     //21
     
void check4IP(int t1)
{
 
  int t2=millis();
  while(t2+t1>millis())
  {
    while(client.available()>0)
    {
      if(client.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}
void get_ip()
{
  IP="";
  char ch=0;
  
 Serial.print(".");
  while(1)
  {
    Serial.print("..");
    client.println("AT+CIFSR");
    
    
    while(client.available()>0)
    {
      Serial.print("...");
      client.println("AT+CIFSR");
   
      if(client.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while(client.available()>0)
        {
          ch=client.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    
    if(ch=='+')
    break;
    delay(1000);
    
  }
  Serial.println(IP);
  
  delay(20000);
  Serial.print("Port:");
  Serial.println(80);
}
void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    client.println(cmd); 
    while(client.available())
    {
      if(client.find("OK"))
      i=8;
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8)
  Serial.println("OK");
  else
  Serial.println("Error");
}
void wifi_init()
{
      connect_wifi("AT",100);
      connect_wifi("AT+CWMODE=3",100);
      connect_wifi("AT+CWQAP",100); 
      connect_wifi("AT+RST",5000);
      check4IP(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        //connect_wifi("AT+CWJAP=\"Ajio_Test\",\"7411199997\"",7000);         //provide your WiFi username and password here
        connect_wifi("AT+CWJAP=\"JioFi2_7A843F\",\"ubsm2is44s\"",7000);         //provide your WiFi username and password here
   
     // connect_wifi("AT+CWJAP=\"vpn address\",\"wireless network\"",7000);
      }
      else
        {
        }
      Serial.println("Wifi Connected"); 
      get_ip();
      
      connect_wifi("AT+CIPMUX=1",100);
      connect_wifi("AT+CIPSERVER=1,80",100);
}
void sendwebdata(String webPage)
{
    int ii=0;
     while(1)
     {
      unsigned int l=webPage.length();
      Serial.print("AT+CIPSEND=0,");
      client.print("AT+CIPSEND=0,");
      Serial.println(l+2);
      client.println(l+2);
      delay(100);
      Serial.println(webPage);
      client.println(webPage);
      while(client.available())
      {
        //Serial.print(Serial.read());
        if(client.find("OK"))
        {
          ii=11;
          break;
        }
      }
      if(ii==11)
      break;
      delay(100);
     }
}

void test()
{
    if (client.available()) {
    while(client.available())
    {
      Serial.write(client.read());
    }
  }
  if (Serial.available()) {
    delay(1000);
    String command="";

    while(Serial.available())
    {
    command+=(char)Serial.read();  
    }
    client.println(command);
  }
}

void setup() 
{
   Serial.begin(115200);
   client.begin(115200);   
   wifi_init();
   Serial.println("System Ready..");
}
void loop() 
{
    
//   test(); 
  k=0;
  Serial.println("Please Refresh your Page");
  while(k<1000)
  {
    k++;
    Serial.print("loop1:"+k);
   
   while(client.available())
   {
    Serial.print("loop2:"+k);
   
    if(client.find("0,CONNECT"))
    {
      Serial.println("Start Printing");
      Send();
      Serial.println("Done Printing");
      delay(1000);
    }
  }
  delay(1);
 }
}
void Send()
{
      webpage = "<h1>Welcome to Circuit Digest</h1><body bgcolor=f0f0f0>";
      sendwebdata(webpage);
      webpage=name;
      webpage+=dat;
      sendwebdata(webpage);
      delay(1000);
     webpage = "<a href=http://circuitdigest.com/";
     webpage+=">Click Here for More projects</a>";
     webpage+="Data Updated:"+k;
     
     sendwebdata(webpage);
     client.println("AT+CIPCLOSE=0"); 
}
