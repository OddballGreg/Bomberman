/*
 * OpenAL example
 *
 * Copyright(C) Florian Fainelli <f.fainelli@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>

#include <al.h>
#include <alc.h>

#ifdef LIBAUDIO
#include <audio/wave.h>
#define BACKEND	"libaudio"
#else
#include <AL/alut.h>
#define BACKEND "alut"
#endif



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

#define TEST_ERROR(_msg)		\
	error = alGetError();		\
	if (error != AL_NO_ERROR) {	\
		fprintf(stderr, _msg "\n");	\
		return -1;		\
	}

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

//int main(int argc, char **argv)
//{
//	ALboolean enumeration;
//	const ALCchar *devices;
//	const ALCchar *defaultDeviceName = argv[1];
//    ALuint sndBuffer;
//	int ret;
//#ifdef LIBAUDIO
//	WaveInfo *wave;
//#endif
//	char *bufferData;
//	ALCdevice *device;
//	ALvoid *data;
//	ALCcontext *context;
//	ALsizei size, freq;
//	ALenum format;
//	ALuint buffer, source;
//	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
//	ALboolean loop = AL_FALSE;
//	ALCenum error;
//	ALint source_state;
//
//    fprintf(stdout, "Using " BACKEND " as audio backend\n"); //fprintf(stdout, "Using MINE as audio backend\n"); //fprintf(stdout, "Using " BACKEND " as audio backend\n");
//
//	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
//	if (enumeration == AL_FALSE)
//		fprintf(stderr, "enumeration extension not available\n");
//
//	list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
//
//	if (!defaultDeviceName)
//		defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
//
//	device = alcOpenDevice(defaultDeviceName);
//	if (!device) {
//		fprintf(stderr, "unable to open default device\n");
//		return -1;
//	}
//
//	fprintf(stdout, "Device: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));
//
//	alGetError();
//
//	context = alcCreateContext(device, NULL);
//	if (!alcMakeContextCurrent(context)) {
//		fprintf(stderr, "failed to make default context\n");
//		return -1;
//	}
//	TEST_ERROR("make default context");
//
//	/* set orientation */
//	alListener3f(AL_POSITION, 0, 0, 1.0f);
//	TEST_ERROR("listener position");
//    	alListener3f(AL_VELOCITY, 0, 0, 0);
//	TEST_ERROR("listener velocity");
//	alListenerfv(AL_ORIENTATION, listenerOri);
//	TEST_ERROR("listener orientation");
//
//	alGenSources((ALuint)1, &source);
//	TEST_ERROR("source generation");
//
//	alSourcef(source, AL_PITCH, 1);
//	TEST_ERROR("source pitch");
//	alSourcef(source, AL_GAIN, 1);
//	TEST_ERROR("source gain");
//	alSource3f(source, AL_POSITION, 0, 0, 0);
//	TEST_ERROR("source position");
//	alSource3f(source, AL_VELOCITY, 0, 0, 0);
//	TEST_ERROR("source velocity");
//	alSourcei(source, AL_LOOPING, AL_FALSE);
//	TEST_ERROR("source looping");
//
//	alGenBuffers(1, &buffer);
//	TEST_ERROR("buffer generation");
//
//#ifdef LIBAUDIO
//	/* load data */
//	wave = WaveOpenFileForReading("bounce.wav");//test.wav
//	if (!wave) {
//		fprintf(stderr, "failed to read wave file\n");
//		return -1;
//	}
//
//	ret = WaveSeekFile(0, wave);
//	if (ret) {
//		fprintf(stderr, "failed to seek wave file\n");
//		return -1;
//	}
//
//	bufferData = malloc(wave->dataSize);
//	if (!bufferData) {
//		perror("malloc");
//		return -1;
//	}
//
//	ret = WaveReadFile(bufferData, wave->dataSize, wave);
//	if (ret != wave->dataSize) {
//		fprintf(stderr, "short read: %d, want: %d\n", ret, wave->dataSize);
//		return -1;
//	}
//
//	alBufferData(buffer, to_al_format(wave->channels, wave->bitsPerSample),
//			bufferData, wave->dataSize, wave->sampleRate);
//	TEST_ERROR("failed to load buffer data");
//#else
//    sndBuffer = alutCreateBufferFromFile("./music/test.wav");
//    alutLoadMemoryFromFile ("../music/test.wav", &format, &size, (float*)&freq);
////	alutLoadWAVFile("./music/test.wav", &format, &data, &size, &freq, &loop); //test.wav bounce
//	TEST_ERROR("loading wav file");
//
//	alBufferData(buffer, format, data, size, freq);
//	TEST_ERROR("buffer copy");
//#endif
//
//	alSourcei(source, AL_BUFFER, buffer);
//	TEST_ERROR("buffer binding");
//
//	alSourcePlay(source);
//	TEST_ERROR("source playing");
//
//	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
//	TEST_ERROR("source state get");
//	while (source_state == AL_PLAYING) {
//		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
//		TEST_ERROR("source state get");
//	}
//
//	/* exit context */
//	alDeleteSources(1, &source);
//	alDeleteBuffers(1, &buffer);
//	device = alcGetContextsDevice(context);
//	alcMakeContextCurrent(NULL);
//	alcDestroyContext(context);
//	alcCloseDevice(device);
//
//	return 0;
//}



