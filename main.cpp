#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "SDL Version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << std::endl;

	return 0;
}

