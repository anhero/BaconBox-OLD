#ifndef __TEXTFIELD_H
#define __TEXTFIELD_H

#define NO_TEXTFIELD_MAX_LENGHT -1
#include "Convert.h"
#ifdef RB_IPHONE_PLATFORM
#import "RBTextfield.h"
@class RBTextfield;
@class EAGLView;
#endif

#include "State.h"

namespace RedBox {
	class TextField {
	private:
#ifdef RB_IPHONE_PLATFORM
		RBTextfield * iphoneTextField;
		bool initialized;
#endif
		int maximumLength;
		int minimumLength;

		State * currentState;
		

	public:
		TextField(State * aState);
		~TextField();
		void setMaximumLength(int length);
		int getMaximumLength();
		void setMinimumLength(int length);
		int getMimimumLength();
		
		
		void showTextField();
		void hideTextField();
		void setPosition(int x, int y);
		void setSize(int width, int height);
		void setDefault();
		
		
		void setText(const std::string& text);
		void setText(const std::wstring& text);

		std::wstring getText();
	};
}
#endif