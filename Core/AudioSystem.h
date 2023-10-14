#pragma once

#include <vector>
#include <map>
#include <string>
#include <SDL_mixer.h>

enum AudioType
{
	AUDIO_TYPE_MP3,
	AUDIO_TYPE_WAV
};

struct AudioData
{
	AudioType _type;
	Mix_Chunk* _sound;
	Mix_Music* _music;
	// int channel
};

class AudioSystem
{
private:

	std::map<std::string, AudioData> _audioData;

	AudioSystem();

	~AudioSystem();

public:
	static AudioSystem& getInstance();

	AudioSystem(AudioSystem const&) = delete;

	void operator=(AudioSystem const&) = delete;

	void InitializeAudioSystem();

	void LoadAudio(const std::string& name, const std::string& audioDirect);

	void PlayAudio(int audioChannell, const std::string& name, int extraLoops);

	void CleanAudioSystem();


};

