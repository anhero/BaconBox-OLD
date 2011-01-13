#import "RBTextfield.h"


@implementation RBTextfield


- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
    }
    return self;
}

- (int)getMaxLenght{
	return abstractTextField->getMaximumLength();
}
- (void) setAbstractTextField:(RedBox::TextField *)aTextField{
	abstractTextField = aTextField;
}


- (RedBox::TextField*) getAbstractTextField{
	return abstractTextField;
}

- (void)dealloc {
    [super dealloc];
}
@end
