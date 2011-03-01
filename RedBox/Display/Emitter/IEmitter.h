/**
 * @file
 * @ingroup Display
 */
#ifndef RB_IEMITTER_H
#define RB_IEMITTER_H

#include "Renderable.h"

namespace RedBox {
	class IEmitter: public Renderable {
	public:
		IEmitter();
		IEmitter(const IEmitter& src);
		virtual ~IEmitter();
		IEmitter& operator=(const IEmitter& src);
		virtual void update()=0;
		virtual void render()=0;
	protected:
	private:
		void copyFrom(const IEmitter& src);
		void clean();
	};
}
#endif