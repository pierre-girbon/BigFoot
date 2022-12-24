#include <Arduino.h>
#include <Control_Surface.h>

// Multiplexer Init
CD74HC4051 switchMux {5, {2,3,4}};

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
