#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T15:40:11
#
#-------------------------------------------------

QT       += opengl core gui


TARGET = RedBox
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

INCLUDEPATH += ../../../RedBox \
        $$PWD/../../RedBox/RedBox \
        $$PWD/../../RedBox/RedBox/Audio \
        $$PWD/../../RedBox/RedBox/Audio/OpenAL \
        $$PWD/../../RedBox/RedBox/Display \
        $$PWD/../../RedBox/RedBox/Display/Driver \
        $$PWD/../../RedBox/RedBox/Display/Text \
        $$PWD/../../RedBox/RedBox/Emitter \
        $$PWD/../../RedBox/RedBox/Input \
        $$PWD/../../RedBox/RedBox/Input/Accelerometer \
        $$PWD/../../RedBox/RedBox/Input/GamePad \
        $$PWD/../../RedBox/RedBox/Input/Keyboard \
        $$PWD/../../RedBox/RedBox/Input/Keyboard/Qt \
        $$PWD/../../RedBox/RedBox/Input/Pointer \
        $$PWD/../../RedBox/RedBox/Physic \
        $$PWD/../../RedBox/RedBox/Helper \
        $$PWD/../../RedBox/RedBox/SignalSlots \


SOURCES += QtRedbox.cpp \
        $$PWD/../../RedBox/RedBox/*.cpp \
        $$PWD/../../RedBox/RedBox/Audio/*.cpp \
        $$PWD/../../RedBox/RedBox/Audio/OpenAL/*.cpp \
        $$PWD/../../RedBox/RedBox/Display/*.cpp \
        $$PWD/../../RedBox/RedBox/Display/Driver/*.cpp \
        $$PWD/../../RedBox/RedBox/Display/Text/*.cpp \
        $$PWD/../../RedBox/RedBox/Emitter/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/Accelerometer/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/GamePad/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/Keyboard/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/Keyboard/Qt/*.cpp \
        $$PWD/../../RedBox/RedBox/Input/Pointer/*.cpp \
        $$PWD/../../RedBox/RedBox/Physic/*.cpp \
        $$PWD/../../RedBox/RedBox/Helper/*.cpp \
        $$PWD/../../RedBox/RedBox/SignalSlots/*.cpp \

HEADERS += QtRedbox.h \
        $$PWD/../../RedBox/RedBox/*.h \
        $$PWD/../../RedBox/RedBox/Audio/*.h \
        $$PWD/../../RedBox/RedBox/Audio/OpenAL/*.h \
        $$PWD/../../RedBox/RedBox/Display/*.h \
        $$PWD/../../RedBox/RedBox/Display/Driver/*.h \
        $$PWD/../../RedBox/RedBox/Display/Text/*.h \
        $$PWD/../../RedBox/RedBox/Emitter/*.h \
        $$PWD/../../RedBox/RedBox/Input/*.h \
        $$PWD/../../RedBox/RedBox/Input/Accelerometer/*.h \
        $$PWD/../../RedBox/RedBox/Input/GamePad/*.h \
        $$PWD/../../RedBox/RedBox/Input/Keyboard/*.h \
        $$PWD/../../RedBox/RedBox/Input/Keyboard/Qt/*.h \
        $$PWD/../../RedBox/RedBox/Input/Pointer/*.h \
        $$PWD/../../RedBox/RedBox/Physic/*.h \
        $$PWD/../../RedBox/RedBox/Helper/*.h \
        $$PWD/../../RedBox/RedBox/SignalSlots/*.h \

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
