/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_ENTITY_H
#define RB_TILE_MAP_ENTITY_H

#include <string>

#include "PropertyMap.h"

namespace RedBox {
	class TileMapEntity {
	public:
		/**
		 * Default constructor.
		 */
		explicit TileMapEntity(const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src TileMapEntity to make a copy of.
		 */
		TileMapEntity(const TileMapEntity &src);

		/**
		 * Destructor.
		 */
		virtual ~TileMapEntity();

		/**
		 * Assignment operator.
		 * @param src TileMapEntity to copy.
		 * @return Reference to the modified TileMapEntity.
		 */
		TileMapEntity &operator=(const TileMapEntity &src);

		/**
		 * Gets the entity's properties.
		 * @return Reference to the entity's properties.
		 * @see RedBox::TileMapEntity::properties
		 */
		PropertyMap &getProperties();

		/**
		 * Gets the entity's properties.
		 * @return Const reference to the entity's properties.
		 * @see RedBox::TileMapEntity::properties
		 */
		const PropertyMap &getProperties() const;

		/**
		 * Gets the entity's name.
		 * @return Name of the entity. If it doesn't have one the string will
		 * be empty.
		 * @see RedBox::TileMapEntity::name
		 */
		const std::string &getName() const;

		/**
		 * Sets the name of the entity.
		 * @param newName New name to give to the entity.
		 * @see RedBox::TileMapEntity::name
		 */
		virtual void setName(const std::string &newName);
	private:
		/// Name of the entity. Empty if the entity doesn't have a name.
		std::string name;

		/// Custom properties of the entity.
		PropertyMap properties;
	};

}

#endif // RB_TILE_MAP_ENTITY_H
