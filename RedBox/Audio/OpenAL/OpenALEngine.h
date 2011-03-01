/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_ENGINE_H
#define RB_OPENAL_ENGINE_H

#include <string>

#include "AudioEngine.h"

namespace RedBox {
	class OpenALEngine: public AudioEngine {
	public:
		void init();
		void update();
	private:
		OpenALEngine();
		SoundFX* loadSoundFX(const std::string& filePath);
		SoundFX* loadSoundFX(const SoundInfo& info);
		BackgroundMusic* loadBackgroundMusic(const std::string& filePath);
		BackgroundMusic* loadBackgroundMusic(const MusicInfo& info);
		~OpenALEngine();
	};
}

#endif