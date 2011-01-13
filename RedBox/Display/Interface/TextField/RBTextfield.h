#import <UIKit/UIKit.h>

#include "TextField.h"

namespace RedBox {
	class TextField;
}
@interface RBTextfield : UITextField {
	RedBox::TextField * abstractTextField;
}

- (int) getMaxLenght;
- (void) setAbstractTextField:(RedBox::TextField *)aTextField;
- (RedBox::TextField*) getAbstractTextField;

@end
