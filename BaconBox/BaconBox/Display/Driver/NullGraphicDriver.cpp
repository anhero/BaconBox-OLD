#include "BaconBox/Display/Driver/NullGraphicDriver.h"

namespace BaconBox {
	NullGraphicDriver &NullGraphicDriver::getInstance() {
		static NullGraphicDriver instance;
		return instance;
	}

	void NullGraphicDriver::drawShapeWithTextureAndColor(const VertexArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const Color &) {
	}

	void NullGraphicDriver::drawShapeWithTexture(const VertexArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &) {
	}

	void NullGraphicDriver::drawShapeWithColor(const VertexArray &,
	                                           const Color &) {
	}

	void NullGraphicDriver::drawMaskShapeWithTextureAndColor(const VertexArray &,
	                                                         const TextureInformation *,
	                                                         const TextureCoordinates &,
	                                                         const Color &) {
	}

	void NullGraphicDriver::drawMaskShapeWithTexture(const VertexArray &,
	                                                 const TextureInformation *,
	                                                 const TextureCoordinates &) {
	}

	void NullGraphicDriver::drawMaskedShapeWithTextureAndColor(const VertexArray &,
	                                                           const TextureInformation *,
	                                                           const TextureCoordinates &,
	                                                           const Color &,
	                                                           bool) {
	}

	void NullGraphicDriver::unmaskShape(const VertexArray &) {
	}

	void NullGraphicDriver::drawBatchWithTextureAndColor(const VertexArray &,
	                                                     const TextureInformation *,
	                                                     const TextureCoordinates &,
	                                                     const IndiceArray &,
	                                                     const IndiceArrayList &,
	                                                     const ColorArray &) {
	}

	void NullGraphicDriver::drawBatchWithTexture(const VertexArray &,
	                                             const TextureInformation *,
	                                             const TextureCoordinates &,
	                                             const IndiceArray &,
	                                             const IndiceArrayList &) {
	}

	void NullGraphicDriver::drawMaskBatchWithTextureAndColor(const VertexArray &,
	                                                         const TextureInformation *,
	                                                         const TextureCoordinates &,
	                                                         const IndiceArray &,
	                                                         const IndiceArrayList &,
	                                                         const ColorArray &) {
	}

	void NullGraphicDriver::drawMaskedBatchWithTextureAndColor(const VertexArray &,
	                                                           const TextureInformation *,
	                                                           const TextureCoordinates &,
	                                                           const IndiceArray &,
	                                                           const IndiceArrayList &,
	                                                           const ColorArray &,
	                                                           bool) {
	}
    
    void NullGraphicDriver::deleteTexture(TextureInformation * textureInfo){
        
    }

	void NullGraphicDriver::unmaskBatch(const VertexArray &,
	                                    const IndiceArray &,
	                                    const IndiceArrayList &) {
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

