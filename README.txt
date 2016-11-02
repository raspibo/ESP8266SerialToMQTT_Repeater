ESP8266 Serial to MQTT
======================

Ritrasmette le stringhe ricevute via seriale ad un broker MQTT.
Il 'progetto' e` nato per "Centralina livello 1".

Le stringhe da inviare sono da formattare come indicato nel wiki:
  http://www.raspibo.org/wiki/index.php?title=Centralina_livello_1#Promemoria_chiavi.2C_codici_e_...

Per esempio:
I/ESP8266/WiFi/Mobile/Temperatura { "ID" : "STmob", "Valore" : "24.56" }


Riferimenti:
- Sming
- Centralina livello 1