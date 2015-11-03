#include "MeOrion.h"
#include "MeHumitureSensor.h"

MeHumiture hs(PORT_6);

const char* host = "data.sparkfun.com";
const char* streamId   = "your stream id";
const char* privateKey = "your private key";

String buffer = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.print("/setupwifi/your wifi ssid/your wifi password\n");
  delay(3000);
}

  // We now create a URI for the request
double lastTime = 0;
void loop() {
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
    Serial.print("/request/data.sparkfun.com/80/");
    url.replace("/","%2F");
    Serial.print(url);
    Serial.print("\n");
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
