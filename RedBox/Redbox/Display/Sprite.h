/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include <string>

#include "GraphicBody.h"
#include "VerticesGroup.h"
#include "Color.h"
#include "RenderInfo.h"
#include "RenderMode.h"
#include "FlagSet.h"

namespace RedBox {
	struct TextureInfo;
	/**
	 * Represents a sprite. A is used to display animated or non-animated
	 * images or display colored shapes. To use a sprite, initialize it and
	 * pass it to a State. A sprite can only be in one state at a time. Once
	 * you have given the pointer to the state, you don't have to worry about
	 * deleting it, the state takes care of that for you. To remove a sprite
	 * from a state, simply call setToBeDeleted(true), which is inherited from
	 * GraphicBody.
	 * @ingroup Display
	 * @see RedBox::GraphicBody
	 * @see RedBox::State
	 */
	class Sprite : public GraphicBody {
	public:
		/**
		 * Default constructor.
		 */
		Sprite();

		/**
		 * Simple parameterized constructor.
		 * @param textureKey Key to the texture to create a sprite from.
		 */
		Sprite(const std::string& textureKey);

		/**
		 * Simple parameterized constructor. Does the same thing as the
		 * constructor that recieves an key.
		 * @param textureInfo Pointer to the texture information to load the sprite
		 * with.
		 * @see RedBox::RenderInfo::texInfo
		 */
		Sprite(TextureInfo* textureInfo);

		/**
		 * Parameterized constructor. Loads a sprite using the texture in the
		 * resource manager with the corresponding key. Only takes the asked
		 * part of the texture with the given width and height.
		 * @param textureKey Texture's key in the ResourceManager to use for the
		 * constructed sprite.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations)
		 */
		Sprite(const std::string& textureKey,
		       unsigned int frameWidth,
		       unsigned int frameHeight,
		       unsigned int nbFrames = 1);

		/**
		 * Parameterized constructor. Loads a sprite using a pointer to a
		 * TextureInfo. Only takes the asked part of the texture with the given
		 * width and height.
		 * @param textureInfo Pointer to the texture information to load the
		 * sprite from.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations).
		 */
		Sprite(TextureInfo* textureInfo,
		       unsigned int frameWidth,
		       unsigned int frameHeight,
		       unsigned int nbFrames = 1);

		/**
		 * Copy constructor.
		 * @param src Sprite to make a copy of.
		 */
		Sprite(const Sprite& src);

		/**
		 * Assignation operator overload.
		 * @param src Sprite to make a copy of.
		 * @return Reference to the modified sprite.
		 */
		Sprite& operator=(const Sprite& src);

		/**
		 * Destructor. Frees up all allocated memory.
		 */
		virtual ~Sprite();

		/**
		 * Updates the sprite.
		 */
		virtual void update();

		/**
		 * Renders the sprite.
		 */
		virtual void render();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered sprite (if the next sprite
		 * is set as a masked sprite).
		 */
		virtual void mask();

		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked sprite has been rendered.
		 */
		virtual void unmask();

		/**
		 * Gets the graphic body masking the current graphic body.
		 * @return Pointer to the graphic body's mask.
		 */
		virtual GraphicBody* getMask();

		/**
		 * Set the sprite used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inversed Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(GraphicBody* newMask, bool inversed = false);

		/**
		 * Creates a vertex in the vertices group.
		 * @param x Horizontal position.
		 * @param y Vertical position.
		 */
		void createVertex(float x, float y);

		/**
		 * Gets the sprite's center's position.
		 * @return 2D vector containing the sprite's center's position.
		 */
		Vector2 getPositionCenter() const;

		/**
		 * Gets the sprite's center's horizontal position.
		 * @return Sprite's center's horizontal position.
		 */
		float getXPositionCenter() const;

		/**
		 * Gets the sprite's center's vertical position.
		 * @return Sprite's center vertical position.
		 */
		float getYPositionCenter() const;

		using GraphicBody::setPosition;

		/**
		 * Sets the sprite's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 */
		virtual void setPosition(float newXPosition, float newYPosition);

		/**
		 * Gets the sprite's width and height.
		 * @return Vector2 containing the sprite's width and height.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the sprite's width.
		 * @return Sprite's width.
		 */
		virtual float getWidth() const;

		/**
		 * Gets the sprite's height.
		 * @return Sprite's height.
		 */
		virtual float getHeight() const;

		/**
		 * Gets the sprite's main color.
		 * @return Color object containing the color component of the sprite.
		 */
		const Color& getMainColor() const;

		/**
		 * Set the color of the main renderStep with the
		 * given color components Range are from 0 to 255.
		 * Componentes are RGBA.
		 */
		virtual void setMainColor(const Color& newColor);

		/**
		 * Gets the main color's alpha component.
		 * @return Alpha component of the sprite's main color.
		 */
		uint8_t getMainAlpha() const;

