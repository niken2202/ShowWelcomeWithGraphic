
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FONT_SIZE 70

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <algorithm>
class SDL_Texture;
class SDL_Window;
class SDL_Renderer;

class Window {
          
    public:
                                Window();
    virtual                     ~Window(){};
    void                        Init();
    void                        DrawScreen();
    
    private:
    bool                        m_Init;
    SDL_Event                   m_Event;
  
    SDL_Window*                 m_Window;
    SDL_Texture*                m_Screen;
    SDL_Renderer*               m_Renderer;
    TTF_Font*                   font ;
    void                        RenderText(std::string s, int y);
    void                        TextInput();
};
