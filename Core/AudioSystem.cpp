#include "AudioSystem.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

AudioSystem::AudioSystem()
{
	InitializeAudioSystem();
}

AudioSystem::~AudioSystem()
{
	Mix_HaltMusic(); // stops music
	Mix_Quit(); // quits mixer
}

AudioSystem& AudioSystem::getInstance()
{
	static AudioSystem instance;

	return instance;
}

void AudioSystem::InitializeAudioSystem()
{
	int _initted = Mix_Init(MIX_INIT_MP3);
	if (_initted == 0)
	{
		std::cout << "Failed to initialize SDL_Mixer. SDL_Mixer error: " << Mix_GetError() << std::endl;
	}
	else
	{
		std::cout << "Audio Initialization Succeded" << std::endl;
	}

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		std::cout << "Failed to open audio. SDL_Mixer error: " << Mix_GetError() << std::endl;
	}
	else
	{
		std::cout << "Audio Opened Successfully" << std::endl;
	}
}

void AudioSystem::LoadAudio(const string& name,const string& audioDirect)
{

	std::string extention = audioDirect.substr(audioDirect.find_last_of(".") + 1);

	if (extention == "wav") _audioData[name]._type = AUDIO_TYPE_WAV;
	else if (extention == "mp3") _audioData[name]._type = AUDIO_TYPE_MP3;
	else return;

	switch (_audioData[name]._type)
	{
	case AUDIO_TYPE_WAV:
		_audioData[name]._sound = Mix_LoadWAV(audioDirect.c_str());
		break;
	case AUDIO_TYPE_MP3:
		_audioData[name]._music = Mix_LoadMUS(audioDirect.c_str());
		break;
	}
}

void AudioSystem::PlayAudio(int audioChannell, const string& name, int extraLoops)
{
	switch (_audioData[name]._type)
	{
	case AUDIO_TYPE_WAV:
		Mix_PlayChannel(audioChannell, _audioData[name]._sound, extraLoops);
		break;
	case AUDIO_TYPE_MP3:
		Mix_PlayMusic(_audioData[name]._music, extraLoops);
		break;
	}
}

void AudioSystem::CleanAudioSystem()
{
	for (auto& ptr : _audioData)
	{
		switch (ptr.second._type)
		{
		case AUDIO_TYPE_WAV:
			Mix_FreeChunk(ptr.second._sound);
			break;
		case AUDIO_TYPE_MP3:
			Mix_FreeMusic(ptr.second._music);
			break;
		}

	}


}