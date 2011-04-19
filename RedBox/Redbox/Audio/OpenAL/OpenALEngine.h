/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_ENGINE_H
#define RB_OPENAL_ENGINE_H

#include "PlatformFlagger.h"

#ifdef RB_OPENAL
#ifdef RB_WIN32
#include <al.h>
#include <alc.h>
#elif defined(RB_LINUX)
#include <AL/al.h>
#include <AL/alc.h>
#elif defined(RB_APPLE_PLATFORM)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <stdint.h>

#include <string>
#include <vector>
#include <list>

#include "OpenALSoundFX.h"
#include "SoundEngine.h"
#include "SoundParameters.h"

namespace RedBox {
	class SoundFX;
	struct SoundInfo;
	/**
	 * Audio engine using OpenAL to play the sounds.
	 * @ingroup Audio
	 */
	class OpenALEngine: public SoundEngine {
		friend class AudioEngine;
	public:
		/**
		 * Sets the default device to use for audio output. Must be called
		 * before initializing the engine.
		 * @param newDevice Name of the device to set as the default device.
		 */
		void setDefaultDevice(const std::string& newDevice);
		/**
		 * Gets the list of available auio devices on the system.
		 * @return Vector containing the device names.
		 */
		const std::vector<std::string>& getDeviceList();
		/**
		 * Gets OpenALEngine's instance. Retuns NULL if it isn't constructed.
		 */
		static OpenALEngine* getInstance();
		/**
		 * Gets a sound effect. Initializes a sound effect from already loaded
		 * sound effect data.
		 * @param key Key to the sound effect data to use for the sound effect.
		 * @param survive True if the user wants to manage the sound effect by
		 * himself. False if he doesn't want to have to delete the sound
		 * effect after he has started playing it.
		 */
		SoundFX* getSoundFX(const std::string& key, bool survive);
	private:
		/// Chunk ID wav files should have.
		static const uint32_t CHUNK_ID_RIFF = 1179011410;
		/// Format the wav files should have.
		static const uint32_t FORMAT_WAVE = 1163280727;
		/// OpenALEngine's main instance.
		static OpenALEngine* instance;
		/// Device to load.
		std::string defaultDevice;
		/// List of devices available.
		std::vector<std::string> deviceList;
		/// Sources being played.
		std::list<OpenALSoundFX*> sources;
		/**
		 * Default constructor.
		 */
		OpenALEngine();
		/**
		 * Destructor, closes OpenAL.
		 */
		~OpenALEngine();
		/**
		 * Initializes OpenAL.
		 */
		void init();
		/**
		 * Updates OpenAL.
		 */
		void update();
		/**
		 * Loads a sound effect from a file. For now, it must be a wav file.
		 * @param filePath Path to the sound effect's file.
		 * @return Pointer to the loaded sound effect.
		 Null if the loading failed.
		 */
		SoundInfo* loadSound(const std::string& filePath);
		/**
		 * Loads a sound effect from information.
		 * @param info Information about the sound effect to load.
		 * @return Pointer to the loaded sound effect. Null if the loading
		 * failed.
		 */
		SoundInfo* loadSound(const SoundParameters& params);
		/**
		 * Unloads sound data. Called by the resource loader either by demand
		 * of the user or when it is unloading everything before unloading the
		 * audio engine. Will not succeed if there are still sources using the
		 * buffer.
		 * @param sound Sound data to unload.
		 * @return True if the unloading was done correctly, false if not.
		 */
		bool unloadSound(SoundInfo* sound);
		/**
		 * Deletes all sources using a specific buffer.
		 * @param buffer ID of the buffer.
		 */
		void deleteBufferSources(ALuint buffer);
		/**
		 * Loads data from a wav file.
		 * @param fileName Path to the file to load.
		 * @param bufferData Array containing the buffer data of the loaded wav
		 * file.
		 * @param bufferSize Will contain the size of the loaded buffer.
		 * @param format Loaded audio's format.
		 * @param freq Loaded audio's frequency.
		 */
		static void loadWav(const std::string& filePath,
							char*& bufferData,
							ALsizei& bufferSize,
							ALenum& format,
							ALsizei& freq);
	};
}

#endif
#endif
