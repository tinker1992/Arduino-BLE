#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>

float temperature;
float humidity;
float pressure;
float test; 
int test2;

#define ALTITUDE 20.0 // Altitude in Hangzhou

Adafruit_BME280 bme; // I2C

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup(void) {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.print("Reading sensor");

  bool status;
    
    // default settings
    status = bme.begin(0x76);  //The I2C address of the sensor I use is 0x76
    if (!status) {
        lcd.clear();
        lcd.print("Error. Check");
        lcd.setCursor(0,1);
        lcd.print("connections");
        while (1);
    }
}

void loop() {
  
 delay(2000);

 getPressure();
 getHumidity();
 getTemperature();
 
 lcd.clear(); 

//Print Title

lcd.print("BME Weather Station");

 //Printing Temperature
 lcd.setCursor(0,1);
 String temperatureString = String(temperature,1);
 lcd.print("Temperature: "); 
 lcd.print(temperatureString);
 lcd.print((char)223);
 lcd.print("C ");
 Serial.print(temperatureString);
 
 //Printing Humidity
 lcd.setCursor(0,2);
 String humidityString = String(humidity,0); 
 lcd.print("Humidity: ");
 lcd.print(humidityString);
 lcd.print("%");
 
 //Printing Pressure
 lcd.setCursor(0,3);
 lcd.print("Pressure: ");
 String pressureString = String(pressure,2);
 lcd.print(pressureString);
 lcd.print("hPa");
}

float getTemperature()
{
  temperature = bme.readTemperature();
}

float getHumidity()
{
  humidity = bme.readHumidity();
}

float getPressure()
{
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;
}
