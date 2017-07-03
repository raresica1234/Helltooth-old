#pragma once

#include <AL/al.h>
#include <AL/alext.h>

#include <fstream>

#include "utils/String.h"

namespace ht { namespace audio {

	class Audio {
	private:
		friend struct WaveHeader;

		uint32 bufferID;

	public:
		Audio(utils::String path);
		~Audio();

		__forceinline uint32 getID() const { return bufferID; }

	private:
		void loadWaveFile(utils::String path, WaveHeader* header);
		uint32 getFormat(WaveHeader* header);

	};

} }