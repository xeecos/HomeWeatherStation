#include "MeBaseBoard.h"
#include "MeHumitureSensor.h"

MeHumiture hs(PORT_6);

const char* ssid     = "Maker-guest";
const char* password = "makeblock";

const char* host = "data.sparkfun.com";
const char* streamId   = "bGn9WED62OTAz52ADJN1";
const char* privateKey = "VpXDG7EgZ0u7KDP7lwEY";

String buffer = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(3000);
  Serial1.print("/setupwifi/Maker-guest/makeblock\n");
  delay(3000);
}

  // We now create a URI for the request
double lastTime = 0;
void loop() {
  if(Serial1.available()){
    char c = Serial1.read();
    Serial.print(c);
  }
  if(millis()/1000-lastTime>600){
    hs.update();
    String url = "/input/";
    url += streamId;
    url += "?private_key=";
    url += privateKey;
    url += "&humidity=";
    url += hs.getHumidity();
    url += "&temp=";
    url += hs.getTemperature();
    Serial1.print("/request/data.sparkfun.com/80/");
    url.replace("/","%2F");
    Serial1.print(url);
    Serial1.print("\n");
    lastTime = millis()/1000;
  }
}
void urlencode(String input)
{
  input.replace("/","%2F");
}
void urldecode(String input)
{
  input.replace("%2F","/");
}
