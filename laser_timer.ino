/*
  Laser Timer

  Times how long it takes for two laser gates to be activated successively, prints the time
  taken to the serial monitor in milliseconds.

  This program was created for the university of Canterbury's ENMT221 line following robot competition

  modified 17 Oct 2024
  by Boston Black
*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>

/** Serial print options */
#define DEBUG false // Debug mode will print sensor output, useful for setting threshold
#define VERBOSE true // Print time to serial as timer is running

/** Settings */
#define THRESHOLD 600 // Sensor output below which gates will be triggered
#define BAUD_RATE 9600 // Baud rate for serial communication

/** Pins */
#define SENSOR_1 18 // Sensor input for start gate
#define SENSOR_2 19 // Sensor input for end gate
#define DEBUG_LED 25 // LED will be on when timer is active

static unsigned long startTime = 0;
static bool timerActive = false;

void setup()
{
  // initialize sensor pins as input
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);

  // initialize LED as an output.
  pinMode(DEBUG_LED, OUTPUT);

  Serial1.begin(BAUD_RATE);
}

void loop()
{
  // Read sensor values
  uint16_t sensor1 = analogRead(SENSOR_1);
  uint16_t sensor2 = analogRead(SENSOR_2);

  // Print sensor values if DEBUG mode is on
  if (DEBUG) {
    Serial1.println("--------START--------");
    Serial1.println("Sensor vals: ");
    Serial1.println(sensor1);
    Serial1.println(sensor2);
  }
    
  // Start timer if start sensor triggered and timer is not already avtive
  if ((sensor1 <= THRESHOLD) && (timerActive == false)) {
    startTime = millis();
    digitalWrite(DEBUG_LED, HIGH);
    Serial1.println("Timer active...");
    timerActive = true;
  }

  // Print the current time if VERBOSE mode is on
  if (timerActive && VERBOSE) {
    unsigned long time = millis() - startTime;
    Serial1.print("Timer: ");
    Serial1.println(time);
  }

  // End timer and print final time if end sensor triggered and timer is active
  if ((sensor2 <= THRESHOLD) && (timerActive == true)) {
    unsigned long time = millis() - startTime;
    digitalWrite(DEBUG_LED, LOW);
    Serial1.println("-----Finish Time-----");
    Serial1.println(time);
    Serial1.println("Timer stopped.");
    timerActive = false;
  }
}