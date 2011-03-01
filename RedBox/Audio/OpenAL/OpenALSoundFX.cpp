#include "OpenALSoundFX.h"

using namespace RedBox;

void OpenALSoundFX::play(int nbTimes) {
}

OpenALSoundFX::OpenALSoundFX(): SoundFX(), state(0), bufferId(0), sourceId(0),
format(0), freq(0) {
}

OpenALSoundFX::~OpenALSoundFX() {
}