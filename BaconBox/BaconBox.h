
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
 * @defgroup TileMap TileMap
 * @ingroup Display
 * @brief Tile map system.
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
 * @defgroup Serialization Serialization
 * @ingroup Helper
 * @brief Classes related to the serializatiof objects.
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

#include <BaconBox/Engine.h>
#include <BaconBox/MainWindow.h>
#include <BaconBox/State.h>
#include <BaconBox/SimpleManageable.h>
#include <BaconBox/DebugState.h>
#include <BaconBox/TextureInformation.h>
#include <BaconBox/ResourceManager.h>
#include <BaconBox/ResourcePathHandler.h>
#include <BaconBox/SimpleButton.h>
#include <BaconBox/TextButton.h>
#include <BaconBox/Checkbox.h>
#include <BaconBox/LineSlider.h>
#include <BaconBox/InanimateGraphicElement.h>
#include <BaconBox/GraphicElement.h>
#include <BaconBox/InanimateSprite.h>
#include <BaconBox/Sprite.h>
#include <BaconBox/SpriteBatch.h>
#include <BaconBox/SpriteGroup.h>
#include <BaconBox/InanimateSpriteBatch.h>
#include <BaconBox/InanimateSpriteGroup.h>
#include <BaconBox/CollisionGroup.h>
#include <BaconBox/TextureAtlas.h>
#include <BaconBox/TileMap.h>
#include <BaconBox/TileLayer.h>
#include <BaconBox/ObjectLayer.h>
#include <BaconBox/Tileset.h>
#include <BaconBox/LineObject.h>
#include <BaconBox/PolygonObject.h>
#include <BaconBox/RectangleObject.h>
#include <BaconBox/TileObject.h>
#include <BaconBox/TmxTileMapReader.h>
#include <BaconBox/GraphicTileLayer.h>
#include <BaconBox/GraphicObjectLayer.h>
#include <BaconBox/GraphicTileMap.h>
#include <BaconBox/Base64.h>
#include <BaconBox/Compression.h>
#include <BaconBox/Stopwatch.h>
#include <BaconBox/Font.h>
#include <BaconBox/Text.h>
#include <BaconBox/Parser.h>
#include <BaconBox/AudioEngine.h>
#include <BaconBox/MusicEngine.h>
#include <BaconBox/SoundEngine.h>
#include <BaconBox/BackgroundMusic.h>
#include <BaconBox/SoundFX.h>
#include <BaconBox/Timer.h>
#include <BaconBox/SpriteEmitter.h>
#include <BaconBox/SpriteFactory.h>
#include <BaconBox/ShapeFactory.h>
#include <BaconBox/InputManager.h>
#include <BaconBox/DefaultSerializer.h>
#include <BaconBox/JsonSerializer.h>
#include <BaconBox/XmlSerializer.h>
#include <BaconBox/SpriteDefinition.h>
#include <BaconBox/Value.h>
#include <BaconBox/Console.h>
#include <BaconBox/Tween.h>
#include <BaconBox/StepTween.h>
#include <BaconBox/StandardVertexArray.h>
#include <BaconBox/Console.h>
#include <BaconBox/PlatformFlagger.h>
