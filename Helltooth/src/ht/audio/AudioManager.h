#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <vector>

#include "Audio.h"

#include "maths/vec3.h"
#include "maths/mat4.h"

#include "tools/VFS/VFS.h"

#include "utils/Log.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace audio {

	class AudioManager {
	private:
		static AudioManager* instance;

		std::vector<const Audio*> audios;

		ALCdevice* device;
		ALCcontext* context;

	public:
		AudioManager();
		~AudioManager();

		uint32 createAudioFromFile(utils::String path);

		const Audio* getAudio(uint32 id) { return audios[id]; }

		__forceinline void setListenerPosition(maths::vec3 pos) { alListener3f(AL_POSITION, pos.x, pos.y, pos.z); }
		__forceinline void setListenerPosition(float x, float y, float z) { alListener3f(AL_POSITION, x, y, z); }

		__forceinline void setListenerDirection(maths::mat4 view) {
			f32 data[6];
			data[0] = -view[2 + 0 * 4];
			data[1] = -view[2 + 1 * 4];
			data[2] = -view[2 + 2 * 4];
			data[3] = view[1 + 0 * 4];
			data[4] = view[1 + 1 * 4];
			data[5] = view[1 + 2 * 4];
			alListenerfv(AL_ORIENTATION, data); 
		}
		__forceinline void setListenerDirection(float x, float y, float z) { alListener3f(AL_ORIENTATION, x, y, z); }

		__forceinline void setListenerVelocity(maths::vec3 vel) { alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z); }
		__forceinline void setListenerVelocity(float x, float y, float z) { alListener3f(AL_VELOCITY, x, y, z); }

		__forceinline static void Init() {
			if (instance) { HT_ERROR("[AudioManager] Reinitialization not possible!"); return; }
			instance = htnew AudioManager();
		}
		__forceinline static AudioManager* Get() {
			if (!instance) { Init(); HT_ERROR("[AudioManager] AudioManager not initialized, initialization forced!"); }
			return instance;
		}

		__forceinline static void End() {
			if (!instance) { HT_ERROR("[AudioManager] Deletion not possible, AudioManager not initialized!"); return; }
			del instance;
			instance = nullptr;
		}
	};

} }
