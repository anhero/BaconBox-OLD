
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
#include <BaconBox/Display/Window/MainWindow.h>
#include <BaconBox/State.h>
#include <BaconBox/Display/SimpleManageable.h>
#include <BaconBox/DebugState.h>
#include <BaconBox/Display/TextureInformation.h>
#include <BaconBox/ResourceManager.h>
#include <BaconBox/Helper/ResourcePathHandler.h>
#include <BaconBox/Display/Gui/SimpleButton.h>
#include <BaconBox/Display/Gui/TextButton.h>
#include <BaconBox/Display/Gui/Checkbox.h>
#include <BaconBox/Display/Gui/LineSlider.h>
#include <BaconBox/Display/InanimateGraphicElement.h>
#include <BaconBox/Display/GraphicElement.h>
#include <BaconBox/Display/InanimateSprite.h>
#include <BaconBox/Display/Sprite.h>
#include <BaconBox/Display/SpriteBatch.h>
#include <BaconBox/Display/SpriteGroup.h>
#include <BaconBox/Display/InanimateSpriteBatch.h>
#include <BaconBox/Display/InanimateSpriteGroup.h>
#include <BaconBox/Helper/CollisionGroup.h>
#include <BaconBox/Display/TextureAtlas.h>
#include <BaconBox/Display/TileMap/TileMap.h>
#include <BaconBox/Display/TileMap/TileLayer.h>
#include <BaconBox/Display/TileMap/ObjectLayer.h>
#include <BaconBox/Display/TileMap/Tileset.h>
#include <BaconBox/Display/TileMap/LineObject.h>
#include <BaconBox/Display/TileMap/PolygonObject.h>
#include <BaconBox/Display/TileMap/RectangleObject.h>
#include <BaconBox/Display/TileMap/TileObject.h>
#include <BaconBox/Display/TileMap/TinyXML/TmxTileMapReader.h>
#include <BaconBox/Display/TileMap/GraphicTileLayer.h>
#include <BaconBox/Display/TileMap/GraphicObjectLayer.h>
#include <BaconBox/Display/TileMap/GraphicTileMap.h>
#include <BaconBox/Helper/Base64.h>
#include <BaconBox/Helper/Compression.h>
#include <BaconBox/Helper/Stopwatch.h>
#include <BaconBox/Display/Text/Font.h>
#include <BaconBox/Display/Text/Text.h>
#include <BaconBox/Helper/Parser.h>
#include <BaconBox/Audio/AudioEngine.h>
#include <BaconBox/Audio/MusicEngine.h>
#include <BaconBox/Audio/SoundEngine.h>
#include <BaconBox/Audio/BackgroundMusic.h>
#include <BaconBox/Audio/SoundFX.h>
#include <BaconBox/Helper/Timer.h>
#include <BaconBox/Emitter/SpriteEmitter.h>
#include <BaconBox/Helper/SpriteFactory.h>
#include <BaconBox/Helper/ShapeFactory.h>
#include <BaconBox/Input/InputManager.h>
#include <BaconBox/Helper/Serialization/DefaultSerializer.h>
#include <BaconBox/Helper/Serialization/JsonSerializer.h>
#include <BaconBox/Helper/Serialization/XmlSerializer.h>
#include <BaconBox/Display/SpriteDefinition.h>
#include <BaconBox/Helper/Serialization/Value.h>
#include <BaconBox/Console.h>
#include <BaconBox/Helper/Tween/Tween.h>
#include <BaconBox/Helper/Tween/StepTween.h>
#include <BaconBox/Display/StandardVertexArray.h>
#include <BaconBox/Console.h>
#include <BaconBox/PlatformFlagger.h>
