#include "AudioManager.h"

namespace ht { namespace audio {
	using namespace utils;

	AudioManager *AudioManager::instance = nullptr;

	AudioManager::AudioManager() {
		device = alcOpenDevice(NULL);

		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);

		setListenerPosition(0, 0, 0);
		setListenerVelocity(0, 0, 0);
	}

	AudioManager::~AudioManager() {
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	uint32 AudioManager::createAudioFromFile(String path) {
		String realPath;
		VFS::resolvePhysicalPath(path, realPath);

		Audio* audio = htnew Audio(realPath);
		audios.push_back(audio);

		return audios.size() - 1;
	}

} }