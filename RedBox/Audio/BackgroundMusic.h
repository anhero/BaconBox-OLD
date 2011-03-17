/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_BACKGROUNDMUSIC_H
#define RB_BACKGROUNDMUSIC_H

#include "Sound.h"

namespace RedBox {
	/**
	 * Abstract class for background musics. Used by engine specific classes for
	 * background music.
	 * @ingroup Audio
	 */
	class BackgroundMusic : public Sound {
		friend class AudioEngine;
		friend class ResourceManager;
	public:
		/**
		 * Destructor.
		 */
		virtual ~BackgroundMusic();
	protected:
		/**
		 * Default constructor. Musics can only be created by the resource
		 * manager or the music engine.
		 */
		BackgroundMusic();
	};
}

#endif
