/**
 * @file
 * @ingroup Display
 */
#ifndef RB_ANIMATABLE_H
#define RB_ANIMATABLE_H

#include <cstdarg>

#include <vector>

#include "Updateable.h"
#include "TextureMappable.h"
#include "TextureCoordinates.h"
#include "AnimationDefinition.h"
#include "TexturePointer.h"

namespace RedBox {
	/**
	 * All bodies that can be animated are derived from this class.
	 * @ingroup Display
	 */
	class Animatable : virtual public Updateable, public TextureMappable {
	public:
		/**
		 * Simple parameterized constructor.
		 * @param newTexture Texture pointer to use as the texture.
		 */
		explicit Animatable(TexturePointer newTexture = TexturePointer());

		/**
		 * Parameterized constructor. Does not check if the number of frames
		 * to load makes sense.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset in the texture to use when loading the texture
		 * coordinates.
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Animatable::frames
		 */
		Animatable(TexturePointer newTexture,
		           const VertexArray &vertices,
		           const Vector2 &offset,
		           unsigned int nbFrames = 1);

		/**
		 * Copy constructor.
		 * @param src Animatable to make a copy of.
		 */
		Animatable(const Animatable &src);

		/**
		 * Destructor.
		 */
		virtual ~Animatable();

		/**
		 * Assignment operator.
		 * @param src Animatable to make a copy of.
		 * @return Reference to the modified Animatable.
		 */
		Animatable &operator=(const Animatable &src);

		/**
		 * Updates the body.
		 */
		virtual void update();

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see RedBox::Animatable::frames
		 */
		virtual const TextureCoordinates &getCurrentTextureCoordinates() const;

		/**
		 * Gets the vector containing the texture coordinates for each of the
		 * animatable body's frames.
		 * @return Vector containing the texture coordinates for each of the
		 * frames.
		 * @see RedBox::Animatable::frames
		 */
		const std::vector<TextureCoordinates> &getFrames() const;

		/**
		 * Gets the index of the current frame.
		 * @return Index of the current frame in the current animation's array
		 * list of frames. Zero if there is no animation playing.
		 * @see RedBox::Animatable::currentFrame
		 */
		unsigned int getCurrentFrame() const;

		/**
		 * Sets the current frame. Does nothing if the received index is too
		 * high for the current animation or if there is no animation playing.
		 * @param newCurrentFrame New current frame.
		 * @see RedBox::Animatable::currentFrame
		 */
		void setCurrentFrame(unsigned int newCurrentFrame);

		/**
		 * Increments the current frame. Does nothing if there is no animation
		 * playing.
		 * @param increment How much to increment. Loops if the number is
		 * higher than the number of frames the animation is playing. Makes the
		 * current number of loops increment too if needed.
		 * @see RedBox::Animatable::currentFrame
		 * @see RedBox::Animatable::currentNbLoops
		 */
		void incrementCurrentFrame(unsigned int increment = 1);

		/**
		 * Gets the number of times the animation has looped.
		 * @return Number of times the animation has looped. -1 if the
		 * animation is looping infinitely.
		 * @see RedBox::Animatable::currentNbLoops
		 */
		int getCurrentNbLoops() const;

		/**
		 * Checks if the animation is paused.
		 * @return True if there is no animation playing, false if an animation
		 * is playing.
		 * @see RedBox::Animatable::animationPaused
		 */
		bool isAnimationPaused() const;

		/**
		 * Sets whether the animation is to be paused or not. Does nothing if
		 * no animation is playing.
		 * @param newAnimationPaused Pauses the animation if true and if there
		 * is an animation playing.
		 * @see RedBox::Animatable::animationPaused
		 */
		void setAnimationPaused(bool newAnimationPaused);

		/**
		 * Pauses the animation. Does nothing if it is already paused or if
		 * there is no animation playing.
		 * @see RedBox::Animatable::animationPaused
		 */
		void pauseAnimation();

		/**
		 * Resumes the paused animation. Does nothing if no animation was
		 * explicitly paused.
		 * @see RedBox::Animatable::animationPaused
		 */
		void resumeAnimation();

		/**
		 * Gets the frame shown when no animation is playing.
		 * @return Index of the frame shown when no animation is playing.
		 * @see RedBox::Animatable::defaultFrame
		 */
		unsigned int getDefaultFrame() const;

		/**
		 * Sets the default frame to show when no animation is playing.
		 * @param newDefaultFrame Index of the new default frame to show when
		 * no animation is playing. Does nothing if the index received is
		 * higher than the number of frames loaded.
		 */
		void setDefaultFrame(unsigned int newDefaultFrame);

