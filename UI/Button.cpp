#include "Button.h"
#include "../Rendering/RenderInstanceManager.h"
Button::Button(float x, float y, float width, float height)
    : _position{ Vector2 (x, y) }, _width{ width }, _height{height}, highlightColor{ 15,122,176, 0 }, selectColor{ 221,78,44, 0 }, alpha{ 255 }, isSelected{ false }
{
    _color = { 255, 255, 255 };
    RenderInstanceManager::instance().GetRenderer("main")->AddToRenderList(this);
}

// Set the button state to highlighted
void Button::SetHighlighted() {
    _color = highlightColor;
}

// Set the button state to selected/pressed
void Button::SetSelected() {
    _color = selectColor;
    isSelected = true;
}

// Reset the button state to its default
void Button::ResetState() {
    _color = { 255, 255, 255 }; // Reset to default color
    isSelected = false;
}
