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
	../../../RedBox/Audio \
	../../../RedBox/Audio/OpenAL \
	../../../RedBox/Display \
	../../../RedBox/Display/Camera \
	../../../RedBox/Display/GraphicDrivers \
	../../../RedBox/Display/Emitter \
	../../../RedBox/Display/Interface/Text \
	../../../RedBox/other \
	../../../RedBox/Helper \
	../../../RedBox/StatesSystem


SOURCES += QtRedbox.cpp \
	../../../RedBox/Audio/*.cpp \
	../../../RedBox/Audio/OpenAL/*.cpp \
	../../../RedBox/Display/*.cpp \
	../../../RedBox/Display/Camera/*.cpp \
	../../../RedBox/Display/Emitter/*.cpp \
	../../../RedBox/Display/GraphicDrivers/*.cpp \
	../../../RedBox/Display/Interface/Text/*.cpp \
	../../../RedBox/Helper/*.cpp \
	../../../RedBox/StatesSystem/*.cpp \
	../../../RedBox/other/*.cpp

HEADERS += QtRedbox.h \
	../../../RedBox/Audio/*.h \
	../../../RedBox/Audio/OpenAL/*.h \
	../../../RedBox/Display/*.h \
	../../../RedBox/Display/Camera/*.h \
	../../../RedBox/Display/Emitter/*.h \
	../../../RedBox/Display/GraphicDrivers/*.h \
	../../../RedBox/Display/Interface/Text/*.h \
	../../../RedBox/Helper/*.h \
	../../../RedBox/StatesSystem/*.h \
	../../../RedBox/other/*.h \
	../../../RedBox/*.h

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/local/lib
	}
	INSTALLS += target
}

macx {
INCLUDEPATH += $$PWD/../../../libraries/ios/universal/include
DEPENDPATH += $$PWD/../../../libraries/ios/universal/include

LIBS += -L$$PWD/../../../libraries/ios/universal/lib/ -lpng15

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/universal/lib/libpng15.a


LIBS += -L$$PWD/../../../libraries/ios/universal/lib/ -lfreetype

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/universal/lib/libfreetype.a

LIBS += -L$$PWD/../../../libraries/ios/universal/lib/ -lvorbisidec

PRE_TARGETDEPS += $$PWD/../../../libraries/ios/universal/lib/libvorbisidec.a

LIBS += -framework OpenAL

LIBS += -lz
}

