#include "SliderUI.h"

Slider::Slider(int x, int y, int barWidth, int barHeight, int buttonWidth, int buttonHeight, int increments)
    : barRect{ x, y, barWidth, barHeight }, buttonRect{ x, y, buttonWidth, buttonHeight }, increments{ increments }, selected{ false } {}

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
