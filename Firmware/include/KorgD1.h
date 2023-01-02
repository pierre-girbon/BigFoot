#include <Arduino.h>
#include <Control_Surface.h>

// Multiplexer Init
CD74HC4051 switchMux {5, {2,3,4}};

// Footswitches initialization
PCButton PCChange {switchMux.pin(0), {4, CHANNEL_1}};
CCButton BankSelectMSB {switchMux.pin(0), {0, CHANNEL_1}, {0x79, 0}};
CCButton BankSelectLSB {switchMux.pin(0), {32, CHANNEL_1}, {0x02, 0}};
//Expression Pedals init
CCPotentiometer expr1 {
	A0, {MIDI_CC::Modulation_Wheel, CHANNEL_1}
};
