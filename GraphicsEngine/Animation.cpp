#include "Animation.h"

Animation::Animation()
{
	this->currentKey = 0;
	this->texPack.texture = NULL;
	this->time = 0;
	this->currentAnimation = "walk";
	D3DXMatrixIdentity(&this->hatMatrix);
	D3DXMatrixIdentity(&this->rightHandMatrix);
	D3DXMatrixIdentity(&this->leftHandMatrix);
}

Animation::~Animation()
{

}

void Animation::addAnimation(string name, AnimationFile animationFile)
{
	this->animations.insert(animations.begin(), pair<string, AnimationFile>(name, animationFile));
}

int Animation::getNumAnimations()
{
	return this->animations.size();
}

void Animation::setTexturePack(TexturePack* _texPack)
{
	this->texPack = *_texPack;
}

D3DXMATRIX* Animation::getHatMatrix()
{
	return &this->hatMatrix; 
}

D3DXMATRIX* Animation::getRightHandMatrix()
{
	return &this->rightHandMatrix; 
}

D3DXMATRIX* Animation::getLeftHandMatrix()
{
	return &this->leftHandMatrix; 
}

void Animation::Update(float dt)
{
	RandomAnimationFunc(dt);
	
	//vector<D3DXMATRIX> matrices;
	//for(int a = 0; a < currentAnimations.size(); a++)
	//{
	//	vector<vector<FishAnimationStuff>> fishAnimationStuff;
	//}

	//splitfactor

	//for currentAnimations
		//

		//splitfactor += currentAnimation[i].blend%
	//

}

void Animation::UpdateCurrAnimations()
{
	//DoSTUFF

	vector<vector<FishAnimationStuff>> annatStuff;
	
	map<string, AnimationFile*>::iterator it;
	//vector<FishAnimationStuff> blend;
	int c = 0;
	
	float lerping = 0;

	for(it = currentAnimations.begin(); it != currentAnimations.end(); it++, c++)
	{
		lerping += it->second->animationWeight;
		float fps = 24;
		vector<D3DXMATRIX> matrices;
		
		float offset = this->animations[currentAnimation].skeletons[0].keys[0].time;
		int maxKeys = this->animations[currentAnimation].skeletons[0].keys.size() - 1;

		float currKeyTime =  this->animations[currentAnimation].skeletons[0].keys[currentKey].time;
		float nextKeyTime = this->animations[currentAnimation].skeletons[0].keys[currentKey+1].time;

		if(time >= (this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].skeletons[0].keys.size()-1].time-offset)/fps)
		{
			currentKey = 0;
			time = 0;
		}
		else
		{
			if(currentKey + 2 <= maxKeys)
			{
				if(time >= (nextKeyTime-offset)/fps)
				{
					currentKey++;
				}
			}
		}
		
		currKeyTime = this->animations[currentAnimation].skeletons[0].keys[currentKey].time;
		nextKeyTime = this->animations[currentAnimation].skeletons[0].keys[currentKey + 1].time;

		float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
		float timePass = time - (currKeyTime-offset)/fps;
		float lerpValue = timePass/timeInterval;


		vector<FishAnimationStuff> stuff;

		for(int k = 0; k < currentAnimations[it->first]->skeletons[0].keys.size(); k++)
		{
			for(int j = 0; j < currentAnimations[it->first]->skeletons[0].keys[k].numJoints; j++)
			{					
				stuff.push_back(ANewWierdFunction(it->second, 0, j, lerpValue));
			}
		}

		/*for(int b = 0; b < blend.size(); b++)
		{

		}*/
		annatStuff.push_back(stuff);
	}

	for(int j = 0; j < animations[0].skeletons[0].keys[0].numJoints; j++)
	{
		vector<FishAnimationStuff> blending;
		for(int o = 0; o < annatStuff.size(); o++)
		{
			blending.push_back(annatStuff[o][j]);
		}
		FishAnimationStuff joint;
		for(int b = 0; b < blending.size(); b++)
		{

			//blending[b].rotation *= currentAnimations.
		}
	}
}

