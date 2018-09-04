#ifndef SYNTH_H
#define SYNTH_H

typedef struct {
	char *tones;
	int tones_zero;
	int tones_len;
} Synth;

int synth_init(Synth *s, int tone_low, int tone_high);
void synth_deinit(Synth *s);
void synth_set(Synth *s, int tone, int val);

#endif
