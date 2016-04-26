## Local build configuration
## Parameters configured here will override default and ENV values.
## Uncomment and change examples:

#Add your source directories here separated by space
MODULES = app
# EXTRA_INCDIR = include

## ESP_HOME sets the path where ESP tools and SDK are located.
## Windows:
# ESP_HOME = c:/Espressif

## MacOS / Linux:
ESP_HOME = $(HOME)/git/esp-open-sdk

## SMING_HOME sets the path where Sming framework is located.
## Windows:
# SMING_HOME = c:/tools/sming/Sming 

# MacOS / Linux
SMING_HOME = $(HOME)/git/Sming/Sming

## COM port parameter is reqruied to flash firmware correctly.
## Windows: 
# COM_PORT = COM3

# MacOS / Linux:
COM_PORT = /dev/ttyAMA0

# Com port speed (Program transfer)
COM_SPEED	= 115200

# Com port speed serial (& python r/w)
COM_SPEED_SERIAL	= 115200

## Configure flash parameters (for ESP12-E and other new boards):
# SPI_MODE = dio

## SPIFFS options
DISABLE_SPIFFS = 1
# SPIFFs Location
#SPIFF_FILES = web/build
# we will use global WiFi settings from Eclipse Environment Variables, if possible

## Altri parametri
#RBOOT_ENABLED ?= 0
#SPI_SPEED ?= 40
#SPI_MODE ?= qio
#SPI_SIZE ?= 512K

ifdef MQTT_USERNAME
	USER_CFLAGS += -DMQTT_USERNAME=\"$(MQTT_USERNAME)\" -DMQTT_PWD=\"$(MQTT_PWD)\"
endif

ifdef MQTT_HOST
	USER_CFLAGS += -DMQTT_HOST=\"$(MQTT_HOST)\"
endif

ifdef MQTT_PORT
	USER_CFLAGS += -DMQTT_PORT=$(MQTT_PORT)
endif

