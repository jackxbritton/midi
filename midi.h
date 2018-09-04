#ifndef MIDI_H
#define MIDI_H

#include <stdint.h>

typedef enum {
	MIDI_NOTE_OFF = 0x8,
	MIDI_NOTE_ON  = 0x9
} MidiEventType;

typedef struct {
	int tone, velocity;
} MidiEventNote;

typedef struct {
	MidiEventType type;
	union {
		MidiEventNote note;
	};
} MidiEvent;

typedef struct {
	int bytes_left;
	MidiEvent event;
} MidiMarshaller;

int midi_init(MidiMarshaller *mm);
void midi_deinit(MidiMarshaller *mm);
const MidiEvent *midi_decode(MidiMarshaller *mm, uint8_t byte);

#endif
