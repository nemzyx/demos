CC = gcc
CFLAGS = -Wall -I../modules/hagl/include -I../modules/hagl_sdl2
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

mod = $(wildcard ./../modules/hagl/src/*.c) \
      $(wildcard ./../modules/hagl_sdl2/hagl_hal.c)

src = $(wildcard *.c) ${mod}

obj = $(src:.c=.o)

demo: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)
	rm -f $(mod:.c=.o)


.PHONY: clean
clean:
	rm -f $(obj)
