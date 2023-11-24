#pragma once

#include <vector>
#include <map>
#include <string>
#include <SDL_mixer.h>
#include "../Templates/Singleton.h"
#include <memory>

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
};

class AudioSystem : public Singleton<AudioSystem>
{
private:	
	std::map<std::string, AudioData> _audioData;

public:
	AudioSystem(token);
	~AudioSystem();

	void Init();

	void LoadAudio(const std::string& name, const std::string& audioDirect);

	void PlayAudio(int audioChannel, const std::string& name, int extraLoops);

	void Cleanup();

	std::map<std::string, AudioData>& GetAudioData();
};

