
/** 
 * @defgroup Display Display
 * @brief Display related classes (sprite, drawer, camera, etc.)
 */

/** 
 * @defgroup GraphicDrivers GraphicDrivers
 * @ingroup Display
 * @brief Graphics backend (opengl directX or flash driver)
 */

/**
 * @defgroup GUI GUI
 * @ingroup Display
 * @brief GUI controls like buttons and checkboxes.
 */

/**
 * @defgroup Math Math
 * @brief Classes that have mathematical purposes.
 */

/**
 * @defgroup Helper Helper
 * @brief Classes used for miscellaneous utilities.
 */

/**
 * @defgroup Physics Physics
 * @brief Classes used in the physics engine.
 */

/**
 * @defgroup TextDisplay TextDisplay
 * @ingroup Display
 */

/**
 * @defgroup Audio Audio
 * @brief Classes used for the audio engine.
 */
/**
 * @defgroup Events Events
 * @brief Classes used for the event system.
 */

/**
 * @defgroup Input Input
 * @brief Classes related to player input.
 */

/**
 * @defgroup Debug Debug
 * @brief Classes used to help debugging.
 */

#include <RedBox/Engine.h>
#include <RedBox/State.h>
#include <RedBox/DebugState.h>
#include <RedBox/ResourceManager.h>
#include <RedBox/ResourcePathHandler.h>
#include <RedBox/SimpleButton.h>
#include <RedBox/Checkbox.h>
#include <RedBox/LineSlider.h>
#include <RedBox/Sprite.h>
#include <RedBox/Stopwatch.h>
#include <RedBox/Font.h>
#include <RedBox/GraphicString.h>
#include <RedBox/Parser.h>
#include <RedBox/AudioEngine.h>
#include <RedBox/MusicEngine.h>
#include <RedBox/SoundEngine.h>
#include <RedBox/BackgroundMusic.h>
#include <RedBox/SoundFX.h>
#include <RedBox/Timer.h>
#include <RedBox/SpriteEmitter.h>
#include <RedBox/RenderInfo.h>
#include <RedBox/SpriteFactory.h>
#include <RedBox/InputManager.h>
#include <RedBox/Console.h>
#include <RedBox/Tween.h>
#include <RedBox/LoopingMenu.h>
#include <RedBox/ScrollingMenu.h>
#include <RedBox/SpriteMenuElement.h>
