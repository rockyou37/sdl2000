#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *imgSurface = NULL;
    SDL_Texture *imgTexture = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Scenario 4 - Deplacement clavier",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    imgSurface = IMG_Load("image.png");
    imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);

    int imgW = imgSurface->w;
    int imgH = imgSurface->h;
    SDL_FreeSurface(imgSurface);

    /* Position centrée */
    SDL_Rect pos;
    pos.w = imgW;
    pos.h = imgH;
    pos.x = (800 - imgW) / 2;
    pos.y = (600 - imgH) / 2;

    int vitesse = 5;
    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    pos.y -= vitesse;
                    break;
                case SDLK_DOWN:
                    pos.y += vitesse;
                    break;
                case SDLK_LEFT:
                    pos.x -= vitesse;
                    break;
                case SDLK_RIGHT:
                    pos.x += vitesse;
                    break;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imgTexture, NULL, &pos);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(imgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
