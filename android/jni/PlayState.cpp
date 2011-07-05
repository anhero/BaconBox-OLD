#include "PlayState.h"
#include <RedBox/SpriteFactory.h>
#include <cmath>

using namespace RedBox;

PlayState::PlayState() : State() {
		aSprite = SpriteFactory::makePolygon(4, 50, Color::RED);
		aSprite->setPosition(0,0);
		//aSprite2 = SpriteFactory::makePolygon(5, 80, Color::GREEN);
		//aSprite3 = SpriteFactory::makePolygon(3, 100, Color::YELLOW);
		//aSprite4 = SpriteFactory::makePolygon(6, 20, Color::GREEN);
		addGraphicBody(aSprite);
		//addGraphicBody(aSprite2);
		//addGraphicBody(aSprite3);
		//addGraphicBody(aSprite4);
	rX = false;
	rY = false;
	i =0;
	j = 0;
	k =0;
}



void PlayState::update() {
//		aSprite->setMainColor(Color(255-i*0.2,j,k*0.5));
//		aSprite2->setMainColor(Color(i,255-j*0.7,k));
//		aSprite3->setMainColor(Color(255-i*0.3,j,k*0.6));
//		aSprite4->setMainColor(Color(i*0.3,j,k*0.6));
//
//
//	
//	if(i>250) {
//		i =0;
//	}
//	if(j>250) {
//		j =0;
//	}
//	if(k>250) {
//		k =0;
//	}
	i++;
	aSprite->setPosition(i*0.5f,4*i);
//	aSprite->setPosition(315,475);
//	aSprite->setPosition(0,0);

//	
//	float bob = sinf(i);
//	aSprite->setPosition(100,bob*100+100);
	
	
//	j++;
//	k++;

//		if (i >= 0xFFFFFFEE) {
//			i = 0;
//		}
//
//	
//		if (rX) {
//			j++;
//			if (j > 300) {
//				rX = true;
//			}
//		}
//		else{
//			j--;
//			if (j < 10) {
//				rX = false;
//			}
//		}
//		
//		if (rY) {
//			k++;
//			if (k > 300) {
//				(rY) = true;
//			}
//		}
//		else{
//			k--;
//			if (k < 10) {
//				(rY) = false;
//			}
//		}
//		aSprite->setPosition(j,k);
//		aSprite2->setPosition(j*0.3,k*0.5);
//		aSprite3->setPosition(300-j,300-k);
//		aSprite3->setPosition(300-j,300-k);
//		aSprite4->setPosition(j*0.5,k*0.5);
	

	
	//aSprite->setPosition(100,100);
	
}
