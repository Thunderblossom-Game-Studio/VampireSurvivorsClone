#pragma once

#include <SDL_video.h>
#include <SDL_image.h>


class SpriteSheet
{
public:
	SpriteSheet(char const* path, int row, int column);
    ~SpriteSheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position);

private:
    SDL_Rect     m_clip;
    SDL_Surface* m_spritesheet_image;
};

