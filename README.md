# dog-bowl-sensor
MQTT Scale for Dog Water and Food Bowl, adapted from [EverythingSmartHome's mqtt-bed-sensor](https://everythingsmarthome.co.uk/howto/building-a-bed-occupancy-sensor-for-home-assistant/)

## Requirements
### Hardware
- [HX711 Amplifier](https://amzn.to/2POYBzH)
- [Load Cells](https://amzn.to/2PQunMC)
- ESP8266 based board with 5v output (Wemos D1 Mini etc)

### Libraries
- [HX711](https://github.com/bogde/HX711) library - available through Arduino IDE library manager
- [PubSubClient](https://github.com/knolleary/pubsubclient) library - available through Arduino IDE library manager
- [ESP boards](https://github.com/esp8266/Arduino)

## Use case
This project is being built to automatically detect the water and food in my dog's bowl and then integrate this data into HomeKit by way of Home Assistant.

## Calibration
1. Load calibration sketch and ensure no additional weight is on the bed/scale
2. Using serial monitor, observe starting measurements
3. Place known weight on bed/scale e.g 5kg and observe new measurements printed on monitor
4. Adjust calibration factor variable and repeat steps till values are correct. Take note of calibration factor

## Bed sensor
1. Load sketch, ensure no additional weight is on the scales
2. Fill in all variables in config.h file
3. Observe output on serial monitor, place known weight on scales and ensure read-out is correct.
4. Once happy, unplug and plug into main power supply and enjoy!

## Credits
This project will be based heavily on the work done by [EverythingSmartHome for an MQTT Bed Sensor](https://everythingsmarthome.co.uk/howto/building-a-bed-occupancy-sensor-for-home-assistant/)
Additional credit goes to Zack over at [Self Hosted Home](https://selfhostedhome.com/diy-bed-presence-detection-home-assistant/) who inspired EverythingSmartHome's project.
