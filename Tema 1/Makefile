# Declaratii variabile
CC = gcc
CFLAGS = -Wall
SRCS = jocuri_societate.c forme.c circuits.c segment_display.c
OBJS = $(SRCS:%.c=%)
LIB = -lm

TARGETS=jocuri_societate forme circuits segment_display

build: $(OBJS) $(TARGETS)

jocuri_societate: jocuri_societate.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LIB)

forme: forme.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LIB)

simulator_circuite: circuits.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LIB)

segment_display: segment_display.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LIB)

clean:
	rm -f $(TARGETS)

.PHONY: pack clean