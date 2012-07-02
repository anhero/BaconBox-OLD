#include "BaconBox/Audio/OpenAL/WavHeader.h"

namespace BaconBox {
	std::ostream &operator<<(std::ostream &output, const WavHeader &wh) {
		output << "{";
		output << "\"chunkId\" : " << wh.chunkId << ", ";
		output << "\"chunkSize\" : " << wh.chunkSize << ", ";
		output << "\"format\" : " << wh.format << ", ";
		output << "\"subchunk1Id\" : " << wh.subchunk1Id << ", ";
		output << "\"subchunk1Size\" : " << wh.subchunk1Size << ", ";
		output << "\"audioFormat\" : " << wh.audioFormat << ", ";
		output << "\"nbChannels\" : " << wh.nbChannels << ", ";
		output << "\"sampleRate\" : " << wh.sampleRate << ", ";
		output << "\"byteRate\" : " << wh.byteRate << ", ";
		output << "\"blockAlign\" : " << wh.blockAlign << ", ";
		output << "\"bitsPerSample\" : " << wh.bitsPerSample << ", ";
		output << "\"subchunk2Id\" : " << wh.subchunk2Id << ", ";
		output << "\"subchunk2Size\" : " << wh.subchunk2Size;
		output << "}";
		return output;
	}
}