#include <iostream>
#include <fstream>
#include <cstring>
#include <al.h>
#include <alc.h>
#include <SDL/SDL.h>

bool isBigEndian()
{
    int a=1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer,int len)
{
    int a=0;
    if(!isBigEndian())
        for(int i=0;i<len;i++)
            ((char*)&a)[i]=buffer[i];
    else
        for(int i=0;i<len;i++)
            ((char*)&a)[3-i]=buffer[i];
    return a;
}

char* loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size)
{
char buffer[4];
std::ifstream in(fn,std::ios::binary);
in.read(buffer,4);
if(strncmp(buffer,"RIFF",4)!=0)
{
std::cout << "this is not a valid WAVE file"  << std::endl;
return NULL;
}
in.read(buffer,4);
in.read(buffer,4);      //WAVE
in.read(buffer,4);      //fmt
in.read(buffer,4);      //16
in.read(buffer,2);      //1
in.read(buffer,2);
chan=convertToInt(buffer,2);
in.read(buffer,4);
samplerate=convertToInt(buffer,4);
in.read(buffer,4);
in.read(buffer,2);
in.read(buffer,2);
bps=convertToInt(buffer,2);
in.read(buffer,4);      //data
in.read(buffer,4);
size=convertToInt(buffer,4);
char* data=new char[size];
in.read(data,size);
return data;
}

int main(int argc,char** argv)
{
    int channel,sampleRate,bps,size;
    char* data=loadWAV("test.wav",channel,sampleRate,bps,size);
    ALCdevice* device=alcOpenDevice(NULL);
    if(device==NULL)
    {
        std::cout << "cannot open sound card" << std::endl;
        return 0;
    }
    ALCcontext* context=alcCreateContext(device,NULL);
    if(context==NULL)
    {
        std::cout << "cannot open context" << std::endl;
        return 0;
    }
    alcMakeContextCurrent(context);

    unsigned int bufferid,format;
    alGenBuffers(1,&bufferid);
    if(channel==1)
    {
        if(bps==8)
        {
            format=AL_FORMAT_MONO8;
        }else{
            format=AL_FORMAT_MONO16;
        }
    }else{
        if(bps==8)
        {
            format=AL_FORMAT_STEREO8;
        }else{
            format=AL_FORMAT_STEREO16;
        }
    }
    alBufferData(bufferid,format,data,size,sampleRate);
    unsigned int sourceid;
    alGenSources(1,&sourceid);
    alSourcei(sourceid,AL_BUFFER,bufferid);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    SDL_Event event;
    Uint32 start;
    bool running;
    bool b[4]={0,0,0,0};
    float x=0,z=0;
    while(running)
    {
        start=SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running=false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            b[0]=true;
                            break;
                        case SDLK_RIGHT:
                            b[1]=true;
                            break;
                        case SDLK_DOWN:
                            b[2]=true;
                            break;
                        case SDLK_LEFT:
                            b[3]=true;
                            break;
                        case SDLK_SPACE:
                            alSourcePlay(sourceid);
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            b[0]=false;
                            break;
                        case SDLK_RIGHT:
                            b[1]=false;
                            break;
                        case SDLK_DOWN:
                            b[2]=false;
                            break;
                        case SDLK_LEFT:
                            b[3]=false;
                            break;
                    }
                    break;
            }
        }

        if(b[0])
            z+=0.3;
        if(b[1])
            x+=0.3;
        if(b[2])
            z-=0.3;
        if(b[3])
            x-=0.3;
        alSource3f(sourceid,AL_POSITION,x,0,z);
        alSourcei(sourceid,AL_LOOPING,AL_TRUE);


        float f[]={1,0,0,0,1,0};
        alListenerfv(AL_ORIENTATION,f);


        if(1000/30.0>SDL_GetTicks()-start)
            SDL_Delay(1000/30.0-(SDL_GetTicks()-start));
    }

    alDeleteSources(1,&sourceid);
    alDeleteBuffers(1,&bufferid);

    alcDestroyContext(context);
    alcCloseDevice(device);
    delete[] data;
    return 0;
}



