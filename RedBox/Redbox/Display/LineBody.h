#ifndef RB_LINE_BODY_H
#define RB_LINE_BODY_H

#include "GraphicBody.h"

namespace RedBox {
	class LineBody : public GraphicBody {
	public:
		/**
		 * Enum used to determine if a line body is horizontal or vertical.
		 */
		enum Orientation {
			HORIZONTAL,
			VERTICAL
		};

		/**
		 * Default constructor.
		 */
		LineBody();

		/**
		 * Parameterized constructor.
		 * @param newLength Line's starting length.
		 * @param newOrientation Line's starting orientation.
		 * @see RedBox::LineBody::length
		 * @see RedBox::LineBod::orientation
		 */
		LineBody(float newLength, Orientation newOrientation);

		/**
		 * Copy constructor.
		 * @param src Line body to make a copy of.
		 */
		LineBody(const LineBody& src);

		/**
		 * Destructor.
		 */
		~LineBody();

		/**
		 * Assignation operator overload.
		 * @param src Line body to make a copy of.
		 * @return Reference to the modified line body.
		 */
		LineBody& operator=(const LineBody& src);

		/**
		 * Updates the line body.
		 * @see RedBox::GraphicBody::update()
		 */
		void update();

		/**
		 * Renders the line body.
		 */
		void render();

		/**
		 * Gets the line body's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the line body's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		/**
		 * Change the line body's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 * @see RedBox::GraphicBody::setScaling(float xScaling, float yScaling)
		 */
		void setScaling(float xScaling, float yScaling);

		/**
		 * Gets the line body's orientation.
		 * @return Line's current orientation, either horizontal or vertical.
		 */
		Orientation getOrientation() const;

		void setOrientation(Orientation newOrientation);

		bool isHorizontal() const;

		void setHorizontal();

		void setHorizontal(float newLength);

		bool isVertical() const;

		void setVertical();

		void setVertical(float newLength);

		float getLength() const;

		void setLength(float newLength);

		void setLengthAndOrientation(float newLength,
									 Orientation newOrientation);
	private:
		/// Line's length.
		float length;

		/// Line's orientation, either horizontal or vertical.
		Orientation orientation;
	};
}

#endif
