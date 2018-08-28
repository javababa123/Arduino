/*
  ESP8266 AWS IoT demo
  Simple demo code to provide static data into AWS IoT platform
  
  created   Mar 2017
  by CheapskateProjects
  ---------------------------
  The MIT License (MIT)
  Copyright (c) 2017 CheapskateProjects
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <ESP8266AWSImplementations.h>

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

const char* ssid = "iAstra";
const char* password = "singhisking";

void initWLAN()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
}

void initAWS()
{
  iotClient.setAWSRegion("us-east-2");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("aeq23tgrj7evg.iot.us-east-2.amazonaws.com");
  iotClient.setAWSPath("/things/testbulb/shadow");
  iotClient.setAWSKeyID("AKIAJCBE7FYMZFGSG4KQ");
  iotClient.setAWSSecretKey("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");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("begin");
  initWLAN();
  Serial.println("wlan initialized");
  initAWS();
  Serial.println("iot initialized");
}

void loop()
{
  char shadow[100];
  strcpy(shadow, "{\"state\":{\"reported\":{\"test_value1\":098723, \"test_value2\":342234}}}");
  
  Serial.println("Trying to send data");
  Serial.print(shadow);
  
  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);
  
  delay(10000);
}
