#pragma once

#include <AL/al.h>
#include <AL/alext.h>

#include "Audio.h"
#include "AudioManager.h"


namespace ht { namespace audio {

	class Source {
	private:
		uint32 sourceID;

	public:
		Source(const Audio* audio);
		Source(uint32 audio);
		~Source();

		__forceinline void setPosition(maths::vec3 pos) { alSource3f(sourceID, AL_POSITION, pos.x, pos.y, pos.z); }
		__forceinline void setPosition(float x, float y, float z) { alSource3f(sourceID, AL_POSITION, x, y, z); }

		__forceinline void play() { alSourcePlay(sourceID); }
		__forceinline void pause() { alSourcePause(sourceID); }
		__forceinline void loop(bool looping) { alSourcei(sourceID, AL_LOOPING, looping == true ? AL_TRUE : AL_FALSE); }
		__forceinline void stop() { alSourceStop(sourceID); }
	};

} }