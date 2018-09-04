CFLAGS = -c -Wall
LFLAGS =
OBJS   = main.o midi.o synth.o
TARGET = midi

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm $(OBJS) $(TARGET)
