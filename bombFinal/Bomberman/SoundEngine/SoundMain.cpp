//Device opening
//
#include <al.h>
#include <alc.h>
#include "SoundEngine.hpp"

int main(int argc,char** argv)
{
    Sound musicloop;
    musicloop.initialize("music/loop.wav");
    musicloop.play(0, true);
    Sound musicbounce;
    musicbounce.initialize("music/bounce.wav");
    musicbounce.play(0, false);
    while (1)
    {
    }
    return(0);
}