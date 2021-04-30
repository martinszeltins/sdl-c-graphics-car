#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)
#define SPEED (10)

int main(void)
{
    SDL_Init(SDL_RENDERER_ACCELERATED);

    SDL_Window * window = SDL_CreateWindow("Seabattle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface * surface = IMG_Load("img/car.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect sprite;
    SDL_QueryTexture(texture, NULL, NULL, &sprite.w, &sprite.h);

    float x_position = 0;
    float y_position = 0;
    float x_speed = 0;
    float y_speed = 0;

    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    int close_requested = 0;
    

    /**
     * The main loop of the program
     * 
     * This will keep reading user input and drawing the sprite
     * every 1/60th of a second (60 fps).
     */
    while (!close_requested)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close_requested = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            up = 1;
                            break;

                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            left = 1;
                            break;

                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down = 1;
                            break;

                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = 1;
                            break;
                    }

                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            up = 0;
                            break;

                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            left = 0;
                            break;

                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down = 0;
                            break;

                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = 0;
                            break;
                    }

                    break;
            }
        }

        x_speed = 0;
        y_speed = 0;

        if (up && !down) y_speed = -SPEED;
        if (down && !up) y_speed = SPEED;
        if (left && !right) x_speed = -SPEED;
        if (right && !left) x_speed = SPEED;

        x_position = x_position + x_speed;
        y_position = y_position + y_speed;

        sprite.y = (int) y_position;
        sprite.x = (int) x_position;
        
        // clear the window
        SDL_SetRenderDrawColor(renderer, 247, 247, 247, 255);
        SDL_RenderClear(renderer);

        // draw the image to the window
        SDL_RenderCopy(renderer, texture, NULL, &sprite);
        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}