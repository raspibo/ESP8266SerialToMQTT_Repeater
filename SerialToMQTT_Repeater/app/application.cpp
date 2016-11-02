#include <user_config.h>
#include <SmingCore/SmingCore.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "levelh" // Put you SSID and Password here
	#define WIFI_PWD "leveldave"
#endif

// ... and/or MQTT username and password
#ifndef MQTT_USERNAME
	#define MQTT_USERNAME ""
	#define MQTT_PWD ""
#endif

// ... and/or MQTT host and port
#ifndef MQTT_HOST
	#define MQTT_HOST "level1"
	#define MQTT_PORT 1883
#endif

// Forward declarations
void startMqttClient();
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount);

Timer procTimer;

// MQTT client
// For quick check you can use: http://www.hivemq.com/demos/websocket-client/ (Connection= test.mosquitto.org:8080)
MqttClient mqtt(MQTT_HOST, MQTT_PORT);

// Check for MQTT Disconnection
void checkMQTTDisconnect(TcpClient& client, bool flag){
	
	// Called whenever MQTT connection is failed.
	if (flag == true)
		Serial.println("MQTT Broker Disconnected!!");
	else
		Serial.println("MQTT Broker Unreachable!!");
	
	// Restart connection attempt after few seconds
	procTimer.initializeMs(2 * 1000, startMqttClient).start(); // every 2 seconds
}

// Legge lo stream della seriale e lo mette sulla variabile "Message" come stringa
// Credo che questa funzione sia in un ".h/.cpp" del framework. Funziona ? La uso ;)
// Aggiungo l'invio del dato al broker mqtt.
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
  String MessageP = "";	// Inizializzo stringa publish, DOVE pubblicare
  String MessageS = "";	// Inizializzo stringa string, COSA pubblicare
  int countspace = 0;	// Mi serve per sapere se ho incontrato il primo carattere spazio, per dividere la stringa
  if (arrivedChar == '\n')
  {
	while (stream.available())
	{
      char cur = stream.read();
	  if (countspace == 1)
	  {
		MessageS += cur;
	  }
	  if (countspace == 0)
	  {
		if ( cur == ' ')
		{
		  countspace = 1;
		}
		else
		{
		  MessageP += cur;
		}
	  }
	//Serial.print(cur);
	//Message += cur;   // Aggiunge caratteri (cur) alla stringa
	}

	/* Forse questo non serve piu` ? */
    //Message.remove(Message.length()-2);   // Elimino dalla stringa i caratteri "\" e "n", perche` inviano un CR

	/* Come devo manipolare "Message" per ottenere i parametri che mi servono ? */

    if (mqtt.getConnectionState() != eTCS_Connected)
        startMqttClient(); // Auto reconnect

    Serial.println("Let's publish message now!");

    Serial.print("MessaggioP: ");
    Serial.println(MessageP);
    Serial.print("MessaggioS: ");
    Serial.println(MessageS);
	
	//MessageS.remove(MessageS.length()-2);	// Elimino dalla stringa i caratteri "\" e "n", perche` inviano un CR	// NON FUNZIONA ? Mi ha tolto anche la }
	
	//mqtt.publish(MQTT_PUBLISH, "{ \"ID\" : \"" + String(ID) + "\", \"Valore\" : \"" + String(Message) + "\" }"); // or publishWithQoS
	/* Quella sopra e` la vecchia stringa
	Adesso (sopra) devo vedere COME per dividere la stringa in arrivo ed ottenere due parametri: PUBLISH e MESSAGE
	*/
	//mqtt.publishWithQoS(String(MessageP),String(MessageS),1);	// Il qos 2 non va proprio, l'1 non mi sembra che vada cosi` bene, torno a ..
	mqtt.publish(String(MessageP),String(MessageS));
  }
}

// Run MQTT client
void startMqttClient()
{
	procTimer.stop();
	if(!mqtt.setWill("last/will","The connection from this device is lost:(", 1, true)) {
		debugf("Unable to set the last will and testament. Most probably there is not enough memory on the device.");
	}
	mqtt.connect("esp8266", MQTT_USERNAME, MQTT_PWD);
	// Assign a disconnect callback function
	//mqtt.setCompleteDelegate(checkMQTTDisconnect); // Non funziona e non c'e` piu` nel nuovo esempio
}

// Will be called when WiFi station was connected to AP
void connectOk()
{
	Serial.println("I'm CONNECTED");

	// Praticamente e` tutto qua!
	Serial.setCallback(onDataCallback);

	// Run MQTT client
	startMqttClient();

}

// Will be called when WiFi station timeout was reached
void connectFail()
{
	Serial.println("I'm NOT CONNECTED. Need help :(");

	// .. some you code for device configuration ..
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Debug output to serial

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(true);
	WifiAccessPoint.enable(false);

	// Run our method when station was connected to AP (or not connected)
	WifiStation.waitConnection(connectOk, 20, connectFail); // We recommend 20+ seconds for connection timeout at start
}