		/**
		 * Gets the definition of an animation.
		 * @param name Name of the animation definition to look for.
		 * @return Pointer to the animation definition or NULL if no animation
		 * definition was found.
		 * @see RedBox::Animatable::animations
		 */
		AnimationDefinition *getAnimation(const std::string &name);

		/**
		 * Adds an animation definition. Does nothing if the animation
		 * definition's frame indexes are too high, if there are no frame
		 * indexes or if the name is empty.
		 * @param newName Name of the animation to add.
		 * @param newAnimationDefinition Definition of the animation to add.
		 * @param overwrite Flag to use to overwrite the existing animation if
		 * an animation definition with the same name already exists. False by
		 * default.
		 */
		void addAnimation(const std::string &newName,
		                  const AnimationDefinition &newAnimationDefinition,
		                  bool overwrite = false);

		/**
		 * Adds an animation definition. Does nothing if the animation
		 * definition's frame indexes are too high, if there are no frame
		 * indexes or if the name is empty. Does nothing if there is already an
		 * animation with the received name.
		 * @param newName Name of the animation to add.
		 * @param newTimePerFrame Time in seconds each frame lasts during the
		 * animation.
		 * @param newNbLoops Number of times the animation will play before
		 * stopping. -1 (or any negative number) means it will loop infinitely.
		 * @param nbFrames Number of frames the animation has.
		 */
		void addAnimation(const std::string &newName,
		                  double newTimePerFrame,
		                  int newNbLoops,
		                  unsigned int nbFrames, ...);

		/**
		 * Removes an animation. If the animation currently playing is the one
		 * removed, the animation is stopped and the body will show the
		 * default frame.
		 * @param name Name of the animation to remove.
		 */
		void removeAnimation(const std::string &name);

		/**
		 * Gets the name of the animation currently playing.
		 * @return Name of the animation currently playing. Empty string if no
		 * animation is playing.
		 */
		const std::string &getCurrentAnimation() const;

		/**
		 * Starts an animation. Restarts the animation if the animation is
		 * already playing and unpauses if it was paused. If the name received
		 * is empty, the animation is stopped (if one was playing) and the
		 * default frame will be shown. Does nothing if the animation does not
		 * exist.
		 * @param name Name of the animation to start.
		 */
		void startAnimation(const std::string &name);

		/**
		 * Stops the animation, whether it was playing or paused. The body will
		 * then be showing the default frame.
		 */
		void stopAnimation();

		/**
		 * Loads the texture coordinates. Does not check if the number of frames
		 * to load makes sense.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture.
		 * @param nbFrames Number of frames to load. If set to 0, it will use the maximum frame number 
         * for the texture and size of the Animatable object.
		 * @see RedBox::Animatable::frames
		 */
		void loadTextureCoordinates(const VertexArray &vertices,
		                            const Vector2 &offset,
		                            unsigned int nbFrames = 1);

		/**
		 * Loads the texture coordinates. Does not check if the number of frames
		 * to load makes sense.
		 * @param newTexture Texture pointer to use as the new texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Animatable::frames
		 */
		void loadTextureCoordinates(TexturePointer newTexture,
		                            const VertexArray &vertices,
		                            const Vector2 &offset,
		                            unsigned int nbFrames = 1);
	protected:
		/**
		 * Method called internally when the current frame is changed.
		 */
		virtual void currentFrameChange();

	private:
		/**
		 * Vector containing the texture's coordinates for each animation frame.
		 */
		std::vector<TextureCoordinates> frames;

		/**
		 * Current frame at which the animation is currently. This represents
		 * the index in the animation's vector of frames, not in the
		 * Animatable's frames attribute. If no animation is playing, contains
		 * 0.
		 */
		unsigned int currentFrame;

		/// Current number of times the animation has looped.
		int currentNbLoops;

		/// Set to true if the animation is paused (false by default).
		bool animationPaused;

		/// Internal time counter for animations.
		double animationCounter;

		/**
		 * Index of the frame to show when the body isn't animated. 0 by
		 * default.
		 */
		unsigned int defaultFrame;

		/**
		 * Map to associate names to each animations in the frames attribute.
		 * For example, to get information about a specific animation, you'd do
		 * animations["animationName"].
		 */
		AnimationMap animations;

		/// Name of the animation currently playing.
		std::string currentAnimation;
	};

}

#endif
