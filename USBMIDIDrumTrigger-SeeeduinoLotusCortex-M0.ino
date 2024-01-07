#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

const int sensorPin = A1;
const int ledPin = 13;
const unsigned long debounceDelay = 1; // Debounce delay in milliseconds
const unsigned long noteOffDelay = 100; // Note-off delay in milliseconds

bool noteOn = false; // Flag to track if a note is currently on
unsigned long noteStartTime; // Time when the note was triggered
unsigned long lastDebounceTime = 0; // Last time the sensor value was stable
int lastSensorValue = 0; // Last stable sensor value

void setup()
{
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on a core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif

  pinMode(ledPin, OUTPUT);

  //usb_midi.setStringDescriptor("TinyUSB MIDI");

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call usb_midi's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Attach the handleNoteOn function to the MIDI Library. It will
  // be called whenever the Bluefruit receives MIDI Note On messages.
  MIDI.setHandleNoteOn(handleNoteOn);

  // Do the same for MIDI Note Off messages.
  MIDI.setHandleNoteOff(handleNoteOff);

  Serial.begin(115200);

  // wait until device mounted
  while (!TinyUSBDevice.mounted()) delay(1);
}

void loop()
{
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);

  // Check for debounce
  if (millis() - lastDebounceTime >= debounceDelay)
  {
    // Update the last debounce time
    lastDebounceTime = millis();

    // Check if the sensor value is stable and above the threshold
    if (sensorValue > 1000 && sensorValue != lastSensorValue)
    {
      // Calculate velocity based on the sensor reading (0 to 127)
      int velocity = map(sensorValue, 1001, 1023, 1, 127);

      // If a note is not already on, trigger a new note
      if (!noteOn)
      {
        // Send Note On for MIDI note 38 (snare) with velocity on channel 1.
        MIDI.sendNoteOn(38, velocity, 1);

        // Set noteOn flag and record the start time
        noteOn = true;
        noteStartTime = millis();
      }
    }
    else if (sensorValue <= 1000 && noteOn)
    {
      // If a note was on and the duration is greater than 100 ms, turn it off
      if (millis() - noteStartTime > noteOffDelay)
      {
        // Send Note Off for MIDI note 38 (snare) on channel 1.
        MIDI.sendNoteOff(38, 0, 1);

        // Reset noteOn flag
        noteOn = false;
      }
    }

    // Update the last stable sensor value
    lastSensorValue = sensorValue;
  }

  // read any new MIDI messages
  MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Log when a note is released.
  Serial.print("Note off: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}
