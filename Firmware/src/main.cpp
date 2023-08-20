#include <Arduino.h>
#include <Control_Surface.h>

#include "RolandMC707.h"

#define LEDBUILTIN	13

// Midi Interfaces
USBMIDI_Interface usbMidi;
HardwareSerialMIDI_Interface serialMidi {Serial1, MIDI_BAUD};

BidirectionalMIDI_PipeFactory<2> pipes;

void setup() {
	// Led Builtin setup
	pinMode(LEDBUILTIN, OUTPUT);
	digitalWrite(LEDBUILTIN, HIGH);
	delay(800);
	digitalWrite(LEDBUILTIN, LOW);

	// Serial monitor Setup
	Serial.begin(9600);
	Serial.print("Welcome to BigFoot");

	// Control Surface setup
	Control_Surface | pipes | usbMidi;
	Control_Surface | pipes | serialMidi;
	Control_Surface.begin();
}

void loop() {
	Control_Surface.loop();
}
