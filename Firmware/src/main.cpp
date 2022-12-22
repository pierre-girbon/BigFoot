#include <Arduino.h>
#include <Bounce2.h>

/******************************************************
 * 	Midi Lib
 * ****************************************************/
enum MidiMessageType{NOTE_OFF, NOTE_ON, POLY_AFTERTOUCH, CONTROL_CHANGE, PROGRAM_CHANGE, AFTERTOUCH, PITCH_WHEEL};

enum SwitchType{CONTINUOUS, ONE_SHOT, TOGGLE};

class SwitchController {
	public:
		SwitchController(MidiMessageType msgType, byte channel, SwitchType swType) {
			midiMessageType = msgType;
			setMidiChannel(channel);
			switchType = swType;
		}

		SwitchController(MidiMessageType msgType, byte channel, SwitchType swType, byte data1) {
			midiMessageType = msgType;
			setMidiChannel(channel);
			setMidiData1(data1);
			switchType = swType;
		}

		void setPin(byte pin1, byte pin2) {
			btn1.attach(pin1, INPUT_PULLUP);
			btn1.interval(10);
			btn2.attach(pin2, INPUT_PULLUP);
			btn2.interval(10);
		}

		void setPin(byte pin2) {
			btn2.attach(pin2, INPUT_PULLUP);
			btn2.interval(10);
		}

		void setMidiChannel(byte channel) {
			if (channel >= 0 && channel <= 15) {
				midiChannel = channel;
			}
		}

		byte getMidiChannel() {
			return midiChannel;
		}

		void setMidiData1(byte data1) {
			if (midiMessageType == CONTROL_CHANGE || midiMessageType == PROGRAM_CHANGE) {
				midiData1 = data1;
			}
		}

		byte getMidiData1() {
			return midiData1;
		}

		byte getMidiData2() {
			return midiData2;
		}

		void readRawData() {
			if (midiMessageType != CONTROL_CHANGE && midiMessageType != PROGRAM_CHANGE) {
				btn1.update();
				previousData1 = midiData1;
				midiData1 = 127 * (1 - btn1.read());  // Input Pullup
			}
			
			btn2.update();
			previousData2 = midiData2;
			midiData2 = 127 * (1 - btn2.read());
		}

		void sendMidi() {
			if (switchType == CONTINUOUS) {
				if (midiData2 == 127) {
					Serial.print("Send Midi Message - ");
					Serial.print(switchType);
					Serial.print(midiMessageType);
					Serial.print(midiChannel);
					Serial.print(midiData1);
					Serial.println(midiData2);
				}
			}
			else if (switchType == ONE_SHOT) {
				if (previousData2 == 0 and midiData2 == 127) {
					Serial.print("Send One shot Midi Message - ");
					Serial.print(midiMessageType);
					Serial.print(midiChannel);
					Serial.print(midiData1);
					Serial.println(midiData2);
				}
			}
		}

	private:
		MidiMessageType midiMessageType;
		byte midiChannel;
		SwitchType switchType;
		byte midiData1;
		byte previousData1;
	        Bounce btn1 = Bounce();
		byte midiData2;
		byte previousData2;
	        Bounce btn2 = Bounce();

};


/******************************************************
 * 	Init Part
 ******************************************************/
#define LEDBUILTIN	13

// Multiplexer channel selection pins
const byte Ss[3] = {2, 3, 4};

// Switch LEDs pin
const byte footLedPin = 6;

// Preset change pins
const byte presetUp = 7;
const byte presetDown = 8;

// Expression pedals pins
const byte exprPin1 = A0;
const byte exprPin2 = A1;


SwitchController Sw1 = SwitchController(
		PROGRAM_CHANGE, // Controller Type
	       	12,  		// Channel
	       	CONTINUOUS,	// Switch Type
	       	7);  		// Program number

void setup() {
	// Internal LED Setup
	pinMode(LEDBUILTIN, OUTPUT);
	digitalWrite(LEDBUILTIN, HIGH);
	delay(1000);
	digitalWrite(LEDBUILTIN, LOW);

	// USB Serial setup
	Serial.begin(9600);
	Serial.println("Setup phase");

	// Multiplexer channel pins setup
	for (byte i = 0; i < 3; i++) {
		pinMode(Ss[i], OUTPUT);
	}

	// Foot switches
	Sw1.setPin(5);
	
	pinMode(presetUp, INPUT_PULLUP);
	pinMode(presetDown, INPUT_PULLUP);

	pinMode(footLedPin, OUTPUT);
}

void loop() {
	digitalWrite(Ss[0], LOW);
	digitalWrite(Ss[1], LOW);
	digitalWrite(Ss[2], LOW);

	Sw1.readRawData();
	Sw1.sendMidi();
}
