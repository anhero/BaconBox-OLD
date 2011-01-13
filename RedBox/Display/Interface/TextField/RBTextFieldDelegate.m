#import "RBTextFieldDelegate.h"

@implementation RBTextFieldDelegate

static RBTextFieldDelegate * textFieldDelegateSingleton;


+ (RBTextFieldDelegate*)getTextFieldDelegate{
	return textFieldDelegateSingleton;
}

+(void) initialize
{
	textFieldDelegateSingleton = [[RBTextFieldDelegate alloc] init];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
	RBTextfield * aTextfield = (RBTextfield*)textField;
	RedBox::TextField * abstractTextField = [aTextfield getAbstractTextField];
	int maxLenght = abstractTextField->getMaximumLength();
	if ( maxLenght <= NO_TEXTFIELD_MAX_LENGHT) {
		return YES;
	}
	else {
		NSUInteger newLength = [textField.text length] + [string length] - range.length;
		return (newLength > maxLenght) ? NO : YES;
	}

	
	
}

- (BOOL)textFieldShouldReturn:(UITextField*)texField
{
	RBTextfield * aTextfield = (RBTextfield*)texField;
	RedBox::TextField * abstractTextField = [aTextfield getAbstractTextField];
	
	if([texField.text length] >= abstractTextField->getMimimumLength()){
		[texField resignFirstResponder];
		return YES;
	}
	else {
		return NO;
	}	
}
@end
