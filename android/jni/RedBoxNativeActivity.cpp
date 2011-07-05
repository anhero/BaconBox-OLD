//#include "RedBoxNativeActivity.h"
#include <RedBox.h>
#include <Loader.h>
#include <android/log.h>
#include <jni.h>
extern "C"
{
static JNIEnv* environment = NULL;

static jclass activityClass;

static jmethodID midCreateGLContext;
static jmethodID midFlipBuffers;

static float lastAccelerometer[3];


JNIEXPORT void JNICALL Java_net_anhero_RedBoxActivity_nativeInit(JNIEnv * JEnv, jclass cls){
 	environment = JEnv;
	activityClass = cls;

	midCreateGLContext = environment->GetStaticMethodID(activityClass,
                                "createGLContext","()V");
	
	midFlipBuffers = environment->GetStaticMethodID(activityClass,
                                "flipBuffers","()V");
	
	if(!midCreateGLContext || !midFlipBuffers ) {
        __android_log_print(ANDROID_LOG_WARN, "RedBox", "RedBox: Couldn't locate Java callbacks, check that they're named and typed correctly");
    }

	environment->CallStaticVoidMethod(activityClass, midCreateGLContext);
//	RedBox::Engine::initializeEngine(320,480);
	RedBox::Loader::load();
	while(true){
		RedBox::Engine::pulse();
		if(!RedBox::Engine::isBufferSwapped()) {
			environment->CallStaticVoidMethod(activityClass, midFlipBuffers);
			RedBox::Engine::setBufferSwapped();

		}
 	}
}

JNIEXPORT void JNICALL Java_net_anhero_RedBoxActivity_onNativeTouch
  (JNIEnv * JEnv, jclass cls, jint action, jfloat x, jfloat y, jfloat p){

  }


JNIEXPORT void JNICALL Java_net_anhero_RedBoxActivity_onNativeAccel
  (JNIEnv * JEnv, jclass cls, jfloat x, jfloat y, jfloat z){
	lastAccelerometer[0] = x;
    lastAccelerometer[1] = y;
    lastAccelerometer[2] = z;
  }


JNIEXPORT void JNICALL Java_net_anhero_RedBoxActivity_onNativeKeyDown
  (JNIEnv * JEnv, jclass cls, jint keycode){


  }


JNIEXPORT void JNICALL Java_net_anhero_RedBoxActivity_onNativeKeyUp
  (JNIEnv * JEnv, jclass cls, jint keycode){
	}

  }
