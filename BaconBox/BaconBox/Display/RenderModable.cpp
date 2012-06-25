#include "RenderModable.h"

namespace BaconBox {
	RenderModable::RenderModable() : renderModes() {
	}

	RenderModable::RenderModable(const RenderModable &src) :
		renderModes(src.renderModes) {
	}

	RenderModable::~RenderModable() {
	}

	RenderModable &RenderModable::operator=(const RenderModable &src) {
		if (this != &src) {
			renderModes = src.renderModes;
		}

		return *this;
	}

	const FlagSet<RenderMode>& RenderModable::getRenderModes() const {
		return renderModes;
	}

	void RenderModable::setRenderModes(const FlagSet<RenderMode> &newRenderModes) {
		renderModes = newRenderModes;
	}

	void RenderModable::addRenderModes(const FlagSet<RenderMode> &newRenderModes) {
		renderModes |= newRenderModes;
	}

	void RenderModable::addRenderMode(RenderMode newRenderMode) {
		renderModes.set(newRenderMode);
	}

	void RenderModable::removeRenderModes(const FlagSet<RenderMode>& renderModesToRemove) {
		renderModes.reset(renderModesToRemove);
	}

	void RenderModable::removeRenderMode(RenderMode renderModeToRemove) {
		renderModes.reset(renderModeToRemove);
	}
}
