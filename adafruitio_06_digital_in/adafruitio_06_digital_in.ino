#include "config.h"
#include <dht.h>

#define dht_pin 5
#define dirt_pin 34
#define lumi_pin 35
 
dht DHT;

bool current = false;
bool last = false;

int humi;
int temp;
int tempdirt;

float value = 0;

AdafruitIO_Feed *humiditedirt = io.feed("humiditedirt");
AdafruitIO_Feed *humidite = io.feed("humidite");
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *luminosite = io.feed("luminosite");

void setup() {
  pinMode(lumi_pin, INPUT_PULLUP);
  Serial.begin(115200);

  while(! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
  DHT.read11(dht_pin);  
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");  
  tempdirt= analogRead(dirt_pin);
  tempdirt = map(tempdirt,550,0,0,100);
  Serial.println(tempdirt);
  humiditedirt->save(tempdirt);
  Serial.println(analogRead(lumi_pin));
  luminosite->save(analogRead(lumi_pin));  
  humi = DHT.humidity;
  humidite->save(humi);
  temp = DHT.temperature;
  temperature->save(temp);

  delay(5000);
}