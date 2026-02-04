#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // ------------------------------
    // Déclarations SDL2 générales
    // ------------------------------
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // ------------------------------
    // Déclarations SDL2_image
    // ------------------------------
    SDL_Texture *image = NULL;
    SDL_Rect posImage;

    // ------------------------------
    // Déclarations SDL2_mixer
    // ------------------------------
    Mix_Chunk *son = NULL;

    // ------------------------------
    // Déclarations SDL2_ttf
    // ------------------------------
    TTF_Font *font = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Rect textPosition;
    int init = 0; // contrôle affichage texte

    // ------------------------------
    // Variables de contrôle
    // ------------------------------
    int running = 1;
    SDL_Event event;

    // ------------------------------
    // Initialiser SDL2 (vidéo + audio)
    // ------------------------------
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    // ------------------------------
    // Créer la fenêtre
    // ------------------------------
    window = SDL_CreateWindow(
        "Atelier SDL2 ",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // ------------------------------
    // Créer le renderer
    // ------------------------------
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // ------------------------------
    // Initialiser SDL2_image et télécharger l'image
    // ------------------------------
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        printf("Erreur IMG_Init : %s\n", IMG_GetError());
        return 1;
    }
    image = IMG_LoadTexture(renderer, "palestine2.jpg");
    if (!image) {
        printf("Erreur IMG_LoadTexture : %s\n", IMG_GetError());
        return 1;
    }
    posImage.x = 0;
    posImage.y = 0;
    posImage.w = 800;
    posImage.h = 600;

    // ------------------------------
    // Initialiser SDL2_mixer
    // ------------------------------
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return 1;
    }
    son = Mix_LoadWAV("palestine.mp3");
    if (!son) {
        printf("Erreur Mix_LoadWAV : %s\n", Mix_GetError());
        return 1;
    }
    Mix_PlayChannel(-1, son, -1); // joue en boucle

    // ------------------------------
    // Initialiser SDL2_ttf
    // ------------------------------
    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        return 1;
    }
    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        return 1;
    }
    SDL_Color couleurNoire = {0, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font,
        "from the river to the sea Palestine will be free",
        couleurNoire);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    textPosition.x = 200;
    textPosition.y = 200;
    textPosition.w = 400;
    textPosition.h = 50;

    // ------------------------------
    // Boucle principale
    // ------------------------------
    while (running) {
        // ------------------------------
        // Gestion des événements
        // ------------------------------
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
            if (event.type == SDL_MOUSEBUTTONDOWN)
                init = 1;
        }

        // ------------------------------
        // Effacer le renderer (fond blanc)
        // ------------------------------
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // ------------------------------
        // Afficher l'image sur tout l'écran
        // ------------------------------
        SDL_RenderCopy(renderer, image, NULL, &posImage);

        // ------------------------------
        // Afficher le texte si init = 1
        // ------------------------------
        if (init == 1) {
            SDL_RenderCopy(renderer, textTexture, NULL, &textPosition);
        }

        // ------------------------------
        // Mettre à jour l'écran
        // ------------------------------
        SDL_RenderPresent(renderer);
    }

    // ------------------------------
    // Libération des ressources
    // ------------------------------
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    Mix_FreeChunk(son);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


