# USB MIDI Drum Trigger using Seeeduino Lotus Cortex-M0

This project demonstrates how to create a USB MIDI drum trigger using the Seeeduino Lotus Cortex-M0 board. The drum trigger uses an analog sensor to detect hits and send MIDI Note On messages to trigger drum sounds on a computer or MIDI-enabled device.

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Customization](#customization)
- [Contributing](#contributing)
- [License](#license)

## Hardware Requirements

To build and run this project, you will need the following hardware components:

- Seeeduino Lotus Cortex-M0 board (or similar Arduino-compatible board)
- Analog sensor (e.g., piezo sensor, force-sensitive resistor)
- USB cable for connecting the board to your computer
- MIDI-enabled device (computer, synthesizer, drum module)

## Software Requirements

You will need the following software tools and libraries to work with this project:

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Adafruit TinyUSB Library](https://github.com/adafruit/Adafruit_TinyUSB_Arduino)
- [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library)

## Installation

1. Clone this repository to your local machine or download the ZIP file.

git clone https://github.com/your-username/USBMIDIDrumTrigger-SeeeduinoLotusCortex-M0.git


2. Open the Arduino IDE and install the required libraries:
- Adafruit TinyUSB Library
- Arduino MIDI Library

3. Connect your Seeeduino Lotus Cortex-M0 board to your computer via USB.

4. Open the `USBMIDIDrumTrigger.ino` sketch in the Arduino IDE.

5. Select the appropriate board and COM port in the Arduino IDE settings.

6. Upload the sketch to your board.

## Usage

1. Connect the analog sensor (e.g., piezo sensor or force-sensitive resistor) to the board's analog input pin.

2. Power on your MIDI-enabled device (computer, synthesizer, drum module) and ensure it is connected via USB.

3. Hit the sensor to trigger MIDI Note On messages. The sensor's hits will trigger MIDI notes on your connected device.

4. Monitor the serial output in the Arduino IDE's Serial Monitor for debugging and note information.

## Customization

You can customize this project by:

- Adjusting the sensor sensitivity threshold in the code (`sensorValue > threshold`).
- Changing the MIDI note number to trigger different drum sounds.
- Modifying the delay between MIDI messages to fine-tune responsiveness.

Feel free to adapt the code and hardware to your specific needs and drum trigger setup.

## Contributing

Contributions are welcome! If you have any suggestions, bug fixes, or improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
