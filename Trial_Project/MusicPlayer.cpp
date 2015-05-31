#include "MusicPlayer.h"


MusicPlayer::MusicPlayer() :mMusic(), mFilename(), mVolume(100.f)
{ 
	mFilename[Music::MissionTheme] = "A:/Project/objection_orchestra.ogg";
}


MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::play(Music::ID theme)
{
	std::cout << "Inside play" << std::endl;
	std::string fileName = mFilename[theme];
	if (!mMusic.openFromFile(fileName))
	{
		throw std::runtime_error("Music " + fileName + " could not be loaded");
	}
	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}