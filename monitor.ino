// This #include statement was automatically added by the Particle IDE.
#include "OneWire/OneWire.h"

// This #include statement was automatically added by the Particle IDE.
#include "spark-dallas-temperature/spark-dallas-temperature.h"

#include "application.h"
#include "LiquidCrystal_I2C.h"

DallasTemperature dallas(new OneWire(D2));
LiquidCrystal_I2C   *lcd;

void setup()
{
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);  // set the LCD address to 0x20 for a 16x2 //SparkCore bug, address is actually 27 but shifted (0x27*2)
    lcd->init();                      // initialize the lcd
    lcd->backlight();
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("---Spark*Core---");
    lcd->setCursor(0,1);
    lcd->print("Uptime:");

    pinMode(A0, OUTPUT);
    dallas.begin();
}

void loop()
{
    lcd->setCursor(7,1);

    dallas.requestTemperatures();
    float celsius = dallas.getTempCByIndex( 0 );
    Serial.print("Temperature: "); Serial.println(celsius) ;

    lcd->print(celsius);

    if(celsius > 25) {

        analogWrite(A0, 100);
        delay(50);
        analogWrite(A0, 255);
        delay(50);
        analogWrite(A0, 100);
        delay(50);
        analogWrite(A0, 0);
    }
    delay(200);


}
