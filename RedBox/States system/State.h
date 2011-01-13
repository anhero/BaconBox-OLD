#ifndef __STATE_H
#define __STATE_H

#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
#import "Finch.h"
#import <UIKit/UIKit.h>
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#endif //Target iPhone
#endif //__APPLE__

#include <map>
#include <list>
#include <string>

#include "ResourceHelper.h"
#include "RedboxEngine.h"
#include "GraphicString.h"
#include "GraphicObject.h"
#include "SpriteEmitter.h"
#include "Camera.h"
#include "BackgroundMusic.h"
#include "SoundFX.h"
#include "BoundingBox.h"
#include "HudElement.h"
#include "Random.h"
#include "Font.h"
//class SpriteEmitter;

namespace RedBox {

	
	class State {
	private:
		static const double QUAKE_DT = 0.05;
		std::map<std::string, SoundFX*> soundEffects;
		void updateQuake();
		BackgroundMusic* bgMusic;
	protected:
		std::list<GraphicObject*> graphicObjects;
		std::list<HudElement*> hudGraphicObjects;
		std::list<SpriteEmitter*> spriteEmitters;
		std::list<GraphicString*> uiStringObjects;
		std::string name;
		bool initialized;

		std::map<int, std::list<Renderable*> > renderables;
		
		Camera* theCamera;
		double quakeness;
		double quakedecay;

		void removeRenderable(Renderable* toRemove);
	public:
		State();
		virtual ~State();
		HudElement* addHudGraphicObject(HudElement *aGraphicObject, bool useDefaultZ = true);
		GraphicObject* addGraphicObject(GraphicObject *aGraphicObject, bool useDefaultZ = true);
		GraphicString* addGraphicString(GraphicString *aGraphicString, bool useDefaultZ = true);
		void addSpriteEmitter(SpriteEmitter* aSpriteEmitter, bool useDefaultZ = true);
		virtual void update();
		virtual void render();
		virtual void initializeState();
		
		virtual bool touchesBegan(NSSet * touches);
		virtual bool touchesEnded(NSSet * touches);
		
		bool isInitialized();
		std::string getName();
		
		static State * getCurrentState();
		void registerSoundEffect(const std::string& name, const std::string& path);
		void playSoundEffect(const std::string& name);
		bool isSoundRegistered(const std::string& name) const;
		
		static const int HUD_Z = 10000;
		static const int DEFAULT_Z = 0;
		static const int DEFAULT_SPRITEEMITTER_Z = 5000;
	
		void setIphoneOrientation(IPhoneOrientationEnum orientation);
		IPhoneOrientationEnum getIphoneOrientation();
		
		int getScreenWidth();
		int getScreenHeight();
		void startQuake(double quakeness, double quakedecay);
		void stopQuake();
		void setBgMusic(const std::string& bgMusicPath);
		void stopMusic();
		void startMusic();
		void pauseMusic();
		void resumeMusic();
		virtual void resumingState() = 0;
	};
}
#endif
