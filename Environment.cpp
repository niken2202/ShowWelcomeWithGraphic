
#include "Environment.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Window::Window() : m_Window(NULL),
                   m_Screen(NULL),
                   m_Renderer(NULL),
                   m_Init(false)
{
}

void Window::Init()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error: Could not init SDL\n"
                  << SDL_GetError();
        m_Init = false;
        return;
    }

    m_Window = SDL_CreateWindow("Where is my 500K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_Window == nullptr)
    {
        std::cout << "Error: Could not create SDL Window" << std::endl;
        m_Init = false;
        return;
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_Renderer)
    {
        std::cout << "Could not create renderer\n"
                  << SDL_GetError();
        m_Init = false;
        return;
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
    {
        std::cout << "Error: Could not init SDL_image" << std::endl;
        m_Init = false;
        return;
    }

    SDL_Surface *surface = NULL;

    surface = IMG_Load("img//background.jpg");

    if (!surface)
    {
        std::cout << " Could not loadd Screen\n"
                  << IMG_GetError();
        return;
    }

    m_Screen = SDL_CreateTextureFromSurface(m_Renderer, surface);

    if (!m_Screen)
    {
        std::cout << "Could not draw Screen\n"
                  << SDL_GetError();
        return;
    }
    else
        std::cout << "Loaded Screen" << std::endl;

    SDL_FreeSurface(surface);
   
    TTF_Init();
    font = TTF_OpenFont("font//Vegan Style Personal Use.ttf",80);
   //TTF_SetFontStyle(font, TTF_STYLE_STRIKETHROUGH);

    m_Init = true;
}

void Window::DrawScreen()
{
    bool stop = false;
    while (!stop)
    {
        while (SDL_PollEvent(&m_Event) != 0)
        {
            if (m_Event.type == SDL_KEYDOWN && m_Event.key.keysym.sym == SDLK_ESCAPE)
            {
                stop = true;
            }
           
        }

        SDL_RenderCopy(m_Renderer, m_Screen, NULL, NULL);
        RenderText("What is your name ?");
        SDL_RenderPresent(m_Renderer);
    }

    SDL_RenderClear(m_Renderer);
}

void Window::RenderText(std::string s){

    SDL_Color White = {255, 255, 255}; 
    
    char const *pchar = s.c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, pchar, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage); 
    SDL_Rect Message_rect; //create a rect

    Message_rect.x = SDL_GetWindowSurface(m_Window)->w/2-250;  //controls the rect's x coordinate
    Message_rect.y = SDL_GetWindowSurface(m_Window)->w/9; // controls the rect's y coordinte
  
    Message_rect.w =500; // controls the width of the rect
    Message_rect.h = 80; // controls the height of the rect

    SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}