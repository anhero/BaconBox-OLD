LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE := RedBoxApp


LOCAL_SRC_FILES := \
	RedBoxNativeActivity.cpp \
	PlayState.cpp

LOCAL_C_INCLUDES := \
	Loader.h \
	PlayState.h \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/../../libraries/current/include/


LOCAL_STATIC_LIBRARIES := RedBox
#	LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/libraries/current/lib) \
                 -lRedBox
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libraries/current/lib) \
                 -lGLESv1_CM -llog -lz \
                 -lpng 


include $(BUILD_SHARED_LIBRARY)

#subdirs := $(LOCAL_PATH)/../../Android.mk

#include $(subdirs)

include $(CLEAR_VARS)

LOCAL_PATH := $(LOCAL_PATH)/../..

# $(warning Value of LOCAL_PATH is '$(LOCAL_PATH)') 

LOCAL_MODULE := RedBox

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/RedBox/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Audio/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Display/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Display/Driver/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Emitter/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Helper/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Helper/libc/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Input/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Input/Accelerometer/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Input/GamePad/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Input/Keyboard/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/Input/Pointer/*.cpp) \
	$(wildcard $(LOCAL_PATH)/RedBox/RedBox/SignalSlots/*.cpp))


LOCAL_C_INCLUDES := $(LOCAL_PATH)/RedBox/ \
	$(LOCAL_PATH)/RedBox/RedBox/ \
	$(LOCAL_PATH)/RedBox/RedBox/Audio/ \
	$(LOCAL_PATH)/RedBox/RedBox/Display/ \
	$(LOCAL_PATH)/RedBox/RedBox/Display/Driver/ \
	$(LOCAL_PATH)/RedBox/RedBox/Emitter/ \
	$(LOCAL_PATH)/RedBox/RedBox/Helper/ \
	$(LOCAL_PATH)/RedBox/RedBox/Helper/libc \
	$(LOCAL_PATH)/RedBox/RedBox/Input/ \
	$(LOCAL_PATH)/RedBox/RedBox/Input/Accelerometer/ \
	$(LOCAL_PATH)/RedBox/RedBox/Input/GamePad/ \
	$(LOCAL_PATH)/RedBox/RedBox/Input/Keyboard/ \
	$(LOCAL_PATH)/RedBox/RedBox/Input/Pointer/ \
	$(LOCAL_PATH)/RedBox/RedBox/SignalSlots/ \
	$(LOCAL_PATH)/libraries/current/include/


LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/libraries/current/lib) \
                 -lGLESv1_CM -llog -lz \
                 -lpng 

include $(BUILD_STATIC_LIBRARY)

