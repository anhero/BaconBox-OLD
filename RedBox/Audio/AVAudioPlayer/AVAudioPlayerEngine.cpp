#include "AVAudioPlayerEngine.h"

#include "AVAudioPlayerMusic.h"
#include "MusicInfo.h"
#include "ResourceManager.h"
#include "AudioState.h"

#include "Debug.h"

using namespace RedBox;

BackgroundMusic* AVAudioPlayerEngine::getBackgroundMusic(std::string const &key,
														 bool survive) {
	MusicInfo* bgmInfo = ResourceManager::getMusic(key);
	if(bgmInfo) {
		AVAudioPlayerMusic* bgm = new AVAudioPlayerMusic();
		bgm->load(bgmInfo->filePath);
		if (!survive) {
			managedMusics.push_back(bgm);
		}
		return bgm;
	} else {
		return NULL;
	}
}

AVAudioPlayerEngine::AVAudioPlayerEngine(): MusicEngine() {
}

AVAudioPlayerEngine::~AVAudioPlayerEngine() {
}

void AVAudioPlayerEngine::init() {
}

void AVAudioPlayerEngine::update() {
	for (std::list<AVAudioPlayerMusic*>::iterator i = managedMusics.begin();
		 i != managedMusics.end(); i++) {
		// If the music is at stopped, we delete it.
		if((*i)->getCurrentState() == AudioState::STOPPED) {
			delete *i;
			managedMusics.erase(i);
		}
	}
}

MusicInfo* AVAudioPlayerEngine::loadMusic(const std::string& filePath) {
	MusicInfo* result = new MusicInfo();
	result->filePath = filePath;
	return result;
}

MusicInfo* AVAudioPlayerEngine::loadMusic(const MusicParameters& params) {
	MusicInfo* result = new MusicInfo();
	result->filePath = params.filePath;
	return result;
}

bool unloadMusic(MusicInfo* music) {
	return true;
}