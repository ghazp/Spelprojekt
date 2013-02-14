#pragma once

#include "DataStructures.h"
#include <string>
using namespace std;

void clearSoundEngine();

int createSoundHandle(string _filename, bool _music, bool _3d, FLOAT3 _pos, float _volume = 1.0f);

void deactivateSound(int _handle);

void initSoundEngine();

bool isSoundPlaying(int _handle);

void loopSound(int _handle);

void playSound(int _handle);

void setMusicVolume(float _value);

void setSoundVolume(float _value);

void setSoundVolume(int _handle, float _volume);

void stopSound(int _handle);

void deleteSoundEngine();

void updateSoundEngine(const FLOAT3& _listenerPos);