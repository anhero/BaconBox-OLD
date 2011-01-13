#ifndef __SPRITE_EMITTER_H
#define __SPRITE_EMITTER_H

#include "Vector2D.h"
#include "GraphicObject.h"
#include <vector>
#include <cstdlib>
#include <string>
#include "json.h"
#include "Random.h"

namespace RedBox {
/** \brief A sprite emitter for explosions and the likes.
 *
 * This class is used to represent a sprite emitter used for explosions and 
 * the likes.
 */
class SpriteEmitter : public GraphicObject {
private:
	struct EmitObject {
		EmitObject(): mySprite(NULL), lifespan(0), birthdate(0), isActive(false), deltaX(0.0f), deltaY(0.0f), nbBlasts(0)/*, renderedOnce(false)*/ {}
		~EmitObject() { clean(); }
		EmitObject(const EmitObject& src): mySprite(NULL) {
			copyFrom(src);
		}
		EmitObject& operator=(const EmitObject& src) {
			copyFrom(src);
			return *this;
		}
		GraphicObject* mySprite;
		double lifespan;
		double birthdate;
		bool isActive;
		int nbBlasts;
		double deltaX;
		double deltaY;
		//bool renderedOnce;
	private:
		void clean() { 
			if(mySprite) {
				delete mySprite;
				mySprite = NULL;
			}
		}
		void copyFrom(const EmitObject& src) {
			if (this != &src) {
				clean();
				if (&src) {
					lifespan = src.lifespan;
					birthdate = src.birthdate;
					isActive = src.isActive;
					nbBlasts = src.nbBlasts;
					deltaX = src.deltaX;
					deltaY = src.deltaY;
					if(src.mySprite) mySprite = new GraphicObject(*src.mySprite);
					//renderedOnce = src.renderedOnce;
				} else {
					lifespan = 0;
					birthdate = 0;
					isActive = false;
					nbBlasts = 0;
					deltaX = 0.0f;
					deltaY = 0.0f;
				}

			}
		}
	};
	double force; // Vector's length.
	double forceRange; // The sprites' force variation.
	double coneAngle; // The range of angles the vectors can have.
	double directionAngle; // The direction the vectors will point at.
	double x; // The emitter's x position.
	double y; // The emitter's y position.
	double xFriction;
	double yFriction;
	std::vector<EmitObject> emitObjects; // References to the sprites to be emitted.
	double spriteLifespan; // The sprites' base lifespan.
	double spriteLifespanVariation; // The sprites' lifespan variation.
	double deltaXCorrection;
	double deltaYCorrection;
	bool isDead;
	/** \brief Generate a random lifespan.
	 * 
	 * This function generates a sprite's random lifespan using the base
	 * lifespan and the lifespan variation.
	 * @return A lifespan generated randomly.
	 */
	double generateLifespan() { return (spriteLifespan + generateVariation()); }
	double generateVariation() { return Random::getRandomDouble(0.0, spriteLifespanVariation); }
	bool updateEmitObject(std::vector<EmitObject>::iterator currentEmitObject);
	void clean();
	void copyFrom(const SpriteEmitter& src);
public:
	/** \brief The default constructor.
	 *
	 * The default constructor initializes an empty sprite emitter.
	 */
	SpriteEmitter();
	/** \brief The parameterized consctructor.
	 *
	 * The parameterized constructor initializes the sprite emitter using
	 * the values given.
	 * @param newX The sprite emitter's x position.
	 * @param newY The sprite emitter's y position.
	 * @param newForce The sprite emitter's force.
	 * @param newForceRange The sprites' force variation.
	 * @param newDirectionAngle The direction the sprite emitter will emit at.
	 * @param newConeAngle The cone's size of sprite emitting.
	 * @param nbSprites The number of sprites to be emitted.
	 * @param newSpriteLifespan The sprites' average lifespan.
	 * @param newSpriteLifespanVariation The sprites' lifespan variation.
	 */
	SpriteEmitter(double newX, double newY, double newForce,
				  double newForceRange, double newDirectionAngle, 
				  double newConeAngle, unsigned int nbSprites,
				  double newSpriteLifespan, double newSpriteLifespanVariation,
				  int newNbBlasts = -1, bool now = false);
	SpriteEmitter(const SpriteEmitter& src);
	SpriteEmitter& operator=(const SpriteEmitter& src);
					  
	/** \brief The destructor.
	 *
	 * The destructor frees the memory used by the sprite emitter.
	 */
	virtual ~SpriteEmitter();

	/** \brief Update the sprites.
	 * 
	 * This method takes care of updating the sprites emitted.
	 */
	void update();
	
	void render();

	/** \brief Get the force.
	 *
	 * This function returns the sprite emitter's force.
	 * @return The sprite emitter's force.
	 */
	double getForce() const;
	/** \brief Get the direction angle.
	 *
	 * This function returns the sprite emitter's direction angle.
	 * @return The sprite emitter's direction angle.
	 */
	double getDirectionAngle() const;
	/** \brief Get the cone angle.
	 *
	 * This function returns the sprite emitter's cone angle.
	 * @return The sprite emitter's cone angle.
	 */
	double getConeAngle() const;
	/** \brief Get the x position.
	 *
	 * This function returns the sprite emitter's x position.
	 * @return The sprite emitter's x position.
	 */
	double getX() const;
	/** \brief Get the y position.
	 *
	 * This function returns the sprite emitter's y position.
	 * @return The sprite emitter's y position.
	 */
	double getY() const;
	
	/** \brief Get the number of sprites.
	 *
	 * This functions returns the number of sprites emitted.
	 * @return The number of sprites emitted.
	 */
	unsigned int getNbEmitObjects() const;
	
	/** \brief Get the sprites.
	 *
	 * This function returns a pointer to the array of sprites emitted.
	 * @return The sprites emitted.
	 */
	//GraphicObject* getSprites();
	
	/** \brief Set the force.
	 *
	 * This method sets the sprite emitter's force.
	 * @param newForce The sprite emitter's force.
	 */
	void setForce(float newForce);
	/** \brief Set the direction angle.
	 *
	 * This method sets the sprite emitter's direction angle.
	 * @param newDirectionAngle The sprite emitter's new direction angle.
	 */
	void setDirectionAngle(float newDirectionAngle);
	/** \brief Set the cone angle.
	 *
	 * This method sets the sprite emitter's cone angle.
	 * @param newConeAngle The sprite emitter's new cone angle.
	 */
	void setConeAngle(float newConeAngle);
	void constructDrawer(double x, double y, double width, double height, double angle, const std::string& imageName, int frameWidth, int frameHeight);
	void addAnimation(const std::string& nameOfAnimation, int frames[],  int numberOfFrames, int FPS);
	void playAnimation(char name[]);
	void playFirstAnimation();
	bool isDone() {return isDead;}
	void setAngle(double angle);
	void setWidth(double width);
	void setHeight(double height);
	void setPosition(double x, double y);
	void setXPosition(double x);
	void setYPosition(double y);
	void setFrameWidth(int frameWidth);
	void setFrameHeight(int frameHeight);
	void setFilename(const char* filename);
	void setXFriction(double newXFriction);
	void setYFriction(double newYFriction);
	void setDeltaXCorrection(double newXCorr);
	void setDeltaYCorrection(double newYCorr);
	
	double getWidth() const ;
	double getHeight() const ;
	double getXPosition() const ;
	double getYPosition() const ;
	double getAngle();
	double getXFriction() const;
	double getYFriction() const;
	int getFrameWidth();
	int getFrameHeight();
	std::string getFilename();
	void die();
	void initDrawer();
};
}

#endif