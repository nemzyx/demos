#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <hagl.h>
#include <hagl_hal.h>
#include <aps.h>
#include <fps.h>

#include "rgbplasma.h"

static const uint64_t MS_PER_FRAME_100_FPS = 1000 / 100;

static fps_instance_t fps;
static aps_instance_t bps;

typedef struct stats {
  float fps;
  float bps;
} stats_t;

static stats_t stats;
uint32_t stats_callback(); // declare to define later

int main()
{
  srand(time(0)); // seed the RNG
  hagl_backend_t *display = hagl_init();
  size_t bytes = 0;

  uint32_t stats_delay = 1000; /* 0.5 fps */
  SDL_Event event;
  SDL_TimerID fps_id;
  fps_id = SDL_AddTimer(stats_delay, stats_callback, &stats);

  fps_init(&fps);
  aps_init(&bps);
  
  printf("Press ESC to quit.\n\n");
  bool quit = false;

  while (!quit) {
    uint32_t start = SDL_GetTicks();

    rgbplasma_animate();
    rgbplasma_render(display);
    
    bytes = hagl_flush(display);

    uint32_t end = SDL_GetTicks();
    int32_t delay = MS_PER_FRAME_100_FPS - (end - start);
    if (delay > 0) { SDL_Delay(delay); }
    stats.bps = aps_update(&bps, bytes);
    stats.fps = fps_update(&fps);

    if (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) { quit = true; }
      if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;
        }
        hagl_clear(display);
        fps_reset(&fps);
        aps_reset(&bps);
        break;
      }
    }    
  }

  SDL_RemoveTimer(fps_id);
  hagl_close(display);

  return 0;
}

uint32_t stats_callback(uint32_t interval, void *param)
{
  stats_t *data = (stats_t *)param;
  printf("%.*f fps / %.*f kBps\n", 1, data->fps, 1, data->bps / 1000);
  return interval;
}
