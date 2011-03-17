/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUND_ENGINE_H
#define RB_SOUND_ENGINE_H

#include <string>

#include "SoundParameters.h"
#include "AudioEngine.h"

namespace RedBox {
	class SoundFX;
	struct SoundInfo;
	/**
	 * Abstract class for sound engines. Audio engine implementations for sound
	 * effects must inherit from this class and implement the required abstract
	 * functions.
	 * @ingroup Audio
	 */
	class SoundEngine : public AudioEngine {
		friend class ResourceManager;
	public:
		/**
		 * Constructs a sound effect. Gets the sound's data associated with the
		 * key.
		 * @param key Identifier for the sound data to use. The sound data needs
		 * to be loaded beforehand.
		 * @param survive Used to specify if the sound effect's destroy is
		 * managed by the user or by the engine when the sound is done playing.
		 * This lets the user simply call this function and play the sound
		 * directly if survive is at false or keep it and re-use it if surive is
		 * at true.
		 * @return Sound effect generated by this function, the user will either
		 * have to destroy it manually if survive is set at true, or will be
		 * automatically destroyed once the sound's state is at STOPPED. The
		 * sound effect returned is at the INITIAL state.
		 */
		virtual SoundFX* getSoundFX(const std::string& key, bool survive) = 0;
	protected:
		/**
		 * Default constructor. Engine initialization is specifically done in
		 * the init() method inherited from AudioEngine.
		 */
		SoundEngine();
		/**
		 * Destructor. Unloads the sound engine.
		 */
		virtual ~SoundEngine();
		/**
		 * Loads sound data from a file.
		 * @param filePath Path to the sound file to load.
		 * @return Pointer to the sound data loaded.
		 */
		virtual SoundInfo* loadSound(const std::string& filePath) = 0;
		/**
		 * Loads sound data from engine specific parameters.
		 * @param params Parameters to use to load the sound data. Each engine
		 * has implementation different parameters.
		 * @return Pointer to the sound data loaded.
		 */
		virtual SoundInfo* loadSound(const SoundParameters& params) = 0;
		/**
		 * Unloads sound data.
		 * @param sound Sound data that needs to be unloaded. Delete must not be
		 * called on it, the resource manager that calls this function takes
		 * care of that.
		 * @return True if the unloading was successful, false if not.
		 */
		virtual bool unloadSound(SoundInfo* sound) = 0;
	};
}

#endif