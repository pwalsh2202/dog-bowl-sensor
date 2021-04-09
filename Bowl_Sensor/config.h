
// Wifi Settings
#define SSID                          		"Your Wifi SSID Here"
#define PASSWORD                      		"Your Wifi Password Here"

// MQTT Settings
#define HOSTNAME                      		"dog-bowl-sensor"
#define MQTT_SERVER                   		"your_mqtt_hostname"
#define WATER_STATE_TOPIC                   "home/kitchen/dog/water"
#define WATER_STATE_RAW_TOPIC               "home/kitchen/dog/water/raw"
#define FOOD_STATE_TOPIC                   	"home/kitchen/dog/food"
#define FOOD_STATE_RAW_TOPIC               	"home/kitchen/dog/food/raw"
#define AVAILABILITY_TOPIC            		"home/kitchen/dog/available"
#define TARE_TOPIC                    		"home/kitchen/dog/tare"
#define mqtt_username                 		"mqtt_username"
#define mqtt_password                 		"mqtt_password"

// HX711 Pins
const int WATER_DOUT_PIN = 2; // Water - Remember these are ESP GPIO pins, they are not the physical pins on the board.
const int WATER_SCK_PIN = 3;

const int FOOD_DOUT_PIN = 4; // Food - Remember these are ESP GPIO pins, they are not the physical pins on the board.
const int FOOD_SCK_PIN = 5;

int calibration_factor = 2000; // Defines calibration factor we'll use for calibrating.