FishAnimationStuff Animation::ANewWierdFunction(AnimationFile* animationFile, int skeletonIndex, int jointIndex, float lerpValue)
{
	FishAnimationStuff f;

	D3DXQUATERNION tempQuat1;
	FFloat4ToD3DXQUATERNION(tempQuat1, animationFile->skeletons[skeletonIndex].keys[currentKey].joints[jointIndex].rotation);
	D3DXQUATERNION tempQuat2;
	FFloat4ToD3DXQUATERNION(tempQuat2, animationFile->skeletons[skeletonIndex].keys[currentKey + 1].joints[jointIndex].rotation);
	D3DXVECTOR3 tempTrans1;
	FFloat3ToD3DXVECTOR3(tempTrans1, animationFile->skeletons[skeletonIndex].keys[currentKey].joints[jointIndex].translation);
	D3DXVECTOR3 tempTrans2;
	FFloat3ToD3DXVECTOR3(tempTrans2, animationFile->skeletons[skeletonIndex].keys[currentKey + 1].joints[jointIndex].translation);
	D3DXVECTOR3 tempScale1;
	FFloat3ToD3DXVECTOR3(tempScale1, animationFile->skeletons[skeletonIndex].keys[currentKey].joints[jointIndex].scale);
	D3DXVECTOR3 tempScale2;
	FFloat3ToD3DXVECTOR3(tempScale2, animationFile->skeletons[skeletonIndex].keys[currentKey + 1].joints[jointIndex].scale);


	D3DXQuaternionSlerp(&f.rotation, &tempQuat1, &tempQuat2, lerpValue);
	D3DXVec3Lerp(&f.scale, &tempScale1, &tempScale2, lerpValue);
	D3DXVec3Lerp(&f.translation, &tempTrans1, &tempTrans2, lerpValue);

	return f;
}

