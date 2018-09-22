#include <LCD5110_Basic.h>
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
extern uint8_t SmallFont[];
DHT dht(DHTPIN, DHTTYPE);
LCD5110 tela(8,9,10,12,11);

void setup()
{
	tela.InitLCD();
	Serial.begin(9600);
	Serial.println("Iniciando...");
	dht.begin();
}

void loop()
{
	float hmd = dht.readHumidity();
	float tmp = dht.readTemperature();

	if (isnan(hmd) || isnan(tmp)) {
		Serial.println("Aguardando os dados do sensor!");
		return;
	}

	float sst = dht.computeHeatIndex(tmp, hmd, false);
	Serial.print("Umidade: ");
	Serial.print(hmd);
	Serial.print(" % ");
	Serial.print("Temperatura: ");
	Serial.print(tmp);
	Serial.print(" Cº ");
	Serial.print("Sensação Térmica: ");
	Serial.print(sst);
	Serial.print(" Cº \n");

	tela.clrScr();
	tela.setFont(SmallFont);

	tela.print("---------------", 0, 0);

	tela.print("Tmp:", 0, 10);
	tela.printNumI(tmp, 30, 10);
	tela.print("C", 42, 10);

	tela.print("Umd:", 0, 25);
	tela.printNumI(hmd, 30, 25);
	tela.print("%", 42, 25);

	tela.print("STr:", 0, 40);
	tela.printNumI(sst, 30, 40);
	tela.print("C", 42, 40);
	delay(2000);
}
