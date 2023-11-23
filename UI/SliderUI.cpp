#include "SliderUI.h"
#include "Button.h" // Include the header file for Button

Button* button;
Button* base;
float barIncrement;
float currentIncrement = 0;

Slider::Slider(int x, int y, int barWidth, int barHeight, int increments)
    : barRect{ x, y, barWidth, barHeight }, increments{ increments }, selected{ false }
{
    // Create a Button instance
    base = new Button(x, y, barWidth, barHeight);
    // Create a Button instance
    button = new Button(x, y, barWidth/increments, barHeight);
    // base width / increments, for every increment, move the button by base width/increments
    barIncrement = barWidth / increments;
}

// Enable/Disable alpha
void Slider::SetAlpha(bool enable) 
{
    if (enable) 
    {
        base-> alpha = 255; // Fully opaque
        button->alpha = 255; // Fully opaque
    }
    else 
    {
        base-> alpha = 0;   // Fully transparent
        base->alpha = 0;   // Fully transparent
    }
}

// Move the button up (decrease its x-coordinate)
void Slider::MoveUp() 
{
    if (currentIncrement < increments)
    {
        button->SetX(button->GetX() + barIncrement);
    }
}

// Move the button down (increase its x-coordinate)
void Slider::MoveDown() 
{
    if (currentIncrement > 0 )
    {
        button->SetX(button->GetX() - barIncrement);
    }
}

// Set the slider state to selected
void Slider::SetSelected() 
{
    selected = true;
}

// Reset the slider state to its default
void Slider::ResetState() 
{
    selected = false;
}
