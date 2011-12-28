/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDERBATCH_H
#define RB_RENDERBATCH_H

#include <set>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

#include "Orderable.h"
#include "Updateable.h"
#include "Maskable.h"
#include "Vector2.h"
#include "ColorArray.h"
#include "IndiceArray.h"
#include "RenderModable.h"
#include "Console.h"
#include "GraphicDriver.h"
#include "StandardVertexArray.h"
#include "TextureCoordinates.h"
#include "TextureInformation.h"
#include "Texturable.h"

namespace RedBox {
	/**
	 * Represents a batch of sprites to render at the same time.
	 * @ingroup Display
	 * @tparam Type of graphic contained. Either BatchedSprite or
	 * BatchedInanimateSprite.
	 */
	template <typename T>
	class RenderBatch : virtual public Updateable, virtual public Maskable,
		public RenderModable, public Texturable {
		template <typename U, typename V> friend class BatchedGraphic;
		template <typename U> friend class BatchedVertexArray;
	public:
		typedef std::multiset<T *, Orderable::LessCompare> BodyMap;

		typedef std::list<typename BodyMap::value_type> BodyList;

		/**
		 * Default constructor.
		 */
		RenderBatch() : Updateable(), Maskable(), RenderModable(), Texturable(),
			bodies(), toAdd(), toRemove(), toChange(), indices(), vertices(),
			textureCoordinates(), colors(), updating(false), currentMask(NULL) {
			renderModes.set(RenderMode::TEXTURE);
		}

		/**
		 * Destructor.
		 */
		virtual ~RenderBatch() {
			free();
		}

		/**
		 * Updates the body.
		 */
		virtual void update() {
			// We add the sprites that are waiting to be added.
			std::for_each(toAdd.rbegin(), toAdd.rend(), std::bind1st(std::mem_fun(&RenderBatch<T>::add), this));

			toAdd.clear();

			// We take note that we are updating the batch's bodies.
			updating = true;

			typename BodyMap::value_type tmpBody;

			// We update the bodies.
			typename BodyMap::iterator i = bodies.begin();

			while (i != bodies.end()) {
				// We check if it needs to be deleted.
				if ((*i)->isToBeDeleted()) {
					// We add it to the list of sprites that are waiting to be
					// removed.
					toRemove.push_back(*i);

					// We remove the body from the container.
					bodies.erase(i++);

				} else {
					// We update the body.
					(*i)->update();

					// We check if the body's z coordinate has changed.
					if ((*i)->isKeyChanged()) {
						// We make a backup copy of its vertices.
						(*i)->getVertices().unlinkVertices();

						// We remove the body's vertices from the array.
						tmpBody = *i;
						bodies.erase(i++);
						removeVertices(tmpBody->getVertices().begin, tmpBody->getVertices().getNbVertices());

						toChange.push_back(tmpBody);

					} else {
						++i;
					}
				}
			}

			// We take note that we are done updating the batch's bodies.
			updating = false;

			// We remove the bodies that are waiting to be removed.
			typename BodyList::value_type tmp;

			while (!toRemove.empty()) {
				tmp = toRemove.front();
				toRemove.pop_front();
				removeVertices(tmp->getVertices().begin, tmp->getVertices().getNbVertices());
				delete tmp;
			}

			// We re-insert the bodies that had their z changed.
			std::for_each(toChange.begin(), toChange.end(), std::bind1st(std::mem_fun(&RenderBatch::add), this));

			toChange.clear();
		}

		/**
		 * Renders the body in the context.
		 */
		virtual void render() {
			// The render mode for textures has to be set.
			if (renderModes.isSet(RenderMode::TEXTURE)) {
				if (renderModes.isSet(RenderMode::INVERSE_MASKED)) {
					if (currentMask) {
						currentMask->mask();

						GraphicDriver::getInstance().drawMaskedBatchWithTextureAndColor(vertices,
						                                                                this->getTextureInformation(),
						                                                                textureCoordinates,
						                                                                indices,
						                                                                colors,
						                                                                true);

						currentMask->unmask();
					}

				} else if (renderModes.isSet(RenderMode::MASKED)) {
					if (currentMask) {
						currentMask->mask();

						GraphicDriver::getInstance().drawMaskedBatchWithTextureAndColor(vertices,
						                                                                this->getTextureInformation(),
						                                                                textureCoordinates,
						                                                                indices,
						                                                                colors,
						                                                                true);

						currentMask->unmask();
					}

				} else {
					GraphicDriver::getInstance().drawBatchWithTextureAndColor(vertices,
					                                                          this->getTextureInformation(),
					                                                          textureCoordinates,
					                                                          indices,
					                                                          colors);
				}
			}
		}

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		virtual void mask() {
			GraphicDriver::getInstance().drawMaskBatchWithTextureAndColor(vertices, this->getTextureInformation(), textureCoordinates, indices, colors);
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask() {
			GraphicDriver::getInstance().unmaskBatch(vertices, indices);
		}

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		virtual Maskable *getMask() const {
			return currentMask;
		}

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(Maskable *newMask, bool inverted = false) {
			currentMask = newMask;

			// If the new mask is valid.
			if (currentMask) {
				// We set the flags correctly depending on the "inverted"
				// parameter.
				renderModes.set(RenderMode::INVERSE_MASKED, inverted);
				renderModes.set(RenderMode::MASKED, !inverted);

			} else {
				// If we removed the batch's mask, we reset the flags.
				renderModes.set(RenderMode::INVERSE_MASKED, false);
				renderModes.set(RenderMode::MASKED, false);
			}
		}

		/**
		 * Adds a body to the render batch.
		 * @param nbVertices Number of vertices to give to the sprite.
		 * @param z Z layer in the batch to insert the new sprite.
		 */
		typename BodyMap::value_type add(VertexArray::SizeType nbVertices, int z) {
			typename BodyMap::value_type result;

			if (updating) {
				toAdd.push_back(new T(this, new VertexArray::ContainerType(nbVertices)));
				result = toAdd.back();

			} else {
				// We initialize the body.
				result = new T(this, 0, nbVertices);
				// We set its z.
				result->setZ(z);
				// We tell it it's now managed.
				result->managed = true;
				// We reset the keyChanged to false.
				result->keyChanged = false;
				// We insert the body in the batch.
				bodies.insert(result);

				// We find the place to insert the body's vertices, texture
				// coordinates and colors in the arrays.
				VertexArray::SizeType tmpBegin = 0;
				bool found = false;

				for (typename BodyMap::iterator i = bodies.begin();
				     i != bodies.end(); ++i) {
					if (found) {
						(*i)->getVertices().begin += nbVertices;

					} else if (*i == result) {
						result->getVertices().begin = tmpBegin;
						found = true;

					} else {
						tmpBegin = (*i)->getVertices().begin +
						           (*i)->getVertices().getNbVertices();
					}
				}

				// We make sure to also keep the bodies' index updated in the
				// list of bodies to remove.
				for (typename BodyList::iterator i = toRemove.begin();
				     i != toRemove.end(); ++i) {
					if ((*i)->getVertices().begin >= result->getVertices().begin) {
						(*i)->getVertices().begin += nbVertices;
					}
				}

				// We insert the vertices, the texture coordinates and the
				// colors in the arrays.
				vertices.insert(vertices.getBegin() + result->getVertices().begin,
				                nbVertices, Vector2());
				textureCoordinates.insert(textureCoordinates.begin() + result->getVertices().begin,
				                          nbVertices, Vector2());
				colors.insert(colors.begin() + result->getVertices().begin, nbVertices, result->getColor());

				// We ref*resh the batch's indices.
				refreshIndices();

				// We refresh the new body's texture coordinates.
				result->refreshTextureCoordinates();
			}

			return result;
		}

		/**
		 * Adds a sprite to the render batch.
		 * @param newBody Pointer to the new batched sprite to add to the render
		 * batch. A sprite cannot be in two render batches.
		 */
		typename BodyMap::value_type add(typename BodyMap::value_type newBody) {
			// We make sure the pointer is valid and that the body isn't already
			// managed.
			if (newBody && !newBody->isManaged() &&
			    newBody->getVertices().vertices) {
				if (updating) {
					toAdd.push_back(newBody);

				} else {
					// We make sure the number of vertices is correct.
					newBody->getVertices().nbVertices = newBody->getVertices().vertices->size();
					newBody->getVertices().batch = this;
					newBody->managed = true;
					newBody->keyChanged = false;

					// We insert the new body in the batch.
					bodies.insert(newBody);

					// We update the bodies' index and we get the new body's
					// index.
					VertexArray::SizeType tmpBegin = 0;
					bool found = false;

					for (typename BodyMap::iterator i = bodies.begin();
					     i != bodies.end(); ++i) {
						if (found) {
							(*i)->getVertices().begin += newBody->getVertices().nbVertices;

						} else if (*i == newBody) {
							newBody->getVertices().begin = tmpBegin;
							found = true;

						} else {
							tmpBegin = (*i)->getVertices().begin + (*i)->getVertices().nbVertices;
						}
					}

					for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
						if ((*i)->getVertices().begin >= newBody->getVertices().begin) {
							(*i)->getVertices().begin += newBody->getVertices().nbVertices;
						}
					}

					vertices.insert(vertices.getBegin() + newBody->getVertices().begin, newBody->getVertices().vertices->begin(), newBody->getVertices().vertices->end());
					textureCoordinates.insert(textureCoordinates.begin() + newBody->getVertices().begin, newBody->getVertices().getNbVertices(), Vector2());
					colors.insert(colors.begin() + newBody->getVertices().begin, newBody->getVertices().getNbVertices(), newBody->getColor());

					newBody->refreshTextureCoordinates();

					delete newBody->getVertices().vertices;
					newBody->getVertices().vertices = NULL;

					refreshIndices();
				}
			}

			return newBody;
		}
	private:
		/**
		 * Clears the render batch.
		 */
		void clear() {
			if (!updating) {
				free();

				bodies.clear();
				toAdd.clear();
				toRemove.clear();
				toChange.clear();
				vertices.clear();
				textureCoordinates.clear();
				colors.clear();

			} else {
				Console::println("Could not clear the render batch because it's currently updating its bodies.");
			}
		}

		/**
		 * Frees all memory dynamically allocated by the batch.
		 */
		void free() {
			for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {
				delete *i;
			}

			for (typename BodyList::iterator i = toAdd.begin(); i != toAdd.end(); ++i) {
				delete *i;
			}

			for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
				delete *i;
			}

			for (typename BodyList::iterator i = toChange.begin(); i != toChange.end(); ++i) {
				delete *i;
			}
		}