		/**
		 * Sets the alpha component on the main renderstep.
		 * @param alpha New alpha component. Range is from 0 to 255.
		 */
		void setMainAlpha(int32_t newAlpha);

		/**
		 * Gets the vertices group.
		 * @return Reference to the sprite's group of vertices.
		 */
		VerticesGroup& getVertices();

		/**
		 * Gets the vertices group.
		 * @return Reference to the sprite's group of vertices.
		 */
		const VerticesGroup& getVertices() const;

		/**
		 * Gets the sprite's left side's position.
		 * @return Sprite's left side's position.
		 */
		float getMinX() const;

		/**
		 * Gets the sprite's right side's position.
		 * @return Sprite's right side's position.
		 */
		float getMaxX() const;

		/**
		 * Gets the sprite's top side's position.
		 * @return Sprite's top side's position.
		 */
		float getMinY() const;

		/**
		 * Gets the sprite's bottom side's position.
		 * @return Sprite's bottom side's position.
		 */
		float getMaxY() const;

		/**
		 * Gets the sprite's render info.
		 * @return Reference to the sprite's render information.
		 */
		RenderInfo& getRenderInfo();

		/**
		 * Gets the sprite's render info.
		 * @return Reference to the sprite's render information.
		 */
		const RenderInfo& getRenderInfo() const;

		/**
		 * Checks if the sprite's animation is paused.
		 * @return True if the animation is paused, false if not.
		 * @see RedBox::Sprite::animationPaused
		 */
		bool isAnimationPaused() const;

		/**
		 * Sets the current animation.
		 * @param name Name of the animation to play.
		 */
		void playAnimation(const std::string& name);

		/**
		 * Pauses the sprite's animation. Stays paused until resumeAnimation()
		 * or playAnimation(...) is called.
		 */
		void pauseAnimation();

		/**
		 * Resumes the paused animation, does nothing if the animation wasn't
		 * paused.
		 */
		void resumeAnimation();

		/**
		 * Gets the name of the current animation.
		 * @return String containing the sprite's current animation. Empty
		 * string if there is no current animation.
		 */
		const std::string& getCurrentAnimation() const;

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
		 */
		void addAnimation(const std::string& name,
		                  double timePerFrame,
		                  int nbLoops,
		                  unsigned int nbFrames, ...);

		/**
		 * Gets the rendering modes.
		 * @return Current rendering modes.
		 */
		const FlagSet<RenderMode>& getRenderModes() const;

		/**
		 * Sets the rendering modes.
		 * @param newMode New mode to be set.
		 */
		void setRenderModes(const FlagSet<RenderMode>& newRenderModes);

		/**
		 * Adds a mode with the bitwise inclusive OR. More than one mode can
		 * be added at the same time using the same operator.
		 * @param newMode New mode to add.
		 */
		void addRenderModes(const FlagSet<RenderMode>& newRenderModes);

		/**
		 * Adds a mode with the bitwise inclusive OR. More than one mode can
		 * be added at the same time using the same operator.
		 * @param newMode New mode to add.
		 */
		void addRenderMode(RenderMode newRenderMode);

		/**
		 * Flip off given mode flags.
		 * @param mode Mode(s) to flip off. You can pass more than one flag like
		 * this: (Flag1 | Flag2).
		 * @see RedBox::RenderStep::mode
		 */
		void removeRenderModes(const FlagSet<RenderMode>& renderModesToRemove);

		/**
		 * Flip off given mode flag.
		 * @param mode Mode(s) to flip off. You can pass more than one flag like
		 * this: (Flag1 | Flag2).
		 * @see RedBox::RenderStep::mode
		 */
		void removeRenderMode(RenderMode renderModeToRemove);

		using GraphicBody::setScaling;

		/**
		 * Change the sprite's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 */
		virtual void setScaling(float newXScaling, float newYScaling);

		/**
		 * Rotates the sprite from a point.
		 * @param rotationAngle Angle to rotate the sprite.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::GraphicBody::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2& rotationPoint);

		/**
		 * Clones the sprite.
		 * @return Pointer to the new Sprite.
		 */
		virtual GraphicBody* clone() const;

	private:
		/// Vertices making up the sprite.
		VerticesGroup vertices;

		/// Contains the render information.
		RenderInfo renderInfo;

		/// Flag set of render modes.
		FlagSet<RenderMode> renderModes;

		/// Set to true if the animation is paused (false by default).
		bool animationPaused;

		/// Internal time counter for animations.
		double animationCounter;

		/**
		 * Constructs the sprite using the given info.
		 * @param textureInfo Pointer to the texture's information.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations).
		 */
		void construct(TextureInfo* textureInfo,
		               unsigned int frameWidth,
		               unsigned int frameHeight,
		               unsigned int nbFrames = 1);
	};
}

#endif // RB_SPRITE_H
