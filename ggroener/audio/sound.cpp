//Device opening
//
#include <AL/al.h>
#include <AL/alc.h>
...
ALCdevice *device;

device = alcOpenDevice(NULL);
if (!device) // handle errors
{
    //out put error message
    fprintf(stdout, "Unable to open handle to a Devices\n");
}


//Device enumeration
//
ALboolean enumeration;

enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
if (enumeration == AL_FALSE)
    fprintf(stdout, "enumeration not supported\n");// enumeration not supported
else
    fprintf(stdout, "enumeration supported\n"); // enumeration supported


//Retrieving the device list
//
static void list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));


//Error stack initialisation and usage
//
alGetError(); // might have to remove this

ALCenum error;

error = alGetError();
if (error != AL_NO_ERROR)
{   
    fprintf(stdout, "Something went wrong with OpenAL\n");  // something wrong happened
    alutGetErrorString();
}


//Context creation and initialization
//
ALCcontext *context;

context = alcCreateContext(device, NULL);
if (!alcMakeContextCurrent(context))
{
    fprintf(stdout, "failed to make context current\n");
    alGetError();
    // // test for errors here using alGetError();
}


//Definining and configuring the listener
//
ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

alListener3f(AL_POSITION, 0, 0, 1.0f);
alGetError();// check for errors
alListener3f(AL_VELOCITY, 0, 0, 0);
alGetError();// check for errors
alListenerfv(AL_ORIENTATION, listenerOri);
alGetError();// check for errors


//Source generation
//
ALuint source;

alGenSources((ALuint)1, &source);
alGetError();// check for errors

alSourcef(source, AL_PITCH, 1);
alGetError(); // check for errors
alSourcef(source, AL_GAIN, 1);
alGetError();// check for errors
alSource3f(source, AL_POSITION, 0, 0, 0);
alGetError();// check for errors
alSource3f(source, AL_VELOCITY, 0, 0, 0);
alGetError();// check for errors
alSourcei(source, AL_LOOPING, AL_FALSE);
alGetError();// check for errors


//Buffer generation
//
ALuint buffer;

alGenBuffers((ALuint)1, &buffer);
alGetError(); // check for errors


//Loading an audio stream to a buffer
//

//This is the easy way but it is deprecated.   
ALsizei size, freq;
ALenum format;
ALvoid *data;
ALboolean loop = AL_FALSE;

alutLoadWAVFile("bounce.wav", &format, &data, &size, &freq, &loop);
alGetError();// check for errors

// Here is the hard way!
WaveInfo *wave;
char *bufferData;
int ret;

wave = WaveOpenFileForReading("bounce.wav");
if (!wave) {
    fprintf(stderr, "failed to read wave file\n");
    return -1;
}

ret = WaveSeekFile(0, wave);
if (ret) {
    fprintf(stderr, "failed to seek wave file\n");
    return -1;
}

bufferData = malloc(wave->dataSize);
if (!bufferData) {
    perror("malloc, Failed to malloc the buffer for the data");
    return -1;
}

ret = WaveReadFile(bufferData, wave->dataSize, wave);
if (ret != wave->dataSize) {
    fprintf(stderr, "short read: %d, want: %d\n", ret, wave->dataSize);
    return -1;
}

alBufferData(buffer, format, data, size, freq);
alGetError();// check for errors


// how to do it in libaudio
static inline ALenum to_al_format(short channels, short samples)
{
    bool stereo = (channels > 1);

    switch (samples) {
        case 16:
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        case 8:
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        default:
            return -1;
    }
}

alBufferData(buffer, to_al_format(wave->channels, wave->bitsPerSample),
        bufferData, wave->dataSize, wave->sampleRate);
alGetError();// check for errors


//Binding a source to a buffer
//
alSourcei(source, AL_BUFFER, buffer);
alGetError();// check for errors


//Playing the source
//
alSourcePlay(source);

// cleanup context
alDeleteSources(1, &source);
alDeleteBuffers(1, &buffer);
device = alcGetContextsDevice(context);
alcMakeContextCurrent(NULL);
alcDestroyContext(context);
alcCloseDevice(device);

alSourcePlay(source);
// check for errors

alGetSourcei(source, AL_SOURCE_STATE, &source_state);
alGetError();// check for errors
while (source_state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
               alGetError();// check for errors
}


//Cleaning up context and resources
//
//This will free everything for us
alDeleteSources(1, &source);
alDeleteBuffers(1, &buffer);
device = alcGetContextsDevice(context);
alcMakeContextCurrent(NULL);
alcDestroyContext(context);
alcCloseDevice(device);
