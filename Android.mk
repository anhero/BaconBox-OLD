LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE := BaconBox 



LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/BaconBox/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Audio/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Display/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Display/Driver/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Emitter/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Helper/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Helper/libc/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Input/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Input/Accelerometer/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Input/GamePad/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Input/Keyboard/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/Input/Pointer/*.cpp) \
	$(wildcard $(LOCAL_PATH)/BaconBox/BaconBox/SignalSlots/*.cpp))



LOCAL_C_INCLUDES := $(LOCAL_PATH)/BaconBox/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Audio/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Display/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Display/Driver/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Emitter/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Helper/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Helper/libc \
	$(LOCAL_PATH)/BaconBox/BaconBox/Input/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Input/Accelerometer/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Input/GamePad/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Input/Keyboard/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/Input/Pointer/ \
	$(LOCAL_PATH)/BaconBox/BaconBox/SignalSlots/ \
	$(LOCAL_PATH)/libraries/current/include/



LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/libraries/current/lib) \
                 -lGLESv1_CM -llog -lz \
                 -lpng 

include $(BUILD_SHARED_LIBRARY)

