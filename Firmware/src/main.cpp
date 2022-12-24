#include <Arduino.h>
#include <Control_Surface.h>


#define LEDBUILTIN	13

// Midi Interfaces
USBMIDI_Interface usbMidi;
HardwareSerialMIDI_Interface serialMidi {Serial1, MIDI_BAUD};

BidirectionalMIDI_PipeFactory<2> pipes;

// Multiplexer initialization
CD74HC4051 switchMux {5, {2, 3, 4}};

// Footswitches initialization
Bank<2> bank(8);
IncrementDecrementSelector<2> selector {
	bank,
	{7,8},
	Wrap::Wrap,
};

Bankable::PCButton PCChange [] {
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(0), {0, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(1), {1, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(2), {2, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(3), {3, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(4), {4, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(5), {5, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(6), {6, CHANNEL_16} },
	{ {bank, BankType::CHANGE_ADDRESS}, switchMux.pin(7), {7, CHANNEL_16} },
};

//Expression Pedals init
CCPotentiometer expr1 {
	A0, {MIDI_CC::Modulation_Wheel, CHANNEL_1}
};

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
