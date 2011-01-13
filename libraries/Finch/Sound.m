#import "Sound.h"
#import <AudioToolbox/AudioToolbox.h> 

#define CLEAR_ERROR_FLAG alGetError()
#define DETACH_SOURCE 0

struct ReadInfo
{
    BOOL success;
    ALsizei bytesRead;
    ALsizei sampleRate;
    ALenum dataFormat;
    ALvoid *data;
};
typedef struct ReadInfo ReadInfo;

@implementation Sound
@synthesize loop, length, gain;

// Clears the error flag.
- (BOOL) checkSuccessOrLog: (NSString*) msg
{
    ALenum errcode;
    if ((errcode = alGetError()) != AL_NO_ERROR)
    {
        NSLog(@"%@, error code %x.", msg, errcode);
        return NO;
    }
    return YES;
}

#pragma mark Designated Initializer

- (id) initWithData: (ALvoid*) data length: (ALsizei) size
    format: (ALenum) format sampleRate: (ALsizei) frequency 
{
    [super init];
    
    ALCcontext *const currentContext = alcGetCurrentContext();
    if (currentContext == NULL)
    {
        NSLog(@"OpenAL context not set, did you initialize Finch?");
        return nil;
    }
    
    // Allocate buffer.
    CLEAR_ERROR_FLAG;
    alGenBuffers(1, &buffer);
    if (![self checkSuccessOrLog:@"Failed to allocate OpenAL buffer"])
        return nil;

    // Pass sound data to OpenAL.
    CLEAR_ERROR_FLAG;
    alBufferData(buffer, format, data, size, frequency);
    if (![self checkSuccessOrLog:@"Failed to fill OpenAL buffers"])
        return nil;
    
    // Initialize the source.
    CLEAR_ERROR_FLAG;
    alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
    if (![self checkSuccessOrLog:@"Failed to create OpenAL source"])
        return nil;

    gain = 1;
    return self;
}

- (void) dealloc
{
    [self stop];
    CLEAR_ERROR_FLAG;
    alSourcei(source, AL_BUFFER, DETACH_SOURCE);
    alDeleteBuffers(1, &buffer), buffer = 0;
    alDeleteSources(1, &source), source = 0;
    [self checkSuccessOrLog:@"Failed to clean up after sound"];
    [super dealloc];
}

#pragma mark Playback Controls

- (void) setGain: (float) val
{
    gain = val;
    alSourcef(source, AL_GAIN, gain);
}

- (BOOL) playing
{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

- (void) setLoop: (BOOL) yn
{
    loop = yn;
    alSourcei(source, AL_LOOPING, yn);
}

- (void) play
{
    if (self.playing)
        [self stop];
    CLEAR_ERROR_FLAG;
    alSourcePlay(source);
    [self checkSuccessOrLog:@"Failed to start sound"];
}

- (void) stop
{
    if (!self.playing)
        return;
    CLEAR_ERROR_FLAG;
    alSourceStop(source);
    [self checkSuccessOrLog:@"Failed to stop sound"];
}
- (ReadInfo) readPCMDataFrom: (NSURL*) path
{
    ReadInfo result = {NO};
	OSStatus errcode = noErr;
	UInt32 propertySize;
	AudioFileID fileId = 0;
	
	errcode = AudioFileOpenURL((CFURLRef) path, kAudioFileReadPermission, 0, &fileId);
	if (errcode)
	 {
		NSLog(@"Failed to read audio file (%x).", errcode);
	 }
	
	AudioStreamBasicDescription fileFormat;
    propertySize = sizeof(fileFormat);
	errcode = AudioFileGetProperty(fileId, kAudioFilePropertyDataFormat, &propertySize, &fileFormat);
	if (errcode)
	 {
		NSLog(@"Failed to read file format info (%x).", errcode);
		
	 }
	
	if (fileFormat.mChannelsPerFrame > 2)
	 { 
		 NSLog(@"More than two channels in sound file.");
		 
	 }
	
	if (fileFormat.mFormatID != kAudioFormatLinearPCM)
	 { 
		 NSLog(@"Sound file not linear PCM.");
		 
	 }
	
    if (!TestAudioFormatNativeEndian(fileFormat))
	 {
        NSLog(@"Sounds must be little-endian.");
	 }
	
	if ((fileFormat.mBitsPerChannel != 8) && (fileFormat.mBitsPerChannel != 16))
	 { 
		 NSLog(@"Only files with 8 or 16 bits per channel supported.");
		 
	 }
	
    UInt64 fileSize = 0;
    propertySize = sizeof(fileSize);
	errcode = AudioFileGetProperty(fileId, kAudioFilePropertyAudioDataByteCount, &propertySize, &fileSize);
	if (errcode)
	 {
		NSLog(@"Failed to read sound file size (%x).", errcode);
		
	 }
	
    propertySize = sizeof(length);
    errcode = AudioFileGetProperty(fileId, kAudioFilePropertyEstimatedDuration, &propertySize, &length);
    if (errcode)
        NSLog(@"Failed to read sound length: %x.", errcode);
	
	UInt32 dataSize = (UInt32) fileSize;
	result.data = malloc(dataSize);
	if (!result.data)
	 {
        NSLog(@"Failed to allocate memory for sound data.");
        
	 }
    
    errcode = AudioFileReadBytes(fileId, false, 0, &dataSize, result.data);
    if (errcode == noErr)
	 {
        result.success = YES;
        result.bytesRead = dataSize;
        result.dataFormat = (fileFormat.mChannelsPerFrame > 1) ?
		AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
        result.sampleRate = fileFormat.mSampleRate;
	 }
    else 
	 { 
		 NSLog(@"Failed to read sound data (%x).", errcode);
		 
	 }	
	
	
	if (fileId)
        AudioFileClose(fileId);
    if (!result.success && result.data)
        free(result.data), result.data = 0;
	return result;
}

- (id) initWithFile: (NSString*) path
{
    // Provide a friendly error message in case
    // the caller screwed up the file path.
    if (![[NSFileManager defaultManager] fileExistsAtPath:path])
	 {
        NSLog(@"Sound not found: %@.", path);
        return nil;
	 }
    
    ReadInfo info = [self readPCMDataFrom:[NSURL fileURLWithPath:path]];
    if (!info.success)
        return nil;
    return [self initWithData:info.data length:info.bytesRead
					   format:info.dataFormat sampleRate:info.sampleRate];
}

@end
