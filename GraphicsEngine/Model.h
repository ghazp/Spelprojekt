#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "DataStructures.h"
#include "Obb.h"

class Model
{
private:
	Mesh* m_mesh;
	D3DXMATRIX m_modelMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_rotation;
	float m_alpha;
	Obb m_obb;
public:
	Model();
	Model(Mesh* _mesh, D3DXVECTOR3 _position, D3DXVECTOR3 _scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3 _rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f), float _alpha = 1.0f);
	~Model();
	
	DECLDIR float getAlpha()const;
	DECLDIR FLOAT3 getPosition()const;
	D3DXVECTOR2 getPosition2D()const;
	D3DXVECTOR3 getScale()const;
	D3DXVECTOR3 getRotation()const;
	Mesh* getMesh()const;
	D3DXMATRIX getModelMatrix()const { return this->m_modelMatrix; }
	bool intersects(const Obb& _obb)const;
	DECLDIR void move(FLOAT3 _distance);
	DECLDIR void rotate(float _yaw, float _pitch, float _roll);
	DECLDIR void setAlpha(float _alpha);
	void setPosition(D3DXVECTOR3 _position);
	void setScale(D3DXVECTOR3 _scale);
	void setRotation(D3DXVECTOR3 _rotation);
	void updateModelMatrix();

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setScale(float x, float y, float z);
	DECLDIR void setRotation(float x, float y, float z);
};