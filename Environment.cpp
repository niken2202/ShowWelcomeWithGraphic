
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
    font = TTF_OpenFont("font//BrookeS8.ttf", FONT_SIZE);
    //TTF_SetFontStyle(font, TTF_STYLE_STRIKETHROUGH);

    m_Init = true;
}

void Window::DrawScreen()
{
    std::string name = "";
    bool stop = false;
    while (!stop)
    {
        SDL_RenderCopy(m_Renderer, m_Screen, NULL, NULL);
        RenderText("What is your name ?", SDL_GetWindowSurface(m_Window)->h / 3);
        RenderText(name, SDL_GetWindowSurface(m_Window)->h / 2);
        SDL_RenderPresent(m_Renderer);

        while (SDL_PollEvent(&m_Event) != 0)
        {
            if (m_Event.type == SDL_KEYDOWN && m_Event.key.keysym.sym == SDLK_ESCAPE)
            {
                stop = true;
            }
            else if (m_Event.type == SDL_TEXTINPUT)
            {
                system("clear");
                name += m_Event.text.text;
            }
            else if (m_Event.type == SDL_KEYDOWN && m_Event.key.keysym.sym == SDLK_KP_ENTER)
            {
                
            }
            else if (m_Event.type == SDL_KEYDOWN && m_Event.key.keysym.sym == SDLK_BACKSPACE)
            {
                name.erase(name.end() - 1);
            }
        }

       
    }

    SDL_RenderClear(m_Renderer);
}

void Window::RenderText(std::string s, int y)
{

    SDL_Color White = {255, 255, 255};

    char const *pchar = s.c_str();
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, pchar, White);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);

    SDL_Rect Message_rect;
    int w, h;
    if (TTF_SizeText(font, pchar, &w, &h))
    {
        std::cout << "Error check font size!" << std::endl;
        return;
    }

    Message_rect.w = w;                                             // controls the width of the rect
    Message_rect.h = h;                                             // controls the height of the rect
    Message_rect.x = SDL_GetWindowSurface(m_Window)->w / 2 - w / 2; //controls the rect's x coordinate
    Message_rect.y = y;                                             // controls the rect's y coordinte

    SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
void Window::TextInput()
{
    std::string text = "";
    SDL_StartTextInput();
}