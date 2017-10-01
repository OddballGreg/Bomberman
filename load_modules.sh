if [ ! -d external ]; then \
	git clone git@github.com:Kalilo/bomberman_external.git; \
	mv bomberman_external external; \
fi

if [ ! -d resources ]; then \
	git clone git@github.com:Kalilo/bomberman_resources.git; \
	mv bomberman_resources resources; \
fi

if [ ! -d SoundEngine/music ]; then \
	git clone git@github.com:Kalilo/bomberman_music.git; \
	mv bomberman_music SoundEngine/music; \
fi

if [ ! -d gameEngine/resources ]; then \
	git clone git@github.com:Kalilo/bomberman_gameengine_resources.git; \
	mv bomberman_gameengine_resources gameEngine/resources; \
fi