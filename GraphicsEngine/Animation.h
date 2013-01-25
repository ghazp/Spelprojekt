#pragma once

#include <vector>
#include "FishStructs.h"
#include "TexturePack.h"
#include "stdafx.h"
#include <map>

using namespace std;


class Animation
{
private:
	map<string, AnimationFile> animations;
	TexturePack texPack;
	float time;
	int currentKey;
	float nextKey;
	void UpdateSkeletonTexture(vector<D3DXMATRIX>* mat);
	string currentAnimation;
	string pendingAnimation;
	void RandomAnimationFunc(float dt);
	void FFloat3ToD3DXVECTOR3(D3DXVECTOR3 &out, FFloat3 &in);
	void FFloat4ToD3DXQUATERNION(D3DXQUATERNION &out, FFloat4 &in);
	
public:
	Animation();
	~Animation();
	void addAnimation(string name, AnimationFile animationFile);
	int getNumAnimations();
	void Update(float dt);
	void setTexturePack(TexturePack* _texPack);
	ID3D10ShaderResourceView* getResource();
};