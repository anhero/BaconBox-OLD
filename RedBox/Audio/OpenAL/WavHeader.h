/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_WAV_HEADER_H
#define RB_WAV_HEADER_H
namespace RedBox {
#pragma pack(1)
	/**
	 * Contains information about a .wav file.
	 * See https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
	 */
	struct WavHeader {
		uint32_t chunkId;
		uint32_t chunkSize;
		uint32_t format;
		uint32_t subchunk1Id;
		uint32_t subchunk1Size;
		uint16_t audioFormat;
		uint16_t nbChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
		uint32_t subchunk2Id;
		uint32_t subchunk2Size;
	};
}
#pragma pack()
#endif