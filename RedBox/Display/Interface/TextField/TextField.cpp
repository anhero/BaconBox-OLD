#include "TextField.h"
#import "RBTextFieldDelegate.h"
using namespace RedBox;

TextField::TextField(State * aState){
#ifdef RB_IPHONE_PLATFORM
	CGRect aCGRect = CGRectMake(0, 0, 0, 0);
	iphoneTextField  = [[RBTextfield alloc] initWithFrame:aCGRect];
	[iphoneTextField setAbstractTextField:this];
	initialized = false;
	iphoneTextField.delegate = [RBTextFieldDelegate getTextFieldDelegate];
#endif
	currentState = aState;
	minimumLength = 0;
	maximumLength = NO_TEXTFIELD_MAX_LENGHT;
}

void TextField::setMaximumLength(int lenght){
	maximumLength = lenght;
}

int TextField::getMaximumLength(){
	return maximumLength;
}

void TextField::setMinimumLength(int length){
	minimumLength = length;
}
int TextField::getMimimumLength(){
	return minimumLength;
}

void TextField::showTextField(){
#ifdef RB_IPHONE_PLATFORM
	UIApplication * appDelegate = [[UIApplication sharedApplication] delegate];
	EAGLView * glView = [appDelegate glView];
	[glView addSubview:iphoneTextField];

	if (!initialized) {
		IPhoneOrientationEnum orientation = currentState->getIphoneOrientation();
		
		if (orientation == landscapeLeft){
			iphoneTextField.transform = CGAffineTransformMakeRotation(-(M_PI / 2.0));
		} else if (orientation == landscapeRight) {
			iphoneTextField.transform = CGAffineTransformMakeRotation((M_PI / 2.0));
		} else if (orientation == portrait) {
			iphoneTextField.transform = CGAffineTransformMakeRotation(0.0);
		}
		initialized = true;
	}
	
#endif
}

void TextField::hideTextField(){
#ifdef RB_IPHONE_PLATFORM
	[iphoneTextField removeFromSuperview];	
#endif
}


void TextField::setPosition(int x, int y){
#ifdef RB_IPHONE_PLATFORM
	iphoneTextField.center = CGPointMake(x, y);
#endif
}

void TextField::setSize(int width, int height){
#ifdef RB_IPHONE_PLATFORM
	iphoneTextField.bounds = CGRectMake(0, 0, width, height);
#endif
}

void TextField::setDefault(){
#ifdef RB_IPHONE_PLATFORM
	[iphoneTextField setBorderStyle:UITextBorderStyleRoundedRect];
	[iphoneTextField setBackgroundColor:[UIColor clearColor]];
	[iphoneTextField setTextColor:[UIColor blackColor]];
	[iphoneTextField setClearButtonMode:UITextFieldViewModeAlways];
	[iphoneTextField setFont:[UIFont fontWithName:@"Arial" size:18.0f]];
	[iphoneTextField setTextAlignment:UITextAlignmentCenter];
	[iphoneTextField setReturnKeyType:UIReturnKeyDone];
#endif
}

TextField::~TextField(){
	[iphoneTextField dealloc];
}

void TextField::setText(const std::wstring& text){
#ifdef RB_IPHONE_PLATFORM
	char * data = (char*)text.data();
	unsigned size = text.size() * sizeof(wchar_t);
#if TARGET_RT_BIG_ENDIAN
	const NSStringEncoding encoding = NSUTF32BigEndianStringEncoding;
#else
	const NSStringEncoding encoding = NSUTF32LittleEndianStringEncoding;
#endif
	[iphoneTextField setText:[[NSString alloc] initWithBytes:data length:size encoding:encoding]];
	
#endif
}


void TextField::setText(const std::string& text){
	setText(Convert::stringToWstring(text));
}


std::wstring TextField::getText(){
#ifdef RB_IPHONE_PLATFORM

#if TARGET_RT_BIG_ENDIAN
	NSStringEncoding encoding = NSUTF32BigEndianStringEncoding;
#else
	NSStringEncoding encoding = NSUTF32LittleEndianStringEncoding;
#endif
	NSData * asData = [[iphoneTextField text] dataUsingEncoding:encoding];
	return std::wstring((wchar_t*)[asData bytes], [asData length] / sizeof(wchar_t));
#endif

}
