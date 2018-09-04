#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "midi.h"
#include "synth.h"

// Run like `./midi < /dev/midi2`

// p100 - status bytes.
// p101 - data bytes.

int do_stuff(int fd);
int do_more_stuff(int fd, MidiMarshaller *mm, Synth *synth);

int main(int argc, char *argv[]) {
	int err = do_stuff(STDIN_FILENO);
	if (err != 0) fprintf(stderr, "%s\n", strerror(err));
	return err;
}

int do_stuff(int fd) {

	// Init the marshaller and the synth.
	MidiMarshaller mm;
	int err = midi_init(&mm);
	if (err != 0) return err;

	Synth synth;
	err = synth_init(&synth, 36, 84);
	if (err != 0) {
		midi_deinit(&mm);
		return err;
	}

	// Do stuff and exit.
	err = do_more_stuff(fd, &mm, &synth);
	midi_deinit(&mm);
	synth_deinit(&synth);
	return err;
}

int do_more_stuff(int fd, MidiMarshaller *mm, Synth *synth) {

	for (int i = 0; i < 1024; i++) {

		// Read the byte.
		char byte;
		ssize_t num_bytes = read(fd, &byte, 1);
		if (num_bytes == -1) return errno;

		// Check for an event.
		const MidiEvent *event = midi_decode(mm, byte);
		if (event == NULL) continue;

		// Print some stuff.
		synth_set(synth, event->note.tone, event->type == MIDI_NOTE_ON);
		for (int i = 0; i < synth->tones_len; i++) {
			if (synth->tones[i]) printf("%d ", i+synth->tones_zero);
		}
		printf("\n");

	}

	return 0;
}