		/**
		 * Adds vertices in the batch.
		 * @param position
		 */
		void addVertices(VertexArray::SizeType position,
		                 VertexArray::SizeType nbVertices) {
			// We make sure the given parameters make sense.
			if (nbVertices && position < vertices.getNbVertices()) {

				// We update the bodies' vertices index.
				for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {
					if ((*i)->getVertices().begin >= position) {
						(*i)->getVertices().begin += nbVertices;
					}
				}

				// We do so too for the bodies that are to be removed but aren't
				// yet.
				for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
					if ((*i)->getVertices().begin >= position) {
						(*i)->getVertices().begin += nbVertices;
					}
				}

				// We add the vertices to the arrays.
				vertices.insert(vertices.getBegin() + position, nbVertices);
				textureCoordinates.insert(textureCoordinates.begin() + position, nbVertices, TextureCoordinates::value_type());
				colors.insert(colors.begin() + position, nbVertices, ColorArray::value_type());

				// We refresh the indices, the texture coordinates and the color
				// arrays.
				this->refreshAll();

			} else {
				Console::print("Failed to add ");
				Console::print(nbVertices);
				Console::print(" vertices at the position ");
				Console::print(position);
				Console::print(" in a batch that has ");
				Console::print(vertices.getSize());
				Console::print(" vertices.");
				Console::printTrace();
			}
		}

		/**
		 * Removes vertices from the batch array.
		 * @param position Index of the first vertex to remove.
		 * @param nbVertices Number of vertices to remove.
		 */
		void removeVertices(VertexArray::SizeType position,
		                    VertexArray::SizeType nbVertices) {
			// We make sure the given parameters make sense.
			if (nbVertices && position < vertices.getNbVertices()) {

				// We update the bodies' vertices index.
				for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {
					if ((*i)->getVertices().begin >= position) {
						(*i)->getVertices().begin -= nbVertices;
					}
				}

				// We do so too for the bodies that are to be removed but aren't
				// yet.
				for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
					if ((*i)->getVertices().begin >= position) {
						(*i)->getVertices().begin -= nbVertices;
					}
				}

				// We remove the vertices to the arrays.
				vertices.erase(vertices.getBegin() + position, vertices.getBegin() + position + nbVertices);
				textureCoordinates.erase(textureCoordinates.begin() + position, textureCoordinates.begin() + position + nbVertices);
				colors.erase(colors.begin() + position, colors.begin() + position + nbVertices);

				// We refresh the indices, the texture coordinates and the color
				// arrays.
				this->refreshAll();

			} else {
				Console::print("Failed to remove ");
				Console::print(nbVertices);
				Console::print(" vertices at the position ");
				Console::print(position);
				Console::print(" in a batch that has ");
				Console::print(vertices.getNbVertices());
				Console::print(" vertices.");
				Console::printTrace();
			}
		}

		/**
		 * Reconstructs the indices.
		 */
		void refreshIndices() {
			// We clear the current indices.
			indices.clear();

			// We calculate the number of indices we'll need in the array.
			IndiceArray::size_type nbIndices = 0;

			for (typename BodyMap::const_iterator i = bodies.begin(); i != bodies.end(); ++i) {
				nbIndices += ((*i)->getVertices().getNbVertices() - 2) * 5 + 1;
			}

			// We reserve the necessary memory.
			indices.reserve(nbIndices);

			IndiceArray::value_type indiceIterator = 0;

			// We initialize the indices for each body's vertices.
			for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {

				// We make sure the body has at least 3 vertices.
				if ((*i)->getVertices().getNbVertices() >= 3) {
					// We get the body's first vertex's indice.
					indiceIterator = static_cast<IndiceArray::value_type>((*i)->getVertices().begin);

					// We add the indices for each of the body's triangles.
					for (IndiceArray::value_type j = 0;
					     j < static_cast<IndiceArray::value_type>((*i)->getVertices().getNbVertices());
					     ++j) {
						indices.push_back(indiceIterator);
						indices.push_back(indiceIterator);
						indices.push_back(indiceIterator + j + 1);
						indices.push_back(indiceIterator + j + 2);
						indices.push_back(indiceIterator + j + 2);
					}
				}
			}
		}

		/**
		 * Reconstructs the indices and refreshes the colors and the texture
		 * coordinates.
		 */
		void refreshAll() {
			refreshIndices();

			// We update each body's color and texture coordinates.
			for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {
				(*i)->setColor((*i)->getColor());
				(*i)->refreshTextureCoordinates();
			}
		}

		/// Contains all of the bodies to be rendered in batch.
		BodyMap bodies;

		/**
		 * Contains all the bodies that are waiting to be added in the main
		 * container.
		 */
		BodyList toAdd;

		/**
		 * Contains all the bodies that are waiting to be removed from the main
		 * container.
		 */
		BodyList toRemove;

		/**
		 * Contains all the bodies that are waiting to be re-inserted in the
		 * main container after their z has changed.
		 */
		BodyList toChange;

		/// Array of vertex indices for the bodies' triangles.
		IndiceArray indices;

		/// Array containing all the bodies' vertices.
		StandardVertexArray vertices;

		/// Array containing the texture coordinates for each vertex.
		TextureCoordinates textureCoordinates;

		/// Array containint the colors for each vertex.
		ColorArray colors;

		/**
		 * Set to true while the render batch is looping through its bodies to
		 * update them. Used to prevent bad access errors when trying to remove
		 * or add bodies to the batch when inside the batch's update loop.
		 */
		bool updating;

		/// Render batch's current mask.
		Maskable *currentMask;
	};
}

#endif
