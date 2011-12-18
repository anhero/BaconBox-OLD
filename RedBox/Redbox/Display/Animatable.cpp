#include "Animatable.h"

#include <cassert>
#include <cmath>

#include "Engine.h"
#include "TextureInformation.h"

namespace RedBox {
	Animatable::Animatable(TexturePointer newTexture) :
		Updateable(), TextureMappable(newTexture), frames(),
		currentFrame(0), currentNbLoops(-1), animationPaused(true),
		animationCounter(0.0), defaultFrame(0), animations(),
		currentAnimation() {
	}

	Animatable::Animatable(TexturePointer newTexture,
	                       const VerticesArray &vertices,
	                       const Vector2 &offset,
	                       unsigned int nbFrames) : Updateable(),
		TextureMappable(newTexture), frames(), currentFrame(0),
		currentNbLoops(-1), animationPaused(true), animationCounter(0.0),
		defaultFrame(0), animations(), currentAnimation() {
		loadTextureCoordinates(vertices, offset, nbFrames);
	}

	Animatable::Animatable(const Animatable &src) : Updateable(src),
		TextureMappable(src), frames(src.frames),
		currentFrame(src.currentFrame), currentNbLoops(src.currentNbLoops),
		animationPaused(src.animationPaused),
		animationCounter(src.animationCounter), defaultFrame(src.defaultFrame),
		animations(src.animations), currentAnimation(src.currentAnimation) {
	}

	Animatable::~Animatable() {
	}

	Animatable &Animatable::operator=(const Animatable &src) {
		this->TextureMappable::operator=(src);

		if (this != &src) {
			frames = src.frames;
			currentFrame = src.currentFrame;
			currentNbLoops = src.currentNbLoops;
			animationPaused = src.animationPaused;
			animationCounter = src.animationCounter;
			defaultFrame = src.defaultFrame;
			animations = src.animations;
			currentAnimation = src.currentAnimation;
		}

		return *this;
	}

	void Animatable::update() {
		// We make check if there is an animation to be played.
		if (!this->isAnimationPaused()) {
			// We get the current animation's definition.
			AnimationMap::const_iterator definition = animations.find(currentAnimation);

			// Normally, the animation should exist.
			assert(definition != animations.end());

			// We check if the time per frame should be positive.
			if (definition->second.timePerFrame > 0.0) {
				animationCounter += Engine::getSinceLastUpdate();

				// We increment the frames if needed.
				double tmp = floor(animationCounter / definition->second.timePerFrame);
				animationCounter -= tmp * definition->second.timePerFrame;
				incrementCurrentFrame(static_cast<unsigned int>(tmp));

			} else {
				// With a time per frame of 0, we increment the current Frame
				// at each update.
				incrementCurrentFrame();
			}
		}
	}

	const TextureCoordinates &Animatable::getCurrentTextureCoordinates() const {
		// We check if there is an animation selected, whether it is paused or
		// not does not matter.
		if (!currentAnimation.empty()) {
			AnimationMap::const_iterator definition = animations.find(currentAnimation);

			// We make sure the current frame is valid (it should be).
			assert(currentFrame < definition->second.frames.size());
			assert(definition->second.frames[currentFrame] < frames.size());

			return frames[definition->second.frames[currentFrame]];

		} else {
			assert(defaultFrame < frames.size());

			return frames[defaultFrame];
		}
	}

	const std::vector<TextureCoordinates> &Animatable::getFrames() const {
		return frames;
	}

	unsigned int Animatable::getCurrentFrame() const {
		return currentFrame;
	}

	void Animatable::setCurrentFrame(unsigned int newCurrentFrame) {
		// We make sure there is an animation selected.
		if (!currentAnimation.empty()) {
			// We find the concerned animation definition.
			AnimationMap::const_iterator definition = animations.find(currentAnimation);

			// We make sure the new current frame is valid.
			if (newCurrentFrame < definition->second.frames.size()) {
				currentFrame = newCurrentFrame;
			}
		}
	}

	void Animatable::incrementCurrentFrame(unsigned int increment) {
		// We make sure there is an animation selected.
		if (!currentAnimation.empty()) {
			// We find the concerned animation definition.
			AnimationMap::const_iterator definition = animations.find(currentAnimation);

			unsigned int tmpCurrentFrame = currentFrame + increment;
			currentFrame = tmpCurrentFrame % definition->second.frames.size();

			// We only increment the number of loops if it's not infinite.
			if (currentNbLoops >= 0) {
				currentNbLoops += tmpCurrentFrame / definition->second.frames.size();

				// We make sure the current frame is stuck at the last frame
				// if the animation is done.
				if (currentNbLoops > definition->second.nbLoops) {
					currentNbLoops = definition->second.nbLoops + 1;
					currentFrame = definition->second.frames.size() - 1;
				}
			}
		}
	}

	int Animatable::getCurrentNbLoops() const {
		return currentNbLoops;
	}

	bool Animatable::isAnimationPaused() const {
		return animationPaused;
	}

	void Animatable::setAnimationPaused(bool newAnimationPaused) {
		if (newAnimationPaused || (isAnimationPaused() && !currentAnimation.empty())) {
			animationPaused = newAnimationPaused;
		}
	}

	void Animatable::pauseAnimation() {
		setAnimationPaused(true);
	}

	void Animatable::resumeAnimation() {
		setAnimationPaused(false);
	}

	unsigned int Animatable::getDefaultFrame() const {
		return defaultFrame;
	}

	void Animatable::setDefaultFrame(unsigned int newDefaultFrame) {
		if (newDefaultFrame < frames.size()) {
			defaultFrame = newDefaultFrame;
		}
	}

