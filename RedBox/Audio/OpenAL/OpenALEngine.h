/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_ENGINE_H
#define RB_OPENAL_ENGINE_H

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <string>
#include <vector>

#include "AudioEngine.h"

namespace RedBox {
	/**
	 * Audio engine using OpenAL to play the sounds.
	 * @ingroup Audio
	 */
	class OpenALEngine: public AudioEngine {
		friend class AudioEngine;
	public:
		/**
		 * Initializes OpenAL.
		 */
		void init();
		/**
		 * Updates OpenAL.
		 */
		void update();
		/**
		 * Sets the default device to use for audio output. Must be called
		 * before initializing the engine.
		 * @param newDevice Name of the device to set as the default device.
		 */
		static void setDefaultDevice(const std::string& newDevice);
		/**
		 * Gets the list of available auio devices on the system.
		 * @return Vector containing the device names.
		 */
		static const std::vector<std::string>& getDeviceList();
	private:
		/// Device to load.
		static std::string defaultDevice;
		/// List of devices available.
		static std::vector<std::string> deviceList;
		/**
		 * Default constructor.
		 */
		OpenALEngine();
		/**
		 * Loads a sound effect from a file. For now, it must be a wav file.
		 * @param filePath Path to the sound effect's file.
		 * @return Pointer to the loaded sound effect.
		 Null if the loading failed.
		 */
		SoundFX* loadSoundFX(const std::string& filePath);
		/**
		 * Loads a sound effect from information.
		 * @param info Information about the sound effect to load.
		 * @return Pointer to the loaded sound effect. Null if the loading
		 * failed.
		 */
		SoundFX* loadSoundFX(const SoundInfo& info);
		/**
		 * Loads a background music from a file. For now, it must be a wav file.
		 * @param filePath Path to the music's file.
		 * @return Pointer to loaded music. Null if the loading failed.
		 */
		BackgroundMusic* loadBackgroundMusic(const std::string& filePath);
		/**
		 * Loads a background music from information.
		 * @param info Information about the music to load.
		 * @return Pointer to the loaded music. Null if the loading failed.
		 */
		BackgroundMusic* loadBackgroundMusic(const MusicInfo& info);
		/**
		 * Destructor, closes OpenAL.
		 */
		~OpenALEngine();
	};
}

#endif