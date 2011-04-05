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

INCLUDEPATH += ../../../RedBox \
	../../../RedBox/RedBox \
	../../../RedBox/RedBox/Audio \
	../../../RedBox/RedBox/Audio/OpenAL \
	../../../RedBox/RedBox/Display \
	../../../RedBox/RedBox/Display/Driver \
	../../../RedBox/RedBox/Display/Text \
	../../../RedBox/RedBox/Emitter \
	../../../RedBox/RedBox/Input \
	../../../RedBox/RedBox/Input/Accelerometer \
	../../../RedBox/RedBox/Input/GamePad \
	../../../RedBox/RedBox/Input/Keyboard \
	../../../RedBox/RedBox/Input/Keyboard/Qt \
	../../../RedBox/RedBox/Input/Pointer \
	../../../RedBox/RedBox/Physic \
	../../../RedBox/RedBox/Helper \
	../../../RedBox/RedBox/SignalSlots \


SOURCES += QtRedbox.cpp \
	../../../RedBox/RedBox/*.cpp \
	../../../RedBox/RedBox/Audio/*.cpp \
	../../../RedBox/RedBox/Audio/OpenAL/*.cpp \
	../../../RedBox/RedBox/Display/*.cpp \
	../../../RedBox/RedBox/Display/Driver/*.cpp \
	../../../RedBox/RedBox/Display/Text/*.cpp \
	../../../RedBox/RedBox/Emitter/*.cpp \
	../../../RedBox/RedBox/Input/*.cpp \
	../../../RedBox/RedBox/Input/Accelerometer/*.cpp \
	../../../RedBox/RedBox/Input/GamePad/*.cpp \
	../../../RedBox/RedBox/Input/Keyboard/*.cpp \
	../../../RedBox/RedBox/Input/Keyboard/Qt/*.cpp \
	../../../RedBox/RedBox/Input/Pointer/*.cpp \
	../../../RedBox/RedBox/Physic/*.cpp \
	../../../RedBox/RedBox/Helper/*.cpp \
	../../../RedBox/RedBox/SignalSlots/*.cpp \

HEADERS += QtRedbox.h \
	../../../RedBox/RedBox/*.h \
	../../../RedBox/RedBox/Audio/*.h \
	../../../RedBox/RedBox/Audio/OpenAL/*.h \
	../../../RedBox/RedBox/Display/*.h \
	../../../RedBox/RedBox/Display/Driver/*.h \
	../../../RedBox/RedBox/Display/Text/*.h \
	../../../RedBox/RedBox/Emitter/*.h \
	../../../RedBox/RedBox/Input/*.h \
	../../../RedBox/RedBox/Input/Accelerometer/*.h \
	../../../RedBox/RedBox/Input/GamePad/*.h \
	../../../RedBox/RedBox/Input/Keyboard/*.h \
	../../../RedBox/RedBox/Input/Keyboard/Qt/*.h \
	../../../RedBox/RedBox/Input/Pointer/*.h \
	../../../RedBox/RedBox/Physic/*.h \
	../../../RedBox/RedBox/Helper/*.h \
	../../../RedBox/RedBox/SignalSlots/*.h \

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/local/lib
	}
	INSTALLS += target
}

macx {
INCLUDEPATH += $$PWD/../../../libraries/ios/i386/include
DEPENDPATH += $$PWD/../../../libraries/ios/i386/include

LIBS += -L$$PWD/../../../libraries/ios/i386/lib/ -lpng15

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/i386/lib/libpng.a


LIBS += -L$$PWD/../../../libraries/ios/i386/lib/ -lfreetype

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/i386/lib/libfreetype.a

LIBS += -L$$PWD/../../../libraries/ios/i386/lib/ -lvorbisidec

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/i386/lib/libvorbisidec.a

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
