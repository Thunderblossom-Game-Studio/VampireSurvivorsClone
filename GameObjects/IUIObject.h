#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "IRenderableObject.h"

class IUIObject : public IRenderableObject
{
public:
    //IUIObject(SDL_Renderer* renderer, const std::string& fontFile, int fontSize, SDL_Color textColor);
    IUIObject(std::string font, std::string text);
    virtual ~IUIObject();
   //#virtual void RenderText(const std::string& text, int x, int y) = 0;
    virtual float GetX() const = 0;
    virtual float GetY() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    void UpdateTextTexture();
    void UpdateText(std::string text);
    void UpdateFont(std::string fontpath);

protected:
    TTF_Font* _font;
    std::string _string;
};