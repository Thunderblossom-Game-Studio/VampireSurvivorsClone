#include "Menu.h"

Menu::Menu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren)
    : x{ x }, y{ y }, buttonWidth{ buttonWidth }, buttonHeight{ buttonHeight }, sliderWidth{ sliderWidth }, sliderHeight{ sliderHeight }, maxChildren{ maxChildren }, activeChild{ 1 } 
{
}

// Set alpha of children on/off
void Menu::SetAlpha(bool enable) {
    for (int i = 0; i < maxChildren; ++i) {
        buttons[i].SetAlpha(enable);
        sliders[i].SetAlpha(enable);
    }
}

// Handle key presses to change highlighted button accordingly
void Menu::HandleKeyPress(SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            HighlightButton(-1);
            break;

        case SDLK_DOWN:
            HighlightButton(1);
            break;

            // Add more cases for other keys as needed
        }
        break;

        // Add more cases for other event types as needed
    }
}

// Generate buttons with given location, value, and colors
void Menu::GenerateButtons() {
    for (int i = 0; i < maxChildren; ++i) {
        buttons.emplace_back(x, y + i * buttonHeight, buttonWidth, buttonHeight);
        buttons[i].SetAlpha(false); // Initial alpha is set to false
        // Set other properties of the buttons as needed
    }
}

// Generate sliders with given location, value, and colors
void Menu::GenerateSliders() {
    for (int i = 0; i < maxChildren; ++i) {
        sliders.emplace_back(x, y + i * (buttonHeight + sliderHeight), sliderWidth, sliderHeight, buttonWidth, buttonHeight, 5);
        sliders[i].SetAlpha(false); // Initial alpha is set to false
        // Set other properties of the sliders as needed
    }
}

// Change the highlighted button based on the key press (Up or Down)
void Menu::HighlightButton(int direction) {
    buttons[activeChild - 1].SetAlpha(true); // Set the previous button to the default state
    activeChild += direction;

    // Wrap around to the other end if reaching the maximum or minimum
    if (activeChild > maxChildren) {
        activeChild = 1;
    }
    else if (activeChild < 1) {
        activeChild = maxChildren;
    }

    buttons[activeChild - 1].SetAlpha(true); // Set the new active button to the highlighted state
}
