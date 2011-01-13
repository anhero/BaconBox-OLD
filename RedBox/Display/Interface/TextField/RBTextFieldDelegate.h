#include "TextField.h"
@interface RBTextFieldDelegate : NSObject <UITextFieldDelegate>
{
}

+(RBTextFieldDelegate*)getTextFieldDelegate;
@end
