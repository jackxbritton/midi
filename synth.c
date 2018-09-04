#include "synth.h"
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include <stdio.h>

int synth_init(Synth *s, int tone_low, int tone_high) {
	s->tones_zero = tone_low;
	s->tones_len = tone_high - tone_low + 1;
	s->tones = malloc(s->tones_len * sizeof(char));
	if (s->tones == NULL) return errno;
	return 0;
}

void synth_deinit(Synth *s) {
	free(s->tones);
}

void synth_set(Synth *s, int tone, int val) {
	int index = tone - s->tones_zero;
	printf("%d %d\n", tone, index);
	assert(index >= 0 && index < s->tones_len);
	s->tones[index] = val;
}
