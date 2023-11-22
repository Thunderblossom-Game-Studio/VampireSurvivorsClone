#include "Death.h"

End::End(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren)
    : Menu(x, y, buttonWidth, buttonHeight, sliderWidth, sliderHeight, maxChildren) {
    // Additional initialization specific to End
}

// Override HandleKeyPress to add additional functionality
void End::HandleKeyPress(SDL_Event& event) {
    Menu::HandleKeyPress(event); // Call the base class implementation

    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            // Add cases for other keys as needed
        }
        break;

        // Add more cases for other event types as needed
    }
}

// Override Render to add additional rendering logic
void End::Render() {
    Menu::Render(); // Call the base class implementation

    // Additional rendering logic specific to End goes here
}
