/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_ENGINE_H
#define RB_OPENAL_ENGINE_H

#include "BaconBox/PlatformFlagger.h"

#include <stdint.h>

#include <string>
#include <vector>
#include <list>

#include "BaconBox/Audio/OpenAL/RBOpenAL.h"
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/SoundParameters.h"

namespace BaconBox {
	class SoundFX;
	class OpenALSoundFX;
	class NullAudio;
	struct SoundInfo;
	/**
	 * Audio engine using OpenAL to play the sounds.
	 * @ingroup Audio
	 */
	class OpenALEngine: public SoundEngine {
		friend class Engine;
	public:
		/**
		 * Converts the BaconBox volume to its OpenAL equivalent.
		 * @param openALVolume OpenAL volume to convert.
		 * @return BaconBox volume equivalent to the OpenAL volume given.
		 */
		static int openALToBaconBoxVolume(float openALVolume);

		/**
		 * Converts the OpenAL volume to its BaconBox equivalent.
		 * @param baconBoxVolume BaconBox volume to convert.
		 * @return OpenAL volume equivalent to the BaconBox volume given.
		 */
		static float baconBoxToOpenALVolume(int baconBoxVolume);

		/**
		 * Sets the default device to use for audio output. Must be called
		 * before initializing the engine.
		 * @param newDevice Name of the device to set as the default device.
		 */
		void setDefaultDevice(const std::string &newDevice);

		/**
		 * Gets the list of available auio devices on the system.
		 * @return Vector containing the device names.
		 */
		const std::vector<std::string>& getDeviceList();
		/**
		 * Gets a sound effect. Initializes a sound effect from already loaded
		 * sound effect data.
		 * @param key Key to the sound effect data to use for the sound effect.
		 * @param survive True if the user wants to manage the sound effect by
		 * himself. False if he doesn't want to have to delete the sound
		 * effect after he has started playing it.
		 */
		SoundFX *getSoundFX(const std::string &key, bool survive);

		/**
		 * Sets the global sound effects volume.
		 * @param newSoundVolume New global sound effects volume.
		 * @see BaconBox::SoundEngine::soundVolume;
		 */
		void setSoundVolume(int newSoundVolume);
	private:
		/// Chunk ID wav files should have.
		static const uint32_t CHUNK_ID_RIFF = 1179011410;

		/// Format the wav files should have.
		static const uint32_t FORMAT_WAVE = 1163280727;

		/**
		 * Default constructor.
		 */
		OpenALEngine();

		/**
		 * Destructor, closes OpenAL.
		 */
		~OpenALEngine();

		/**
		 * Updates OpenAL.
		 */
		void update();

		/**
		 * Loads a sound effect from a file. For now, it must be a wav file.
		 * @param filePath Path to the sound effect's file.
		 * @return Pointer to the loaded sound effect. Null if the loading
		 * failed.
		 */
		SoundInfo *loadSound(const std::string &filePath);

		/**
		 * Loads a sound effect from information.
		 * @param params Information about the sound effect to load.
		 * @return Pointer to the loaded sound effect. Null if the loading
		 * failed.
		 */
		SoundInfo *loadSound(const SoundParameters &params);

		/**
		 * Unloads sound data. Called by the resource loader either by demand
		 * of the user or when it is unloading everything before unloading the
		 * audio engine. Will not succeed if there are still sources using the
		 * buffer.
		 * @param sound Sound data to unload.
		 * @return True if the unloading was done correctly, false if not.
		 */
		bool unloadSound(SoundInfo *sound);

		/**
		 * Deletes all sources using a specific buffer.
		 * @param buffer ID of the buffer.
		 */
		void deleteBufferSources(ALuint buffer);

		/**
		 * Loads data from a wav file.
		 * @param filePath Path to the file to load.
		 * @param bufferData Array containing the buffer data of the loaded wav
		 * file.
		 * @param bufferSize Will contain the size of the loaded buffer.
		 * @param format Loaded audio's format.
		 * @param freq Loaded audio's frequency.
		 */
		static void loadWav(const std::string &filePath,
		                    char*& bufferData,
		                    ALsizei &bufferSize,
		                    ALenum &format,
		                    ALsizei &freq);

		/// Device to load.
		std::string defaultDevice;

		/// List of devices available.
		std::vector<std::string> deviceList;

		/// Sources being played.
		std::list<OpenALSoundFX *> sources;

		/// Non-surviving NullAudios that were returned.
		std::list<NullAudio *> nullsToClean;
	};
}
#endif
