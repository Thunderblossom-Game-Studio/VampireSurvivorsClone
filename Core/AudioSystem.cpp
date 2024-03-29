#include "AudioSystem.h"
#include "SDL_mixer.h"
#include <iostream>

using namespace std;

AudioSystem::AudioSystem(token)
{
	//Init();
}

AudioSystem::~AudioSystem()
{
	Mix_HaltMusic(); // stops music
	Cleanup(); // Free mixer
	Mix_Quit(); // quits mixer
}

void AudioSystem::Init()
{
	int _init = Mix_Init(MIX_INIT_MP3);
	if (!_init)
	{
		std::cout << "Failed to initialize SDL_Mixer. SDL_Mixer error: " << Mix_GetError() << std::endl;
		return;
	}
	else
	{
		std::cout << "Audio Initialization Succeded" << std::endl;
	}

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		std::cout << "Failed to open audio. SDL_Mixer error: " << Mix_GetError() << std::endl;
		return;
	}
	else
	{
		std::cout << "Audio Opened Successfully" << std::endl;
	}

	cout << _audioData.size() << endl;
}

void AudioSystem::LoadAudio(const string& name,const string& audioDirect)
{
	const std::string extension = audioDirect.substr(audioDirect.find_last_of(".") + 1);

	if (extension == "wav") _audioData[name]._type = AUDIO_TYPE_WAV;
	else if (extension == "mp3") _audioData[name]._type = AUDIO_TYPE_MP3;
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

	cout << _audioData.size() << endl;
}

void AudioSystem::PlayAudio(int audioChannel, const string& name, int extraLoops)
{
	switch (_audioData[name]._type)
	{
	case AUDIO_TYPE_WAV:
		Mix_PlayChannel(audioChannel, _audioData[name]._sound, extraLoops);
		break;
	case AUDIO_TYPE_MP3:
		Mix_PlayMusic(_audioData[name]._music, extraLoops);
		break;
	}

	cout << _audioData.size() << endl;
}

void AudioSystem::Cleanup()
{
	for (auto& [key, value]: _audioData)
	{
		switch (value._type)
		{
		case AUDIO_TYPE_WAV:
			Mix_FreeChunk(value._sound);
			break;
		case AUDIO_TYPE_MP3:
			Mix_FreeMusic(value._music);
			break;
		default:
			break;
		}
	}

	cout << _audioData.size() << endl;
}

std::map<std::string, AudioData>& AudioSystem::GetAudioData()
{
	return _audioData;
}