	AnimationDefinition *Animatable::getAnimation(const std::string &name) {
		AnimationMap::iterator definition = animations.find(name);

		// We return NULL if the animation wasn't found.
		if (definition == animations.end()) {
			return NULL;

		} else {
			return &definition->second;
		}
	}

	void Animatable::addAnimation(const std::string &newName,
	                              const AnimationDefinition &newAnimationDefinition,
	                              bool overwrite) {
		// We start by making sure the name isn't empty and the animation
		// definition has frame indexes.
		if (!newName.empty() && !newAnimationDefinition.frames.empty()) {
			// We make sure that each frame indexes are in the correct range.
			bool okay = true;
			std::vector<unsigned int>::const_iterator i = newAnimationDefinition.frames.begin();

			while (i != newAnimationDefinition.frames.end() && okay) {
				if (*i >= frames.size()) {
					okay = false;

				} else {
					++i;
				}
			}

			// If the animation definition is okay, we can now add it.
			if (okay) {
				std::pair<AnimationMap::iterator, bool> inserted = animations.insert(std::make_pair(newName, newAnimationDefinition));

				// If an animation already existed and we are supposed to overwrite it.
				if (!inserted.second && overwrite) {
					// We overwrite the animation definition.
					inserted.first->second = newAnimationDefinition;

					// If we replaced the animation that is currently being
					// played, we restart it.
					if (newName == currentAnimation) {
						startAnimation(newName);
					}
				}
			} else {
				Console::print("Failed to add the animation named \"");
				Console::print(newName);
				Console::println("\" because one of its frame index was too high.");
				Console::printTrace();
			}
		}
	}

	void Animatable::addAnimation(const std::string &newName,
	                              double newTimePerFrame,
	                              int newNbLoops, unsigned int nbFrames, ...) {
		// We start by making sure the name isn't empty and the animation
		// definition has frame indexes.
		if (!newName.empty() && nbFrames > 0) {
			std::pair<AnimationMap::iterator, bool> insertionResult = animations.insert(std::make_pair(newName, AnimationDefinition()));

			// If there wasn't already an animation with the same name.
			if (insertionResult.second) {
				insertionResult.first->second.frames.resize(nbFrames);
				va_list lstFrames;
				va_start(lstFrames, nbFrames);

				std::vector<unsigned int>::iterator i = insertionResult.first->second.frames.begin();
				bool okay = true;

				while (okay &&
				       i != insertionResult.first->second.frames.end()) {
					*i = va_arg(lstFrames, unsigned int);

					if (*i >= frames.size()) {
						okay = false;
					}

					++i;
				}

				va_end(lstFrames);

				if (okay) {
					insertionResult.first->second.timePerFrame = newTimePerFrame;
					insertionResult.first->second.nbLoops = newNbLoops;

				} else {
					animations.erase(insertionResult.first);
				}
			}

		} else {
			Console::print("Failed to add the animation named : ");
			Console::println(newName);
			Console::printTrace();
		}
	}

	void Animatable::removeAnimation(const std::string &name) {
		// We make sure the name isn't empty.
		if (!name.empty()) {
			// If the name we are about to remove is the same as the current
			// animation, we stop the animation.
			if (name == currentAnimation) {
				stopAnimation();
			}

			// We remove the animation definition.
			animations.erase(name);
		}
	}

	const std::string &Animatable::getCurrentAnimation() const {
		return currentAnimation;
	}

	void Animatable::startAnimation(const std::string &name) {
		if (name.empty()) {
			stopAnimation();

		} else {
			// We get the animation definition.
			AnimationMap::const_iterator definition = animations.find(name);

			// We make sure the animation exists.
			if (definition != animations.end()) {
				// We reset the animation.
				currentFrame = 0;
				currentAnimation = name;
				animationPaused = false;
				currentNbLoops = (definition->second.nbLoops < 0) ? (-1) : (0);
				animationCounter = 0.0;
			}
		}
	}

	void Animatable::stopAnimation() {
		// We make sure there are no animations playing.
		currentFrame = 0;
		currentAnimation.clear();
		animationPaused = true;
		currentNbLoops = -1;
		animationCounter = 0.0;
	}

	void Animatable::loadTextureCoordinates(const VerticesArray &vertices,
	                                        const Vector2 &offset,
	                                        unsigned int nbFrames) {
		Vector2 delta(vertices.getSize());
		Vector2 tmpOffset(offset);
        
        if (nbFrames == 0) {
            unsigned int nbOfXframe = this->getTextureInformation()->imageWidth/vertices.getWidth();
            unsigned int nbOfYframe = this->getTextureInformation()->imageHeight/vertices.getHeight();
            nbFrames = nbOfXframe * nbOfYframe;
        }
        
		frames.resize(nbFrames);

		for (std::vector<TextureCoordinates>::iterator i = frames.begin();
		     i != frames.end(); ++i) {
			i->resize(vertices.getNbVertices());
			TextureMappable::loadTextureCoordinates(this->getTextureInformation(), vertices, tmpOffset, &(*i));
			tmpOffset.addToX(delta.getX());

			// We make sure the texture information is valid before checking
			// its image width.
			if (this->getTextureInformation() &&
			    tmpOffset.getX() + delta.getX() > static_cast<float>(this->getTextureInformation()->imageWidth)) {
				tmpOffset.addToY(delta.getY());
				tmpOffset.setX(0.0f);
			}
		}
	}

	void Animatable::loadTextureCoordinates(TexturePointer newTexture,
	                                        const VerticesArray &vertices,
	                                        const Vector2 &offset,
	                                        unsigned int nbFrames) {
		this->setTextureInformation(newTexture);
		this->loadTextureCoordinates(vertices, offset, nbFrames);
	}
}
