/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_BATCH_H
#define RB_RENDER_BATCH_H

#include <set>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

#include "BaconBox/Display/Orderable.h"
#include "BaconBox/Display/Updateable.h"
#include "BaconBox/Display/Maskable.h"
#include "BaconBox/Vector2.h"
#include "BaconBox/Display/Driver/ColorArray.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/RenderModable.h"
#include "BaconBox/Console.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Display/StandardVertexArray.h"
#include "BaconBox/Display/TextureCoordinates.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Display/Texturable.h"
#include "BaconBox/Helper/IsBaseOf.h"
#include "BaconBox/Display/Animatable.h"

namespace BaconBox {
	/**
	 * Represents a batch of sprites to render at the same time.
	 * @ingroup Display
	 * @tparam Type of graphic contained. Either BatchedSprite or
	 * BatchedInanimateSprite.
	 */
	template <typename T>
	class RenderBatchParent : virtual public Updateable, virtual public Maskable,
		public RenderModable, public Texturable {
		template <typename U, typename V> friend class BatchedGraphic;
		template <typename U> friend class BatchedVertexArray;
	public:
		typedef T ValueType;
			
		typedef std::multiset<T *, Orderable::LessCompare> BodyMap;

		typedef std::list<typename BodyMap::value_type> BodyList;

		/**
		 * Default constructor.
		 */
		RenderBatchParent() : Updateable(), Maskable(), RenderModable(),
			Texturable(), bodies(), toAdd(), toRemove(), toChange(), indices(),
			vertices(), textureCoordinates(), colors(), updating(false),
			currentMask(NULL) {
			renderModes.set(RenderMode::TEXTURE);
		}

		/**
		 * Parameterized constructor. Constructs the render batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * bodies in the batch will use this texture.
		 */
		explicit RenderBatchParent(TexturePointer newTexture) : Updateable(),
			Maskable(), RenderModable(), Texturable(newTexture), bodies(),
			toAdd(), toRemove(), toChange(), indices(), vertices(),
			textureCoordinates(), colors(), updating(false), currentMask(NULL) {
			renderModes.set(RenderMode::TEXTURE);
		}

		/**
		 * Copy constructor.
		 * @param src Render batch to make a copy of.
		 */
		RenderBatchParent(const RenderBatchParent<T> &src) : Updateable(src),
			Maskable(src), RenderModable(src), Texturable(src), bodies(),
			toAdd(), toRemove(), toChange(), indices(), vertices(),
			textureCoordinates(), colors(), updating(false),
			currentMask(src.currentMask) {

			for (typename BodyMap::const_iterator i = src.bodies.begin();
			     i != src.bodies.end(); ++i) {
				this->add((*i)->clone());
			}

			for (typename BodyList::const_iterator i = src.toAdd.begin();
			     i != src.toAdd.end(); ++i) {
				this->add((*i)->clone());
			}

			for (typename BodyList::const_iterator i = src.toChange.begin();
				 i != src.toChange.end(); ++i) {
				this->add((*i)->clone());
			}
		}

		/**
		 * Destructor.
		 */
		virtual ~RenderBatchParent() {
			free();
		}

		/**
		 * Assignment operator overload.
		 * @param src Render batch to copy.
		 * @return Reference to the modified instance.
		 */
		RenderBatchParent<T> &operator=(const RenderBatchParent<T> &src) {
			this->RenderModable::operator=(src);

			if (this != &src && updating) {
				free();
				clear();

				for (typename BodyMap::const_iterator i = src.bodies.begin();
				     i != bodies.end(); ++i) {
					this->add((*i)->clone());
				}

				for (typename BodyList::const_iterator i = src.toAdd.begin();
					 i != src.toAdd.end(); ++i) {
					this->add((*i)->clone());
				}

				for (typename BodyList::const_iterator i = src.toChange.begin();
					 i != src.toChange.end(); ++i) {
					this->add((*i)->clone());
				}
			}

			return *this;
		}

		/**
		 * Updates the body.
		 */
		virtual void update() {
			// We add the sprites that are waiting to be added.
			std::for_each(toAdd.rbegin(), toAdd.rend(), std::bind1st(std::mem_fun(&RenderBatchParent<T>::add), this));

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
					if ((*i)->isActive()) {
						(*i)->update();
					}

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
			std::for_each(toChange.begin(), toChange.end(), std::bind1st(std::mem_fun(&RenderBatchParent::add), this));

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
						                                                                indiceList,
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
						                                                                indiceList,
						                                                                colors,
						                                                                true);

						currentMask->unmask();
					}

				} else {
					GraphicDriver::getInstance().drawBatchWithTextureAndColor(vertices,
					                                                          this->getTextureInformation(),
					                                                          textureCoordinates,
					                                                          indices,
					                                                          indiceList,
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
			GraphicDriver::getInstance().drawMaskBatchWithTextureAndColor(vertices,
			                                                              this->getTextureInformation(),
			                                                              textureCoordinates,
			                                                              indices,
			                                                              indiceList,
			                                                              colors);
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask() {
			GraphicDriver::getInstance().unmaskBatch(vertices,
			                                         indices,
			                                         indiceList);
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

				// We refresh the batch's indices.
				refreshIndices();

				// We refresh the new body's texture coordinates.
				result->refreshTextureCoordinates();
			}

			return result;
		}

		/**
		 * Adds a sprite to the render batch.
		 * @param newBody Pointer to the new body to add to the render batch. A
		 * body cannot be in two render batches.
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
					typename BodyMap::iterator inserted = bodies.insert(newBody);

					// We set its first vertex's index.
					if (inserted != bodies.begin()) {
						--inserted;
						newBody->getVertices().begin = (*inserted)->getVertices().begin + (*inserted)->getVertices().nbVertices;
						++inserted;

					} else {
						newBody->getVertices().begin = 0;
					}

					++inserted;

					// We increment all the indexes for the following bodies.
					for (typename BodyMap::iterator i = inserted; i != bodies.end(); ++i) {
						(*i)->getVertices().begin += newBody->getVertices().nbVertices;
					}

					for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
						if ((*i)->getVertices().begin >= newBody->getVertices().begin) {
							(*i)->getVertices().begin += newBody->getVertices().nbVertices;
						}
					}

					vertices.insert(vertices.getBegin() + newBody->getVertices().begin, newBody->getVertices().vertices->begin(), newBody->getVertices().vertices->end());
					textureCoordinates.insert(textureCoordinates.begin() + newBody->getVertices().begin, newBody->getVertices().getNbVertices(), Vector2());
					colors.insert(colors.begin() + newBody->getVertices().begin, newBody->getVertices().getNbVertices(), newBody->getColor());

					delete newBody->getVertices().vertices;
					newBody->getVertices().vertices = NULL;

					newBody->refreshTextureCoordinates();

					refreshIndices();
				}
			}

			return newBody;
		}

		/**
		 * Adds new bodies to the render batch. If the given body is already
		 * managed by a render batch, it will add only clones of it. If it is
		 * not already managed, it will add the new body and "nbToAdd - 1"
		 * clones of it.
		 * @param newBody Pointer to the new body to add.
		 * @param nbToAdd Number of bodies to add to the batch.
		 */
		void add(typename BodyMap::value_type newBody,
		         typename BodyMap::size_type nbToAdd) {
			if (nbToAdd > 0 && newBody &&
			    newBody->getVertices().getNbVertices() > 0) {

				// We prepare the batch for the number of vertices we are going
				// to add.
				this->reserveVertices(nbToAdd * newBody->getVertices().getNbVertices());

				// If the body is to be added to the batch, we do so.
				if (!newBody->isManaged() && newBody->getVertices().vertices) {
					--nbToAdd;
					this->add(newBody);
				}

				// We add the bodies.
				if (updating) {
					for (typename BodyMap::size_type i = 0; i < nbToAdd; ++i) {
						toAdd.push_back(newBody->clone());
					}

				} else {
					typename BodyMap::value_type tmp;

					for (typename BodyMap::size_type i = 0; i < nbToAdd; ++i) {
						tmp = newBody->clone();

						// We make sure the number of vertices is correct.
						tmp->getVertices().nbVertices = tmp->getVertices().vertices->size();
						tmp->getVertices().batch = this;
						tmp->managed = true;
						tmp->keyChanged = false;

						// We insert the new body in the batch.
						typename BodyMap::iterator inserted = bodies.insert(tmp);

						// We set its first vertex's index.
						if (inserted != bodies.begin()) {
							--inserted;
							tmp->getVertices().begin = (*inserted)->getVertices().begin + (*inserted)->getVertices().nbVertices;
							++inserted;

						} else {
							tmp->getVertices().begin = 0;
						}

						++inserted;

						// We increment all the indexes for the following bodies.
						for (typename BodyMap::iterator i = inserted; i != bodies.end(); ++i) {
							(*i)->getVertices().begin += tmp->getVertices().nbVertices;
						}

						for (typename BodyList::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
							if ((*i)->getVertices().begin >= tmp->getVertices().begin) {
								(*i)->getVertices().begin += tmp->getVertices().nbVertices;
							}
						}

						vertices.insert(vertices.getBegin() + tmp->getVertices().begin, tmp->getVertices().vertices->begin(), tmp->getVertices().vertices->end());
						textureCoordinates.insert(textureCoordinates.begin() + tmp->getVertices().begin, tmp->getVertices().getNbVertices(), Vector2());
						colors.insert(colors.begin() + tmp->getVertices().begin, tmp->getVertices().getNbVertices(), tmp->getColor());

						delete tmp->getVertices().vertices;
						tmp->getVertices().vertices = NULL;

						tmp->refreshTextureCoordinates();
					}

					refreshIndices();
				}
			}
		}

		/**
		 * Increases the batch's capacity to prepare to add new sprites to the
		 * batch. For example, it would be usefull to use before adding 100
		 * batched sprites that each have 4 vertices, you would ask the batch
		 * with this function to reserve 400 vertices. The addition of those
		 * batched sprites would then be a lot faster.
		 * @param nbVerticesToReserve Number of vertices to reserve. If you're
		 * about to add 300 sprites with 5 vertices each, you would call this
		 * function and give the value 1500 to this parameter.
		 */
		void reserveVertices(VertexArray::SizeType nbVerticesToReserve) {
			vertices.reserve(vertices.getNbVertices() + nbVerticesToReserve);
			textureCoordinates.reserve(textureCoordinates.size() + nbVerticesToReserve);
			colors.reserve(colors.size() + nbVerticesToReserve);
		}

		/**
		 * Gets the iterator to the batch's first body.
		 * @return Iterator to the batch's first body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::iterator getBegin() {
			return bodies.begin();
		}

		/**
		 * Gets the const iterator to the batch's first body.
		 * @return Const iterator to the batch's first body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::const_iterator getBegin() const {
			return bodies.begin();
		}

		/**
		 * Gets the iterator to the element body following the last body. This
		 * element acts as a placeholder, attempting to access it results in
		 * undefined behavior.
		 * @return Iterator to the body following the last body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::iterator getEnd() {
			return bodies.end();
		}

		/**
		 * Gets the const iterator to the element body following the last body.
		 * This element acts as a placeholder, attempting to access it results
		 * in undefined behavior.
		 * @return Const iterator to the body following the last body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::const_iterator getEnd() const {
			return bodies.end();
		}

		/**
		 * Gets the reverse iterator to the first body of the reversed render
		 * batch. Corresponds to the last body of the non-reversed render batch.
		 * @return Reverse iterator to the first body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::reverse_iterator getReverseBegin() {
			return bodies.rbegin();
		}

		/**
		 * Gets the const reverse iterator to the first body of the reversed
		 * render batch. Corresponds to the last body of the non-reversed render
		 * batch.
		 * @return Const everse iterator to the first body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::const_reverse_iterator getReverseBegin() const {
			return bodies.rbegin();
		}

		/**
		 * Gets the reverse iterator to the body following the last body of the
		 * reversed render batch. It corresponds to the body preceding the first
		 * body of the non-reversed render batch. This body acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Reverse iterator to the body follwing the last body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::reverse_iterator getReverseEnd() {
			return bodies.rend();
		}

		/**
		 * Gets the const reverse iterator to the body following the last body
		 * of the reversed render batch. It corresponds to the body preceding
		 * the first body of the non-reversed render batch. This body acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Const reverse iterator to the body follwing the last body.
		 * @see BaconBox::RenderBatchParent<T>::bodies
		 */
		typename BodyMap::const_reverse_iterator getReverseEnd() const {
			return bodies.rend();
		}

		/**
		 * Gets the number of bodies in the render batch.
		 * @return Number of bodies the render batch contains.
		 */
		typename BodyMap::size_type getNbBodies() const {
			return bodies.size();
		}
	protected:
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
		 * @param position Position (index) in the batch to add vertices.
		 * @param nbVertices Number of vertices to add.
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
			static const StandardVertexArray::SizeType MAX_NB_INDICES = static_cast<StandardVertexArray::SizeType>(std::numeric_limits<IndiceArray::value_type>::max());

			// We clear the current indices.
			indices.clear();
			indiceList.clear();

			// We calculate the number of indices we'll need in the array.
			IndiceArray::size_type nbIndices = 0;

			for (typename BodyMap::const_iterator i = bodies.begin(); i != bodies.end(); ++i) {
				nbIndices += ((*i)->getVertices().getNbVertices() - 2) * 5 + 1;
			}

			// We reserve the necessary memory.
			indices.reserve(nbIndices);

			IndiceArray::value_type indiceIterator = 0;

			indiceList.push_back(std::make_pair(0, 0));

			// We initialize the indices for each body's vertices.
			for (typename BodyMap::iterator i = bodies.begin(); i != bodies.end(); ++i) {

				// We make sure the body has at least 3 vertices.
				if ((*i)->getVertices().getNbVertices() >= 3) {

					if (((*i)->getVertices().begin + (*i)->getVertices().getNbVertices()) > indiceList.back().first + MAX_NB_INDICES) {
						indiceList.push_back(std::make_pair((*i)->getVertices().begin, indices.size()));
					}

					// We get the body's first vertex's indice.
					indiceIterator = static_cast<IndiceArray::value_type>((*i)->getVertices().begin - indiceList.back().first);


					// We add the indices for each of the body's triangles.
					IndiceArray::value_type nbTriangles = static_cast<IndiceArray::value_type>((*i)->getVertices().getNbVertices() - 2);

					for (IndiceArray::value_type j = 0; j < nbTriangles; ++j) {
						indices.push_back(indiceIterator + j);
						indices.push_back(indiceIterator + j);
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

		/**
		 * Contains all of the bodies to be rendered in batch. Bodies are sorted
		 * by their z value (ascending).
		 */
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

		/// List of indexes for the the batches.
		IndiceArrayList indiceList;

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

	template <typename T, bool ANIMATABLE>
	class RenderBatchMiddle : public RenderBatchParent<T> {
	public:
		/**
		 * Default constructor.
		 */
		RenderBatchMiddle() : RenderBatchParent<T>() {
		}

		/**
		 * Parameterized constructor. Constructs the render batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * bodies in the batch will use this texture.
		 */
		explicit RenderBatchMiddle(TexturePointer newTexture) :
			RenderBatchParent<T>(newTexture) {
		}

		/**
		 * Copy constructor.
		 * @param src Render batch to make a copy of.
		 */
		RenderBatchMiddle(const RenderBatchMiddle<T, ANIMATABLE> &src) :
			RenderBatchParent<T>(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~RenderBatchMiddle() {
		}

		/**
		 * Assignment operator overload.
		 * @param src Render batch to copy.
		 * @return Reference to the modified instance.
		 */
		RenderBatchMiddle<T, ANIMATABLE> &operator=(const RenderBatchMiddle<T, ANIMATABLE> &src) {
			this->RenderBatchParent<T>::operator=(src);
			return *this;
		}
	};

	template <typename T>
	class RenderBatchMiddle<T, true> : public RenderBatchParent<T> {
	public:
		/**
		 * Default constructor.
		 */
		RenderBatchMiddle() : RenderBatchParent<T>() {
		}

		/**
		 * Parameterized constructor. Constructs the render batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * bodies in the batch will use this texture.
		 */
		explicit RenderBatchMiddle(TexturePointer newTexture) :
			RenderBatchParent<T>(newTexture) {
		}

		/**
		 * Copy constructor.
		 * @param src Render batch to make a copy of.
		 */
		RenderBatchMiddle(const RenderBatchMiddle<T, true> &src) :
			RenderBatchParent<T>(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~RenderBatchMiddle() {
		}

		/**
		 * Assignment operator overload.
		 * @param src Render batch to copy.
		 * @return Reference to the modified instance.
		 */
		RenderBatchMiddle<T, true> &operator=(const RenderBatchMiddle<T, true> &src) {
			this->RenderBatchParent<T>::operator=(src);
			return *this;
		}
	};

	template <typename T>
	class RenderBatch :
		public RenderBatchMiddle<T, IsBaseOf<Animatable, T>::RESULT> {
	public:
		/**
		 * Default constructor.
		 */
		RenderBatch() : RenderBatchMiddle<T, IsBaseOf<Animatable, T>::RESULT>() {
		}

		/**
		 * Parameterized constructor. Constructs the render batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * bodies in the batch will use this texture.
		 */
		explicit RenderBatch(TexturePointer newTexture) :
			RenderBatchMiddle<T, IsBaseOf<Animatable, T>::RESULT>(newTexture) {
		}

		/**
		 * Copy constructor.
		 * @param src Render batch to make a copy of.
		 */
		RenderBatch(const RenderBatch<T> &src) :
			RenderBatchMiddle<T, IsBaseOf<Animatable, T>::RESULT>(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~RenderBatch() {
		}

		/**
		 * Assignment operator overload.
		 * @param src Render batch to copy.
		 * @return Reference to the modified instance.
		 */
		RenderBatch<T> &operator=(const RenderBatch<T> &src) {
			this->RenderBatchMiddle<T, IsBaseOf<Animatable, T>::RESULT>::operator=(src);
			return *this;
		}
	};
}

#endif // RB_RENDER_BATCH_H
