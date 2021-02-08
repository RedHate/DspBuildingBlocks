
all:
	g++ -o synth synth.cc Nco.cc PhaseAccumulator.cc

run: all play

#chords!
a:all
	./synth 261 329 440 | aplay -f s16_le -r 24000

b:all
	./synth 311 369 493 | aplay -f s16_le -r 24000

c: all
	./synth 261 329 392 | aplay -f s16_le -r 24000

d: all
	./synth 293 369 440 | aplay -f s16_le -r 24000

e: all
	./synth 329 415 493 | aplay -f s16_le -r 24000

f:all
	./synth 349 440 523 | aplay -f s16_le -r 24000

g: all
	./synth 392 493 587 | aplay -f s16_le -r 24000

#playing the cords.
play: c d e f a g b

clean:
	rm -rf *.o synth
