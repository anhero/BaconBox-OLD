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
#include <list>

#include "AudioEngine.h"
#include "OpenaLSoundFX.h"

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
		void setDefaultDevice(const std::string& newDevice);
		/**
		 * Gets the list of available auio devices on the system.
		 * @return Vector containing the device names.
		 */
		const std::vector<std::string>& getDeviceList();
		/**
		 * Deletes all sources using a specific buffer.
		 */
		void deleteBufferSources(ALuint buffer);
		/**
		 * Gets OpenALEngine's instance. Retuns NULL if it isn't constructed.
		 */
		static OpenALEngine* getInstance();
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
		/**
		 * Gets a sound effect. Initializes a sound effect from already loaded
		 * sound effect data.
		 * @param key Key to the sound effect data to use for the sound effect.
		 * @param survive True if the user wants to manage the sound effect by
		 * himself. False if he doesn't want to have to delete the sound
		 * effect after he has started playing it.
		 */
		SoundFX* getSoundFX(const std::string& key, bool survive);
		/**
		 * Gets a background music. Initializes a music from already loaded
		 * music data. The user has to take care of deleting the background
		 * music's instance after he recieves it.
		 * @param key Key to the music data to use for the background music.
		 */
		BackgroundMusic* getBackgroundMusic(const std::string& key);
	private:
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
		 * Loads a background music from a file. For now, it must be a wav file.
		 * @param filePath Path to the music's file.
		 * @return Pointer to loaded music. Null if the loading failed.
		 */
		MusicInfo* loadMusic(const std::string& filePath);
		/**
		 * Loads a background music from information.
		 * @param info Information about the music to load.
		 * @return Pointer to the loaded music. Null if the loading failed.
		 */
		MusicInfo* loadMusic(const MusicParameters& params);
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
		 * Unloads data of a music. Called by the resource loader either by
		 * demand of the user or when it is unloading everything before
		 * unloading the audio engine. Does nothing in OpenAL's case.
		 * @param sound Music data to unload.
		 * @return True if the unloading was done correctly, false if not.
		 */
		bool unloadMusic(MusicInfo* music);
		/**
		 * Destructor, closes OpenAL.
		 */
		~OpenALEngine();
	};
}

#endif