#include "NullGraphicDriver.h"

namespace RedBox {
	NullGraphicDriver &NullGraphicDriver::getInstance() {
		static NullGraphicDriver instance;
		return instance;
	}

	void NullGraphicDriver::drawShapeWithTextureAndColor(const VerticesArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const Color &) {
	}

	void NullGraphicDriver::drawShapeWithTexture(const VerticesArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &) {
	}

	void NullGraphicDriver::drawShapeWithColor(const VerticesArray &,
	                                           const Color &) {
	}

	void NullGraphicDriver::drawMaskShapeWithTextureAndColor(const VerticesArray &,
	                                                         const TextureInformation *,
	                                                         const TextureCoordinates &,
	                                                         const Color &) {
	}

	void NullGraphicDriver::drawMaskShapeWithTexture(const VerticesArray &,
	                                                 const TextureInformation *,
	                                                 const TextureCoordinates &) {
	}

	void NullGraphicDriver::drawMaskedShapeWithTextureAndColor(const VerticesArray &,
	                                                           const TextureInformation *,
	                                                           const TextureCoordinates &,
	                                                           const Color &,
	                                                           bool) {
	}

	void NullGraphicDriver::unmaskShape(const VerticesArray &) {
	}

	void NullGraphicDriver::drawBatchWithTextureAndColor(const VerticesArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const std::vector<unsigned short> &,
	                                                     const std::vector<unsigned char> &) {
	}

	void NullGraphicDriver::drawBatchWithTexture(const VerticesArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &,
	                                             const std::vector<unsigned short> &) {
	}

	void NullGraphicDriver::drawMaskBatchWithTextureAndColor(const VerticesArray &,
	                                                         const TextureInformation *,
	                                                         const TextureCoordinates &,
	                                                         const std::vector<unsigned short> &,
	                                                         const std::vector<unsigned char> &) {
	}

	void NullGraphicDriver::drawMaskedBatchWithTextureAndColor(const VerticesArray &,
	                                                           const TextureInformation *,
	                                                           const TextureCoordinates &,
	                                                           const std::vector<unsigned short> &,
	                                                           const std::vector<unsigned char> &,
	                                                           bool) {
	}

	void NullGraphicDriver::unmaskBatch(const VerticesArray &,
	                                    const std::vector<unsigned short> &) {
	}

	void NullGraphicDriver::prepareScene(const Vector2 &, float,
	                                     const Vector2 &, const Color &) {
	}


	void NullGraphicDriver::initializeGraphicDriver() {
	}

	void NullGraphicDriver::pushMatrix() {
	}

	void NullGraphicDriver::translate(const Vector2 &) {
	}

	void NullGraphicDriver::loadIdentity() {
	}

	void NullGraphicDriver::popMatrix() {
	}

	TextureInformation *NullGraphicDriver::loadTexture(PixMap *) {
		return NULL;
	}

	NullGraphicDriver::NullGraphicDriver() {
	}

	NullGraphicDriver::~NullGraphicDriver() {
	}
}

