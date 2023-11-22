#include "Button.h"

Button::Button(int x, int y, int width, int height)
    : rect{ x, y, width, height }, baseColor{ 255, 255, 255 }, highlightColor{ 255, 255, 255 }, selectColor{ 255, 255, 255 }, alpha{ 255 }, isSelected{ false } {}

// Standard render call
void Button::Render(SDL_Renderer* renderer) {
    if (isVisible) {
        // Set alpha value
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, baseColor.r, baseColor.g, baseColor.b, alpha);

        // Render the button
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Enable/Disable alpha
void Button::SetAlpha(bool enable) {
    if (enable) {
        alpha = 255; // Fully opaque
    }
    else {
        alpha = 0;   // Fully transparent
    }
}

// Set the button state to highlighted
void Button::SetHighlighted() {
    baseColor = highlightColor;
}

// Set the button state to selected/pressed
void Button::SetSelected() {
    baseColor = selectColor;
    isSelected = true;
}

// Reset the button state to its default
void Button::ResetState() {
    baseColor = { 255, 255, 255 }; // Reset to default color
    isSelected = false;
}
