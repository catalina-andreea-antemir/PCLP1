CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=-lm

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c -o image_editor $(LDFLAGS)

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
