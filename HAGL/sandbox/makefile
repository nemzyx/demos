CC = gcc
CFLAGS = -Wall -I../modules/hagl/include -I../modules/hagl_sdl2_fluid
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

mod = $(wildcard ./../modules/hagl/src/*.c) \
      $(wildcard ./../modules/hagl_sdl2/hagl_hal.c)

src = $(wildcard *.c) ${mod}

obj = $(src:.c=.o)

sandbox: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)
	rm -f $(mod:.c=.o)


.PHONY: clean
clean:
	rm -f $(obj)
