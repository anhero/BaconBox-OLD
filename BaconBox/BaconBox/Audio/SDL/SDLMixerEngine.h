/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SDL_MIXER_ENGINE_H
#define RB_SDL_MIXER_ENGINE_H

#include "BaconBox/PlatformFlagger.h"

#include <stdint.h>

#include <list>

#include <SDL2/SDL_mixer.h>

#include <sigly.h>

#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"

namespace BaconBox {
	class SDLMixerBackgroundMusic;
	class SDLMixerSoundFX;
	class Sound;
	/**
	 * Audio engine implementation to play sounds and music with SDL_mixer.
	 * @ingroup Audio
	 */
	class SDLMixerEngine : public SoundEngine, public MusicEngine {
		friend class Engine;
	public:
		/**
		 * Gets the singleton instance.
		 * @return Pointer to the audio engine's instance.
		 */
		static SDLMixerEngine *getInstance();

		/**
		 * Converts the SDL volume to its BaconBox equivalent.
		 * @param sdlVolume SDL volume to convert.
		 * @return BaconBox volume equivalent to the given SDL volume.
		 */
		static int sdlToBaconBoxVolume(int sdlVolume);

		/**
		 * Converts the BaconBox volume to its SDL equivalent.
		 * @param baconBoxVolume BaconBox volume to convert.
		 * @return SDL volume equivalent to the given BaconBox volume.
		 */
		static int baconBoxToSdlVolume(int baconBoxVolume);

		/// Signal when pause/resume fading needs updating for a music.
		sigly::Signal1<unsigned int> fadeUpdate;

		/// Signal when the global sound volume is changed.
		sigly::Signal0<> soundVolumeChange;

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
		SoundFX *getSoundFX(const std::string &key, bool survive = true);

		/**
		 * Constructs a background music. Gets the music's data associated with
		 * the key.
		 * @param key Identifier for the music data to use. The music data needs
		 * to be loaded beforehand.
		 * @param survive Used to specify if the music destroy is managed by the
		 * user or by the engine when the music is done playing. This lets the
		 * user simply call this function and play the music directly if survive
		 * is at false or keep it and re-use it if surive is at true.
		 * @return Background music generated by this function, the user will
		 * either have to destroy it manually if survive is set at true, or will
		 * be automatically destroyed once the music's state is at STOPPED. The
		 * background music returned is at the INITIAL state.
		 */
		BackgroundMusic *getBackgroundMusic(const std::string &key,
		                                    bool survive = true);
		/**
		 * Called by background musics when the fading from a pause or a
		 * resume is done. It raises a flag that will be checked in the
		 * update method and it will disconnect all listener from the
		 * fadeUpdate signal.
		 */
		void askForDisconnect();
		/**
		 * Sets the engine's global music volume.
		 * @param newMusicVolume Engine's new global music volume level.
		 * @see BaconBox::AudioEngine::musicVolume
		 */
		void setMusicVolume(int newMusicVolume);

		/**
		 * Sets the global sound effects volume.
		 * @param newSoundVolume New global sound effects volume.
		 * @see BaconBox::SoundEngine::soundVolume;
		 */
		void setSoundVolume(int newSoundVolume);
	private:
		/// Playback frequency
		static const int AUDIO_RATE = 44100;

		/// Playback audio format.
		static const uint16_t AUDIO_FORMAT = AUDIO_S16SYS;

		/// Number of audio channels. By default, it's in Stereo.
		static const int AUDIO_CHANNELS = 2;

		/// Size of the audio buffer for music playing.
		static const int AUDIO_BUFFERS = 4096;

		/// Number of possible simultaneous sound effects.
		static const int NB_SOUND_CHANNELS = 32;

		/**
		 * Number of ticks (ms) between each fade update when a music is
		 * fading to pause or resume.
		 */
		static const unsigned int NB_TICKS_PER_FADE = 100;

		/// Pointer to the singleton instance.
		static SDLMixerEngine *instance;

		/// Last tick at which the fade update was called.
		unsigned int lastFadeTick;

		/// Flag used to ask to be disconnected from the fadeUpdate signal.
		bool disconnect;

		/**
		 * List of pointers to sounds that the engine takes care of managing.
		 */
		std::list<Sound *> sounds;

		/**
		 * Default constructor.
		 */
		SDLMixerEngine();

		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * manager.
		 */
		~SDLMixerEngine();

		/**
		 * Updates the necessary informations for the audio engine.
		 */
		void update();

		/**
		 * Loads sound data from a file.
		 * @param filePath Path to the sound file to load.
		 * @return Pointer to the sound data loaded.
		 */
		SoundInfo *loadSound(const std::string &filePath);

		/**
		 * Loads sound data from engine specific parameters.
		 * @param params Parameters to use to load the sound data. Each engine
		 * has implementation different parameters.
		 * @return Pointer to the sound data loaded.
		 */
		SoundInfo *loadSound(const SoundParameters &params);

		/**
		 * Unloads sound data.
		 * @param sound Sound data that needs to be unloaded. Delete must not be
		 * called on it, the resource manager that calls this function takes
		 * care of that.
		 * @return True if the unloading was successful, false if not.
		 */
		bool unloadSound(SoundInfo *sound);

		/**
		 * Loads music data from a file.
		 * @param filePath Path to the music file to load.
		 * @return Pointer to the music data loaded.
		 */
		MusicInfo *loadMusic(const std::string &filePath);

		/**
		 * Loads music data from engine specific parameters.
		 * @param params Parameters to use to load the music data. Each engine
		 * has implementation different parameters.
		 * @return Pointer to the music data loaded.
		 */
		MusicInfo *loadMusic(const MusicParameters &params);

		/**
		 * Unloads music data.
		 * @param music Music data that needs to be unloaded. Delete must not be
		 * called on it, the resource manager that calls this function takes
		 * care of that.
		 * @return True if the unloading was successful, false if not.
		 */
		bool unloadMusic(MusicInfo *music);
	};
}

#endif
