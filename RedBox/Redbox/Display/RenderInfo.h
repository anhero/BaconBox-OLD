#if 0
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
#include <iostream>

#include "Object.h"
#include "AnimationParameters.h"
#include "Color.h"
#include "Vector2.h"

namespace RedBox {
	class VerticesGroup;
	class TextureInformation;
	class GraphicBody;
	/**
	 * Struct contaning rendering information.
	 * @ingroup Display
	 */
	class RenderInfo : public Object {
		/**
		 * Outputs the RenderInfo's content.
		 * @param output The ostream in which RenderInfo is output.
		 * @param r RenderInfo to output in the ostream.
		 * @return Resulting ostream.
		 */
		friend std::ostream &operator<<(std::ostream &output,
		                                const RenderInfo &r);
	public:
		/**
		 * Default constructor.
		 */
		RenderInfo();

		/**
		 * Copy constructor.
		 * @param src RenderInfo to make a copy of.
		 */
		RenderInfo(const RenderInfo &src);

		/**
		 * Parametrized constructor.
		 * @param newTexInfo Pointer to the information about the texture.
		 * @param vertices Vertices to use to generate the texCoords.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * will start loading.
		 * @param newColor Array to use to set the RenderInfo's color.
		 * @see RedBox::RenderInfo::color
		 * @see RedBox::RenderInfo::texInfo
		 */
		RenderInfo(TextureInformation *newTexInfo,
		           VerticesGroup &vertices,
		           unsigned int frameWidth,
		           unsigned int frameHeight,
		           unsigned int nbFrames = 1,
		           const Color &newColor = Color::WHITE);

		/**
		 * Loads the texture coordinates. Used to determine what information
		 * needs to be read in the image to show on screen. The upper left
		 * corner of the image is at coordinates (0, 0), and the lower right
		 * corner is at (1, 1).
		 * @param vertices Vertices making up the shape to use for each frame.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * @param newTexInfo Pointer to the information about the texture.
		 * @see RedBox::RenderInfo::texInfo
		 */
		void loadTexCoords(VerticesGroup &vertices,
		                   unsigned int frameWidth,
		                   unsigned int frameHeight,
		                   unsigned int nbFrames = 1,
		                   TextureInformation *newTexInfo = NULL);
		/**
		 * Adds an animation.
		 * @param name Animation's name used for identification when playing it.
		 * @param frames Vector for the animation's series of frames to play.
		 * @param timePerFrame Time in seconds that each frame lasts during the
		 * animation.
		 * @param nbLoops Number of times the animation will play before
		 * stopping. -1 means it will loop infinitely.
		 * @see RedBox::RenderInfo::animations
		 */
		void addAnimation(const std::string &name,
		                  const std::vector<unsigned int>& frames,
		                  double timePerFrame,
		                  int nbLoops = -1);

		/**
		 * Adds an animation. Accepts a variable number of parameters for each
		 * animation frame. For example, an animation of 7 frames could be added
		 * as such:
		 * addAnimation("myAnimationName", 0.2, -1, 7, 0, 1, 2, 4, 3, 5, 6);
		 * @param name Animation's name used for identification when playing it.
		 * @param timePerFrame Time in seconds that each frame lasts during the
		 * animation.
		 * @param nbLoops Number of times the animation will play before
		 * stopping. -1 means it will loop infinitely.
		 * @param nbFrames Number of frames the animation has.
		 * @see RedBox::RenderInfo::animations
		 */
		void addAnimation(const std::string &name,
		                  double timePerFrame,
		                  int nbLoops,
		                  unsigned int nbFrames, ...);
		/**
		 * Adds an animation. To be used for manual creation of animation
		 * parameters.
		 * @param name Animation's name used for identification when playing it.
		 * @param newAnimation Animation parameters for the new animation.
		 * @see RedBox::RenderInfo::animations
		 */
		void addAnimation(const std::string &name,
		                  const AnimationParameters &newAnimation);

		/**
		 * Sets the sprite used to mask the parent render step.
		 * @param newMask Pointer to the new sprite to use as a mask.
		 * @see RedBox::RenderInfo::mask
		 */
		void setMask(GraphicBody *newMask);

		/**
		 * Gets the sprite used to mask the parent render step.
		 * @return Pointer to the sprite that serves as a mask.
		 * @see RedBox::RenderInfo::mask
		 */
		GraphicBody *getMask();

		/**
		 * Gets the color.
		 * @return RenderInfo's color.
		 * @see RedBox::RenderInfo::color
		 */
		const Color &getColor() const;

