#include "SliderUI.h"

Slider::Slider(int x, int y, int barWidth, int barHeight, int buttonWidth, int buttonHeight, int increments)
    : barRect{ x, y, barWidth, barHeight }, buttonRect{ x, y, buttonWidth, buttonHeight }, increments{ increments }, selected{ false } {}

// Standard render call
void Slider::Render(SDL_Renderer* renderer) {
    if (isVisible) {
        // Set alpha value for the bar
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, alpha);

        // Render the bar
        SDL_RenderFillRect(renderer, &barRect);

        // Set alpha value for the button
        SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, alpha);

        // Render the button
        SDL_RenderFillRect(renderer, &buttonRect);
    }
}

// Enable/Disable alpha
void Slider::SetAlpha(bool enable) {
    if (enable) {
        alpha = 255; // Fully opaque
    }
    else {
        alpha = 0;   // Fully transparent
    }
}

// Move the button up (decrease its y-coordinate)
void Slider::MoveUp() {
    if (buttonRect.y > barRect.y) {
        buttonRect.y -= barRect.h / increments;
    }
}

// Move the button down (increase its y-coordinate)
void Slider::MoveDown() {
    if (buttonRect.y + buttonRect.h < barRect.y + barRect.h) {
        buttonRect.y += barRect.h / increments;
    }
}

// Set the slider state to selected
void Slider::SetSelected() {
    selected = true;
}

// Reset the slider state to its default
void Slider::ResetState() {
    selected = false;
}
