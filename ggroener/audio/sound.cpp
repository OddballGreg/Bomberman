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

ALboolean enumeration;

enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
if (enumeration == AL_FALSE)
     fprintf(stdout, "enumeration not supported\n");// enumeration not supported
else
    fprintf(stdout, "enumeration supported\n"); // enumeration supported

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

alGetErrror(); // might have to remove this

ALCenum error;

error = alGetError();
if (error != AL_NO_ERROR)
{   
    fprintf(stdout, "Something went wrong with OpenAL\n");  // something wrong happened
    alutGetErrorString();
}

ALCcontext *context;

context = alcCreateContext(device, NULL);
if (!alcMakeContextCurrent(context))
{
    fprintf(stdout, "failed to make context current\n");
    alGetError();
            // // test for errors here using alGetError();
}

ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

alListener3f(AL_POSITION, 0, 0, 1.0f);
    alGetError();// check for errors
alListener3f(AL_VELOCITY, 0, 0, 0);
    alGetError();// check for errors
alListenerfv(AL_ORIENTATION, listenerOri);
    alGetError();// check for errors

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
    alGetError();// check for errros
