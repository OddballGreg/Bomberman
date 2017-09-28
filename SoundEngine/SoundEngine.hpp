#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <pthread.h>
#include <al.h>
#include <alc.h>

class Sound {

public:
	Sound();
	Sound(const char *File);
	~Sound();

	void	initialize(const char* File);
	char*	loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size);
	void	play(bool loop);

	void	incVolume(void);
	void	decVolume(void);
	void	setVolume(float percentage);

private:
	unsigned int	_buffer;
	unsigned int	_source;
	bool			_loop = true;
	pthread_t		_thread[5];
	float			_volume = 1.0f;

	int				_rc;
	void			*_status;
};



