#include "Source.h"

namespace ht { namespace audio {

	Source::Source(const Audio* audio) {
		alGenSources(1, &sourceID);
		alSourcei(sourceID, AL_BUFFER, audio->getID());
	}

	Source::Source(uint32 audio) 
		: Source(AudioManager::Get()->getAudio(audio)) {}

	Source::~Source() {
		alDeleteSources(1, &sourceID);
	}

} }