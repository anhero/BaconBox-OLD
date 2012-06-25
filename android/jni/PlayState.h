/**
 * @file
 * @ingroup Group
 */

#ifndef RB_PLAYSTATE_H
#define RB_PLAYSTATE_H

#include <BaconBox.h>
namespace BaconBox{
	/** 
	 *
     * @ingroup Group
     */
	class PlayState : public State{
	public:
		PlayState();
		void update();
	private:
		Sprite * aSprite;
		Sprite * aSprite2;
		Sprite * aSprite3;
		Sprite * aSprite4;

		int i;
		int j;
		int k;
		bool rX;
		bool rY;
	};
}

#endif
