#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "KeyList.h"
#include <iostream>
#ifndef __MUSIC_PLAYER__
#define __MUSIC_PALYER__
class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();
	~MusicPlayer();
	void play(Music::ID);
	void stop();
	void setPaused(bool);
	void setVolume(float);

private:
	sf::Music mMusic;
	std::map<Music::ID, std::string> mFilename;
	float mVolume;
};
#endif