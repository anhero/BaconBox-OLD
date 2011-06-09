#ifndef RB_MAIN_WINDOW_H
#define RB_MAIN_WINDOW_H

#include <sigly.h>

#include <string>

namespace RedBox {
	class MainWindow : public sigly::HasSlots<> {
	public:
		static MainWindow& getInstance();
		virtual void onRedBoxInit(int width, int height)=0;
		virtual void show()=0;
		virtual void setCaption(const std::string& caption)=0;
	protected:
		MainWindow();
	};
}

#endif
