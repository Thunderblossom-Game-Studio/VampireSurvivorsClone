#include "IUIObject.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../Core/AssetManager.h"

//IUIObject::IUIObject(SDL_Renderer* renderer, const std::string& fontFile, int fontSize, SDL_Color textColor) {
    //_font = TTF_OpenFont(fontFile.c_str(), fontSize);
   // _color = textColor;

   

//}

IUIObject::IUIObject(std::string text, std::string font)
{
    if (font.size() == 0 || text.size() == 0())
    {
        return;
    }


    _renderSpace = GameRenderer::RenderSpace::UI;

    UpdateText(text);

    UpdateText(font);

}

IUIObject::~IUIObject() {
    TTF_CloseFont(_font);
}

//SDL_Surface* IUIObject::CreateTextSurface(const std::string& text) {
  //  return TTF_RenderText_Solid(font, text.c_str(), color);
//}

//void IUIObject::RenderText(const std::string& text, int x, int y) {
    /*SDL_Surface* textSurface = CreateTextSurface(text);
    _texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = textSurface->w;
    destRect.h = textSurface->h;

    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);*/
//}

void IUIObject::UpdateTextTexture()
{
    if (_string.size() == 0 && _font)
    {
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(_font, _string.c_str(), _color);

    _texture = SDL_CreateTextureFromSurface(RenderInstanceManager::instance().GetRenderer("main")->GetRenderer(), textSurface);

    _src = { 0, 0, 32 * (int)_string.size() == 0, 160 };

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
