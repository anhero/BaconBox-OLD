#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T15:40:11
#
#-------------------------------------------------

QT       += opengl core gui


TARGET = BaconBox
TEMPLATE = lib
CONFIG += staticlib

CONFIG -= x86_64
CONFIG += x86

DEFINES += QT
DEFINES += _DEBUG

DESTDIR = $$PWD/../../build/lib



#MOC_DIR = $$PWD/../../build
#OBJECTS_DIR = $$PWD/../../build
#RCC_DIR = $$PWD/../../build
#UI_DIR =  $$PWD/../../build

INCLUDEPATH += ../../../BaconBox \
        $$PWD/../../BaconBox/BaconBox \
        $$PWD/../../BaconBox/BaconBox/Audio \
        $$PWD/../../BaconBox/BaconBox/Audio/OpenAL \
        $$PWD/../../BaconBox/BaconBox/Display \
        $$PWD/../../BaconBox/BaconBox/Display/Driver \
        $$PWD/../../BaconBox/BaconBox/Display/Text \
        $$PWD/../../BaconBox/BaconBox/Emitter \
        $$PWD/../../BaconBox/BaconBox/Input \
        $$PWD/../../BaconBox/BaconBox/Input/Accelerometer \
        $$PWD/../../BaconBox/BaconBox/Input/GamePad \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard/Qt \
        $$PWD/../../BaconBox/BaconBox/Input/Pointer \
		$$PWD/../../BaconBox/BaconBox/Input/Pointer/Qt \
		$$PWD/../../BaconBox/BaconBox/Physic \
        $$PWD/../../BaconBox/BaconBox/Helper \
        $$PWD/../../BaconBox/BaconBox/SignalSlots \


SOURCES += QtBaconBox.cpp \
        $$PWD/../../BaconBox/BaconBox/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Audio/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Audio/OpenAL/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Display/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Display/Driver/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Display/Text/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Emitter/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/Accelerometer/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/GamePad/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard/Qt/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Input/Pointer/*.cpp \
		$$PWD/../../BaconBox/BaconBox/Input/Pointer/Qt/*.cpp \
		$$PWD/../../BaconBox/BaconBox/Physic/*.cpp \
        $$PWD/../../BaconBox/BaconBox/Helper/*.cpp \
        $$PWD/../../BaconBox/BaconBox/SignalSlots/*.cpp \

HEADERS += QtBaconBox.h \
        $$PWD/../../BaconBox/BaconBox/*.h \
        $$PWD/../../BaconBox/BaconBox/Audio/*.h \
        $$PWD/../../BaconBox/BaconBox/Audio/OpenAL/*.h \
        $$PWD/../../BaconBox/BaconBox/Display/*.h \
        $$PWD/../../BaconBox/BaconBox/Display/Driver/*.h \
        $$PWD/../../BaconBox/BaconBox/Display/Text/*.h \
        $$PWD/../../BaconBox/BaconBox/Emitter/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/Accelerometer/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/GamePad/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/Keyboard/Qt/*.h \
        $$PWD/../../BaconBox/BaconBox/Input/Pointer/*.h \
		$$PWD/../../BaconBox/BaconBox/Input/Pointer/Qt/*.h \
		$$PWD/../../BaconBox/BaconBox/Physic/*.h \
        $$PWD/../../BaconBox/BaconBox/Helper/*.h \
        $$PWD/../../BaconBox/BaconBox/SignalSlots/*.h \

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/local/lib
	}
	INSTALLS += target
}

macx {
INCLUDEPATH += $$PWD/../../libraries/ios/i386/include
DEPENDPATH += $$PWD/../../libraries/ios/i386/include

LIBS += -L$$PWD/../../libraries/ios/i386/lib/ -lpng15

PRE_TARGETDEPS += $$PWD/../../libraries/ios/i386/lib/libpng.a


LIBS += -L$$PWD/../../libraries/ios/i386/lib/ -lfreetype

PRE_TARGETDEPS += $$PWD/../../libraries/ios/i386/lib/libfreetype.a

LIBS += -L$$PWD/../../libraries/ios/i386/lib/ -lvorbisidec

PRE_TARGETDEPS += $$PWD/../../libraries/ios/i386/lib/libvorbisidec.a

LIBS += -framework OpenAL

LIBS += -lz
}

win32 {

win32:CONFIG(release, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -lzlib
else:win32:CONFIG(debug, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -lzlib

INCLUDEPATH += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/include"
DEPENDPATH += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/include"
INCLUDEPATH += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/include/freetype2"
DEPENDPATH += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/include/freetype2"

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/zlib.lib"
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/zlib.lib"

win32:CONFIG(release, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -llibpng
else:win32:CONFIG(debug, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -llibpng

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/libpng.lib"
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/libpng.lib"

win32:CONFIG(release, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -lfreetype
else:win32:CONFIG(debug, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/" -lfreetype

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/freetype.lib"
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/GnuWin32/lib/freetype.lib"

win32:CONFIG(release, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/libs/Win32/" -lOpenAL32
else:win32:CONFIG(debug, debug|release): LIBS += -L"$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/libs/Win32/" -lOpenAL32

INCLUDEPATH += "$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/include"
DEPENDPATH += "$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/include"

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/libs/Win32/OpenAL32.lib"
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += "$$PWD/../../../../../../../../../../Program Files/OpenAL 1.1 SDK/libs/Win32/OpenAL32.lib"

}