void Animation::RandomAnimationFunc(float dt)
{
	if(getNumAnimations() > 0 && this->texPack.texture != NULL)
	{
		for(int s = 0; s < this->animations[currentAnimation].skeletons.size(); s++)
		{
			float fps = 24;
			vector<D3DXMATRIX> matrices;
		
			float offset = this->animations[currentAnimation].skeletons[s].keys[0].time;
			int maxKeys = this->animations[currentAnimation].skeletons[s].keys.size() - 1;

			float currKeyTime =  this->animations[currentAnimation].skeletons[s].keys[currentKey].time;
			float nextKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey+1].time;

			if(time >= (this->animations[currentAnimation].skeletons[s].keys[this->animations[currentAnimation].skeletons[s].keys.size()-1].time-offset)/fps)
			{
				currentKey = 0;
				time = 0;
			}
			else
			{
				if(currentKey + 2 <= maxKeys)
				{
					if(time >= (nextKeyTime-offset)/fps)
					{
						currentKey++;
					}
				}
			}
		
			currKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey].time;
			nextKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].time;

			float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
			float timePass = time - (currKeyTime-offset)/fps;
			float lerpValue = timePass/timeInterval;

			for(int i = 0; i < this->animations[currentAnimation].skeletons[s].keys[currentKey].joints.size(); i++)
			{
				D3DXMATRIX outMat;
				D3DXVECTOR3 outScale, outTrans;
				D3DXQUATERNION outQuat;
				D3DXQUATERNION tempQuat1;
				FFloat4ToD3DXQUATERNION(tempQuat1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].rotation);
				D3DXQUATERNION tempQuat2;
				FFloat4ToD3DXQUATERNION(tempQuat2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].rotation);
				D3DXVECTOR3 tempTrans1;
				FFloat3ToD3DXVECTOR3(tempTrans1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].translation);
				D3DXVECTOR3 tempTrans2;
				FFloat3ToD3DXVECTOR3(tempTrans2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].translation);
				D3DXVECTOR3 tempScale1;
				FFloat3ToD3DXVECTOR3(tempScale1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].scale);
				D3DXVECTOR3 tempScale2;
				FFloat3ToD3DXVECTOR3(tempScale2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].scale);

				D3DXQuaternionSlerp(&outQuat, &tempQuat1, &tempQuat2, lerpValue);
				D3DXVec3Lerp(&outScale, &tempScale1, &tempScale2, lerpValue);
				D3DXVec3Lerp(&outTrans, &tempTrans1, &tempTrans2, lerpValue);
				D3DXMatrixTransformation(&outMat, NULL, NULL, &outScale, NULL, &outQuat, &outTrans);

				D3DXMATRIX locatorMatrix;
				D3DXVECTOR3 locateScale(1, 1, 1);
				D3DXQUATERNION locateRotate(0, 0, 0, 1);
				D3DXVECTOR3 locateTrans;
				
				if(i == this->animations[currentAnimation].propsLocators.hatIndex)
				{
					locateTrans = D3DXVECTOR3(
						this->animations[currentAnimation].propsLocators.hatPos[0], 
						this->animations[currentAnimation].propsLocators.hatPos[1], 
						this->animations[currentAnimation].propsLocators.hatPos[2]);
						D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
						this->hatMatrix = locatorMatrix * outMat;
				}
				else if(i == this->animations[currentAnimation].propsLocators.rightHandIndex)
				{
					locateTrans = D3DXVECTOR3(
						this->animations[currentAnimation].propsLocators.rightHandPos[0], 
						this->animations[currentAnimation].propsLocators.rightHandPos[1], 
						this->animations[currentAnimation].propsLocators.rightHandPos[2]);
						D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
						this->rightHandMatrix = locatorMatrix * outMat;
				}
				else if(i == this->animations[currentAnimation].propsLocators.leftHandIndex)
				{
					locateTrans = D3DXVECTOR3(
						this->animations[currentAnimation].propsLocators.leftHandPos[0], 
						this->animations[currentAnimation].propsLocators.leftHandPos[1], 
						this->animations[currentAnimation].propsLocators.leftHandPos[2]);
						D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
						this->leftHandMatrix = locatorMatrix * outMat;
				}
				D3DXMATRIX scale;
				D3DXMatrixScaling(&scale, 1.0f, 1.0f, 1.0f);
				outMat = outMat * scale;
				matrices.push_back(outMat);
			}

			UpdateSkeletonTexture(&matrices);
		}
		time += dt;
	}
}

ID3D10ShaderResourceView* Animation::getResource()
{
	return this->texPack.resourceView;
}

void Animation::UpdateSkeletonTexture(vector<D3DXMATRIX>* mat)
{	
	D3DXMATRIX* matrices;
	
	if(SUCCEEDED(this->texPack.texture->Map(0, D3D10_MAP_WRITE_DISCARD, 0, (void**)&matrices)))
	{
		for(UINT m = 0; m < mat->size(); m++)
		{
			matrices[m] = mat->at(m);
		}
	}
	this->texPack.texture->Unmap(0);
	this->texPack.texture;
	int ui = 0;
}

void Animation::PlayLoop(string name, Motion body = Motion::FullBody, int numberOfLoops = _INF_Fisk_, float overlapTime = 0.5f)
{
	if (animations.find(name) == animations.end()) 
	{
		this->animations[name].numLoops = numberOfLoops;
		this->animations[name].isAnimating = true;
		this->animations[name].overlapTime = overlapTime;
		this->currentAnimations.insert(currentAnimations.begin(), pair<string, AnimationFile*>(name, &this->animations[name]));
	}
}

void Animation::Play(string name, Motion body = Motion::FullBody)
{
	//PlayLoop(name, body, 1);
	this->currentAnimation = name;
}

void Animation::Stop(string name, Motion body = Motion::FullBody)
{
	this->animations[name].isAnimating = false;
	this->currentAnimations.erase(name);
}

void Animation::FFloat3ToD3DXVECTOR3(D3DXVECTOR3 &out, FFloat3 &in)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}

void Animation::FFloat4ToD3DXQUATERNION(D3DXQUATERNION &out, FFloat4 &in)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
	out.w = in.w;
}