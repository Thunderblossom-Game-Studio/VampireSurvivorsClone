#include "IUIObject.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../Core/AssetManager.h"

//IUIObject::IUIObject(SDL_Renderer* renderer, const std::string& fontFile, int fontSize, SDL_Color textColor) {
    //_font = TTF_OpenFont(fontFile.c_str(), fontSize);
   // _color = textColor;

   

//}

IUIObject::IUIObject(std::string font, std::string text)
{
    if (font.size() == 0 || text.size() == 0())
    {
        return;
    }


    _renderSpace = GameRenderer::RenderSpace::UI;

    UpdateText(text);

    UpdateFont(font);

}

IUIObject::~IUIObject() {
}


void IUIObject::UpdateTextTexture()
{
    if (_string.size() == 0 || !_font)
    {
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(_font, _string.c_str(), _color);

    _texture = SDL_CreateTextureFromSurface(RenderInstanceManager::instance().GetRenderer("main")->GetRenderer(), textSurface);

    _src = { 0, 0, 32 * (int)_string.size(), 160 };

    SDL_FreeSurface(textSurface);

}

void IUIObject::UpdateText(std::string text)
{
    if (text.size() == 0 || _string == text)
    {
        return;
    }

    _string = text;

    UpdateTextTexture();

}

void IUIObject::UpdateFont(std::string _fontpath)
{
    TTF_Font* _newfont = AssetManager::instance().LoadFont(_fontpath);

    if (_newfont == NULL or _font == _newfont)
    {
        return;
    }

    _font = _newfont;

    UpdateTextTexture();

}