		/**
		 * Gets the texture info. Returns the texture information pointed by
		 * the texInfo pointer.
		 * @return Pointer to the RenderInfo's texture's information.
		 */
		TextureInformation *getTexInfo();

		/**
		 * Gets the vector of texture coordinates.
		 * @return Vector of texture coordinates.
		 */
		std::vector<std::vector<Vector2> >& getTexCoords();
		/**
		 * Sets the color by specifying the red, green, blue and alpha values.
		 * @param newColor The RenderInfo's new color.
		 */
		void setColor(const Color &newColor);

		/**
		 * Sets the texture information.
		 * @param newTexInfo Pointer to the new texture information.
		 */
		void setTexInfo(TextureInformation *newTexInfo);

		/**
		 * Checks whether an animation exists or not.
		 * @param name Name of the animation to check.
		 * @return True if the animation exists, false if not.
		 */
		bool animationExists(const std::string &name) const;

		/**
		 * Gets the animation parameters of a specific animation.
		 * @param name Name of the animation to get.
		 * @return Animation parameters asked for.
		 */
		AnimationParameters *getAnimationParameters(const std::string &name);

		/**
		 * Gets the animation parameters of a specific animation.
		 * @param name Name of the animation to get.
		 * @return Animation parameters asked for.
		 */
		const AnimationParameters *getAnimationParameters(const std::string &name) const;

		/**
		 * Changes the frame to be shown.
		 */
		void setCurrentFrame(unsigned int newCurrentFrame);

		/**
		 * Gets the index of the current animation frame.
		 * @return Index of the current animation frame.
		 */
		unsigned int getCurrentFrame() const;

		/**
		 * Checks if the RenderInfo is animated.
		 * @return True if the RenderInfo contains animations and thus is
		 * animated.
		 */
		bool isAnimated() const;

		/**
		 * Increments the frame index. If it goes over the number of available
		 * frames, it resets to 0.
		 */
		void incrementFrame();

		/**
		 * Gets the name of the RenderInfo's current animation.
		 * @return Current animation's name.
		 */
		const std::string &getCurrentAnimation() const;

		/**
		 * Sets the current animation.
		 * @param name current animation's name.
		 */
		void setCurrentAnimation(const std::string &name);

		/**
		 * Resets the counter of number of loops done for the animation.
		 */
		void resetCurrentNbLoops();

		/**
		 * Gets the default frame index.
		 * @return Index of the default frame to show when the RenderInfo isn't
		 * animated.
		 */
		unsigned int getDefaultFrame() const;

		/**
		 * Sets the default frame index.
		 * @param newDefaultFrame Index of the new default frame to show when
		 * the RenderInfo isn't animated.
		 */
		void setDefaultFrame(unsigned int newDefaultFrame);

		/**
		 * Point the c arrays pointers (texture coordinates and colors)
		 * to the batchcall's arrays.
		 * Set them to NULL if you don't want to sync a batchcall.
		 */
		void setBatchPointer(Vector2 *texCoord, unsigned char *colors);


		/**
		 * Update batchcall array of texture coordinate with the internal
		 * Vector of frame depending on the current frame.
		 * (This function won't re-update the batchcall array
		 * until the current frame change.)
		 */
		void updateBatchPointer();

	private:
		/**
		 * Color, first int is red, second is green, third is blue and last one
		 * is alpha.
		 */
		Color color;

		/**
		 * Pointer to a mask sprite. Pointer is NULL if the parent render step
		 * is not masked.
		 */
		GraphicBody *mask;

		/// Pointer to the texture information.
		TextureInformation *texInfo;

		/**
		 * Vector containing the texture's coordinates for each animation frame.
		 */
		std::vector<std::vector<Vector2> > texCoords;

		/**
		 * Point to the texture coordinates of the current sprite in a renderbatch.
		 * Null if not in batch
		 */
		Vector2 *batchTexCoord;

		unsigned char *batchColors;

		/**
		 * Contain the current frame of the last batchcall update.
		 * Used to prevent redundant updating on the same frame.
		 */
		int lastBatchCallUpdateFrame;

		/**
		 * Current frame at which the animation is currently.
		 */
		unsigned int currentFrame;

		/// Current number of times the animation has looped.
		int currentNbLoops;

		/// Index of the frame to show when the RenderInfo isn't animated.
		unsigned int defaultFrame;

		///Used to prevent redundant updating on the color (when in batchcall)
		bool colorNeedUpdate;

		/**
		 * Map to associate names to each animations in texCoords. For example,
		 * to get information about a specific animation, you'd do
		 * animations["animationName"].
		 */
		std::map<std::string, AnimationParameters> animations;

		/// Name of the animation currently playing.
		std::string currentAnimation;
	};
}

#endif
#endif
