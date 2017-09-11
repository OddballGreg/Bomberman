//Device opening
//
#include <al.h>
#include <alc.h>
#include "SoundEngine.hpp"

int main(int argc,char** argv)
{
    Sound music;
    music.initialize("music/loop.wav");
    music.play(0, true);
    while (1)
    {
    }
    return(0);
}