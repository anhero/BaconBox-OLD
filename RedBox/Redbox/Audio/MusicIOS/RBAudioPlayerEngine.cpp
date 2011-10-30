#include "PlatformFlagger.h"

#include "RBAudioPlayerEngine.h"

#include "RBAudioPlayerMusic.h"
#include "MusicInfo.h"
#include "ResourceManager.h"
#include "AudioState.h"
#include "NullAudio.h"

#include "Console.h"

namespace RedBox {
	BackgroundMusic* RBAudioPlayerEngine::getBackgroundMusic(std::string const &key,
															 bool survive) {
		MusicInfo* bgmInfo = ResourceManager::getMusic(key);
		if(bgmInfo) {
			RBAudioPlayerMusic* bgm = new RBAudioPlayerMusic();
			bgm->load(bgmInfo->filePath);
			if (!survive) {
				managedMusics.push_back(bgm);
			}
			return bgm;
		} else {
			NullAudio* nullAudio = new NullAudio();
			if(!survive) {
				managedMusics.push_back(nullAudio);
			}
			return nullAudio;
		}
	}
	
	void RBAudioPlayerEngine::setMusicVolume(int newMusicVolume) {
		this->MusicEngine::setMusicVolume(newMusicVolume);
	}
	
	RBAudioPlayerEngine::RBAudioPlayerEngine(): MusicEngine() {
	}
	
	RBAudioPlayerEngine::~RBAudioPlayerEngine() {
	}
	
	void RBAudioPlayerEngine::update() {
		for (std::list<BackgroundMusic*>::iterator i = managedMusics.begin();
			 i != managedMusics.end(); i++) {
			// If the music is at stopped, we delete it.
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				delete *i;
				managedMusics.erase(i);
			}
		}
	}
	
	MusicInfo* RBAudioPlayerEngine::loadMusic(const std::string& filePath) {
		MusicInfo* result = new MusicInfo();
		result->filePath = filePath;
		return result;
	}
	
	MusicInfo* RBAudioPlayerEngine::loadMusic(const MusicParameters& params) {
		MusicInfo* result = new MusicInfo();
		result->filePath = params.filePath;
		return result;
	}
	
	bool RBAudioPlayerEngine::unloadMusic(MusicInfo* music) {
		return true;
	}
}