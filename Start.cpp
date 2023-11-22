#include "Start.h"

GameMenu::GameMenu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren)
    : Menu(x, y, buttonWidth, buttonHeight, sliderWidth, sliderHeight, maxChildren) {
    // Additional initialization specific to GameMenu
}

// Override or add additional member functions specific to GameMenu
void GameMenu::CustomGameMenuFunction() {
    std::cout << "Executing a custom function in GameMenu\n";
}

// Override HandleKeyPress to add additional functionality
void GameMenu::HandleKeyPress(SDL_Event& event) {
    Menu::HandleKeyPress(event); // Call the base class implementation

    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
            CustomGameMenuFunction();
            break;

            // Add more cases for other keys as needed
        }
        break;

        // Add more cases for other event types as needed
    }
}
