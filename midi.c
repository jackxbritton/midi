#include "midi.h"
#include <stdio.h>

int midi_init(MidiMarshaller *mm) {
	mm->bytes_left = 0;
	return 0;
}

void midi_deinit(MidiMarshaller *mm) {}

const MidiEvent *midi_decode(MidiMarshaller *mm, uint8_t byte) {

	// if bytes_left == 0, it's a new event.
	if (mm->bytes_left == 0) {

		// Check for a status byte (MSB is 1).
		// If it's not a status byte, status is unchanged (Running Status).
		int is_status = byte >> 7;
		if (is_status) mm->event.type = byte >> 4;

		// Set bytes_left.
		switch (mm->event.type) {
		case 0x8:
		case 0x9:
		case 0xA:
		case 0xB:
		case 0xE:
			mm->bytes_left = 2;
			break;
		case 0xC:
		case 0xD:
			mm->bytes_left = 1;
			break;
		default:
			return NULL;
		}

		// If it was a status byte we're done.
		if (is_status) return NULL;

	}

	mm->bytes_left--;

	// Read the data byte.
	switch (mm->event.type) {
	case MIDI_NOTE_OFF:
	case MIDI_NOTE_ON:
		switch (mm->bytes_left) {
		case 1:
			mm->event.note.tone = byte;
			break;
		case 0:
			mm->event.note.velocity = byte;
			if (mm->event.note.velocity == 0) mm->event.type = MIDI_NOTE_OFF;
			return &mm->event;
		}
	}

	return NULL;
}
