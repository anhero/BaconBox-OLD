//#include "BaconBoxNativeActivity.h"
#include <BaconBox.h>
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


JNIEXPORT void JNICALL Java_net_anhero_BaconBoxActivity_nativeInit(JNIEnv * JEnv, jclass cls){
 	environment = JEnv;
	activityClass = cls;

	midCreateGLContext = environment->GetStaticMethodID(activityClass,
                                "createGLContext","()V");
	
	midFlipBuffers = environment->GetStaticMethodID(activityClass,
                                "flipBuffers","()V");
	
	if(!midCreateGLContext || !midFlipBuffers ) {
        __android_log_print(ANDROID_LOG_WARN, "BaconBox", "BaconBox: Couldn't locate Java callbacks, check that they're named and typed correctly");
    }

	environment->CallStaticVoidMethod(activityClass, midCreateGLContext);
//	BaconBox::Engine::initializeEngine(320,480);
	BaconBox::Loader::load();
	while(true){
		BaconBox::Engine::pulse();
		if(!BaconBox::Engine::isBufferSwapped()) {
			environment->CallStaticVoidMethod(activityClass, midFlipBuffers);
			BaconBox::Engine::setBufferSwapped();

		}
 	}
}

JNIEXPORT void JNICALL Java_net_anhero_BaconBoxActivity_onNativeTouch
  (JNIEnv * JEnv, jclass cls, jint action, jfloat x, jfloat y, jfloat p){

  }


JNIEXPORT void JNICALL Java_net_anhero_BaconBoxActivity_onNativeAccel
  (JNIEnv * JEnv, jclass cls, jfloat x, jfloat y, jfloat z){
	lastAccelerometer[0] = x;
    lastAccelerometer[1] = y;
    lastAccelerometer[2] = z;
  }


JNIEXPORT void JNICALL Java_net_anhero_BaconBoxActivity_onNativeKeyDown
  (JNIEnv * JEnv, jclass cls, jint keycode){


  }


JNIEXPORT void JNICALL Java_net_anhero_BaconBoxActivity_onNativeKeyUp
  (JNIEnv * JEnv, jclass cls, jint keycode){
	}

  }
