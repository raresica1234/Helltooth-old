#include "Audio.h"

namespace ht { namespace audio {
	using namespace utils;

#pragma region WaveHeader

	struct RIFFHeader {
		char data[4];
		uint32 dataSize;
		uint32 format;
	};

	struct FormatHeader {
		char data[4];
		uint32 dataSize;
		uint16 format;
		uint16 channels;
		uint32 sampleRate;
		uint32 byteRate;
		uint16 blockAlign;
		uint16 bitsPerSample;
	};

	struct DataHeader {
		char data[4];
		uint16 dataSize;
	};

	struct WaveHeader {
		RIFFHeader riff;
		FormatHeader format;
		DataHeader data;
		char* rawData = nullptr;
	};

#pragma endregion

	Audio::Audio(String path) {
		WaveHeader header;

		loadWaveFile(path, &header);

		alGenBuffers(1, &bufferID);

		alBufferData(bufferID, getFormat(&header), header.rawData, header.data.dataSize, header.format.sampleRate);

	}

	Audio::~Audio() {
		alDeleteBuffers(1, &bufferID);
	}

	void Audio::loadWaveFile(String path, WaveHeader* header) {
		std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);

		file.read((char*)header, sizeof(WaveHeader) - sizeof(char*));

		if (memcmp(header->riff.data, "RIFF", 4) != 0) {
			HT_ERROR("[Audio] RIFF Header corrupted!");
		}

		if (memcmp(header->format.data, "fmt", 3) != 0) {
			HT_ERROR("[Audio] Format Header corrupted!");
		}

		if (memcmp(header->data.data, "data", 4) != 0) {
			HT_ERROR("[Audio] Data Header corrupted!");
		}

		header->rawData = htnew char[header->data.dataSize];
		
		file.read(header->rawData, header->data.dataSize);
		file.close();
	}


	uint32 Audio::getFormat(WaveHeader* header) {
		switch (header->format.channels) {
		case 1:
			switch (header->format.bitsPerSample) {
			case 8:
				return AL_FORMAT_MONO8;
			case 16:
				return AL_FORMAT_MONO16;
			case 32:
				return AL_FORMAT_MONO_FLOAT32;
			}

		case 2:
			switch (header->format.bitsPerSample) {
			case 8:
				return AL_FORMAT_STEREO8;
			case 16:
				return AL_FORMAT_STEREO16;
			case 32:
				return AL_FORMAT_STEREO_FLOAT32;
			}

		case 6:
			switch (header->format.bitsPerSample) {
			case 8:
				return AL_FORMAT_51CHN8;
			case 16:
				return AL_FORMAT_51CHN16;
			case 32:
				return AL_FORMAT_51CHN32;
			}

		case 8:
			switch (header->format.bitsPerSample) {
			case 8:
				return AL_FORMAT_71CHN8;
			case 16:
				return AL_FORMAT_71CHN16;
			case 32:
				return AL_FORMAT_71CHN32;
			}
		}

		return 0;
	}

} }