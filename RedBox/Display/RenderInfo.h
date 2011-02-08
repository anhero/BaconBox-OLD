/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_INFO_H
#define RB_RENDER_INFO_H

#include <vector>
#include <map>
#include <string>
#include <cstdarg>

#include "TextureInfo.h"
#include "AnimationParameters.h"

namespace RedBox {
    /**
     * Struct contaning rendering information.
     * @ingroup Display
     */
    class RenderInfo {
	public:
        /**
         * Default constructor.
         */
        RenderInfo();
        /**
         * Parametrized constructor.
         * @param newTexInfo Pointer to the information about the texture.
         * @param newColor Array to use to set the RenderInfo's color.
         */
        RenderInfo(TextureInfo* newTexInfo, int* newColor);
		/**
		 * Adds an animation.
		 * @param name Animation's name used for identification when playing it.
		 * @param frames Vector for the animation's series of frames to play.
		 * @param timePerFrame Time in seconds that each frame lasts during the
		 * animation.
		 * @param nbLoops Number of times the animation will play before 
		 * stopping. -1 means it will loop infinitely.
		 */
		void addAnimation(const std::string& name,
						  const std::vector<unsigned int> frames,
						  double timePerFrame,
						  int nbLoops = -1);
		/**
		 * Adds an animation. Accepts a variable number of parameters for each
		 * animation frame. For example, an animation of 7 frames could be added
		 * as such :
		 * addAnimation("myAnimationName", 0.2, -1, 7, 0, 1, 2, 4, 3, 5, 6);
		 * @param name Animation's name used for identification when playing it.
		 * @param timePerFrame Time in seconds that each frame lasts during the
		 * animation.
		 * @param nbLoops Number of times the animation will play before
		 * stopping. -1 means it will loop infinitely.
		 * @param nbFrames Number of frames the animation has.
		 * @param firstFrame Animation's first frame's index. Each of the
		 * other parameters are the following frame indexes.
		 */
		void addAnimation(const std::string& name,
						  double timePerFrame,
						  int nbLoops,
						  unsigned int nbFrames,
						  unsigned int firstFrame, ... );
		/**
		 * Adds an animation. To be used for manual creation of animation
		 * parameters.
		 * @param name Animation's name used for identification when playing it.
		 * @param newAnimation Animation parameters for the new animation.
		 */
		void addAnimation(const std::string& name,
						  const AnimationParameters& newAnimation);
		/**
		 * Gets the color's array.
		 * @return Array containing the RGBA values for the color. Each value
		 * is inclusively between 1 and 255.
		 */
		int* getColor();
		/**
		 * Gets the color's red value.
		 * @return Color's red value. Value inclusively between 1 and 255.
		 */
		int getRedValue() const;
		/**
		 * Gets the color's green value.
		 * @return Color's green value. Value inclusively between 1 and 255.
		 */
		int getGreenValue() const;
		/**
		 * Gets the color's blue value.
		 * @return Color's blue value. Value inclusively between 1 and 255.
		 */
		int getBlueValue() const;
		/**
		 * Gets the color's alpha value.
		 * @return Color's alpha value. Value inclusively between 1 and 255.
		 */
		int getAlphaValue() const;
		/**
		 * Gets the texture info. Returns the texture information pointed by
		 * the texInfo pointer.
		 * @return RenderStep's texture's information.
		 */
		TextureInfo& getTexInfo();
		/**
		 * Gets the vector of texture coordinates.
		 * @return Vector of texture coordinates.
		 */
		std::vector<std::vector<float> >& getTexCoords();
		/**
		 * Sets the color by specifying the red, green, blue and alpha values.
		 * @param red Color's red value. Value inclusively between 1 and 255.
		 * @param green Color's green value. Value inclusively between 1 and 255.
		 * @param blue Color's blue value. Value inclusively between 1 and 255.
		 * @param alpha Color's alpha value. Value inclusively between 1 and 255.
		 */
		void setRGBA(int red, int green, int blue, int alpha);
		/**
		 * Sets the color's red value.
		 * @param red Color's red value. Value inclusively between 1 and 255.
		 */
		void setRedValue(int red);
		/**
		 * Sets the color's green value.
		 * @param green Color's green value. Value inclusively between 1 and 255.
		 */
		void setGreenValue(int green);
		/**
		 * Sets the color's blue value.
		 * @param blue Color's blue value. Value inclusively between 1 and 255.
		 */
		void setBlueValue(int blue);
		/**
		 * Sets the color's alpha value.
		 * @param alpha Color's alpha value. Value inclusively between 1 and 255.
		 */
		void setAlphaValue(int alpha);
		/**
		 * Sets the texture information.
		 * @param newTexInfo Pointer to the new texture information.
		 */
		void setTexInfo(TextureInfo* newTexInfo);
	private:
        /**
         * Color, first int is red, second is green, third is blue and last one
         * is alpha.
         */
        int color[4];
        /// Pointer to the texture information.
        TextureInfo* texInfo;
		/**
		 * Vector containing the texture's coordinates for each animation frame.
		 * For example, to get a vector of texture coordinates for the 3rd
		 * frame, you'd do texCoords[2].
		 */
		std::vector< std::vector<float> > texCoords;
		/**
		 * Map to associate names to each animations in texCoords. For example,
		 * to get information about a specific animation, you'd do 
		 * animations["animationName"].
		 */
		std::map<std::string, AnimationParameters> animations;
    };
}

#endif