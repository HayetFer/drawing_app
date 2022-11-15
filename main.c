#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void clear(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void drawrect(SDL_Renderer * renderer, SDL_Rect * rectangle) {
    /*rect*/
    
    SDL_RenderFillRect(renderer, rectangle);
    SDL_RenderPresent(renderer);
}

/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


int main(int argc, char **argv) {
    int LENGTH = 8;
    int WIDTH = 8;
    SDL_Rect rectangle;
    rectangle.x= 300;
    rectangle.y=300;
    rectangle.w=WIDTH;
    rectangle.h=LENGTH;

    /*                TEXT                        */
    SDL_Event event;
    SDL_Rect rect1;
    SDL_Renderer *renderer;
    SDL_Texture *texture1;
    SDL_Window *window;
    char *font_path;
    int quit;

    if (argc == 1) {
        font_path = "FreeSans.ttf";
    } else if (argc == 2) {
        font_path = argv[1];
    } else {
        fprintf(stderr, "error: too many arguments\n");
        exit(EXIT_FAILURE);
    }

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Roboto-Regular.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text_and_rect(renderer, 0, 0, "                               WELCOME TO THE UNIVERSE OF ART    ", font, &texture1, &rect1);

    quit = 0;
    double angle = 0;
    int r = 0;
    int g = 255;
    int b = 255;
    while (!quit) {
        
       
       // angle = angle % 2*3.1415;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
       // SDL_RenderClear(renderer);
        
        

        /* Use TTF textures. */
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        if(SDL_SetRenderDrawColor(renderer, 112, 166, 237, SDL_ALPHA_OPAQUE)!=0){
        printf("no color");
    }
       
        
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                // Handle arrow keys
                switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                         rectangle.x-=10;
                        break;
                    case SDLK_RIGHT:
                        rectangle.x +=10;
                        break;
                    case SDLK_UP:
                        rectangle.y -= 10;
                        break;
                    case SDLK_DOWN:
                        
                        rectangle.y += 10;
                        
                        break;
                    case SDLK_j:
                        r=140;
                        g=134;
                        b=240;

                        break;
                    case SDLK_v:

                        r=250;
                        g=17;
                        b=21;
                        break;

                     	

                    case SDLK_c:
                        rectangle.w+= 5;
                        rectangle.h+= 5;


                    case SDLK_z:
                        r=78;
                        g=212;
                        b=51;
                        break;

                    case SDLK_t:
                        r=168;
                        g=25;
                        b=133;
                        break;

                    case SDLK_b:
                        r=0;
                        g=255;
                        b=255;
 
                    default:
                        break;
                }

                

            } else if (event.type == SDL_QUIT) {
                quit = 1;
                puts("QUIT!");
                break;
            }
            //clear(renderer);

         
        }
       SDL_SetRenderDrawColor(renderer, r, g, b, 255);
       drawrect(renderer, &rectangle);
    
   




    }
    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;

}
