#include "Model.h"

Model::Model()
{
	this->m_obb = NULL;
	this->m_bs = NULL;
}

Model::Model(ID3D10Device* _device, Mesh* _mesh, D3DXVECTOR3 _position, D3DXVECTOR3 _scale, D3DXVECTOR3 _rotation, float _alpha)
{
	this->m_alpha = _alpha;
	this->m_mesh = _mesh;
	this->m_position = _position;
	this->m_scale = _scale;
	this->m_rotation = _rotation;
	this->updateModelMatrix();
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(_position.x, 0.0f, _position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));  //new Obb(_device, D3DXVECTOR2(_position.x, _position.z), 3.0, 3.0, _rotation.y);
	
	/*point
	direction

	D3DXVECTOR2 B(10.0f, 10.0f);
	D3DXVECTOR2 A(22.0f, 10.0f);
	double lol = this->m_boundingSphere->pointToLineDistance(B, A);*/
}

Model::~Model()
{
	if(this->m_obb)
		delete this->m_obb;
}

float Model::getAlpha()const
{
	return this->m_alpha;
}

BoundingOrientedBox* Model::getObb()const
{
	return this->m_obb;
}

Mesh *Model::getMesh() const
{
	return this->m_mesh;
}

FLOAT3 Model::getPosition()const
{
	return FLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
}

D3DXVECTOR2 Model::getPosition2D()const
{
	return D3DXVECTOR2(this->m_position.x, this->m_position.z);
}

bool Model::intersects(const BoundingOrientedBox& _obb)const
{
	if(this->m_obb)
		return this->m_obb->Intersects(_obb);
	else if(this->m_bs)
		return this->m_bs->Intersects(_obb);
	else
		return false;
}

bool Model::intersects(const BoundingSphere& _bs)const
{
	if(this->m_obb)
		return this->m_obb->Intersects(_bs);
	else if(this->m_bs)
		return this->m_bs->Intersects(_bs);
	else
		return false;
}

void Model::move(FLOAT3 _distance)
{
	this->m_position.x += _distance.x;
	this->m_position.y += _distance.y;
	this->m_position.z += _distance.z;
	this->updateModelMatrix();
}

void Model::rotate(float _yaw, float _pitch, float _roll)
{
	/*D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, _yaw, _pitch, _roll);
	D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);
	this->m_obb->(this->m_obb->getAngle()-_yaw);*/
}

void Model::setAlpha(float _alpha)
{
	this->m_alpha = _alpha;
}

void Model::setPosition(D3DXVECTOR3 _position)
{
	this->m_position = _position;
	this->updateModelMatrix();
}

void Model::setScale(D3DXVECTOR3 _scale)
{
	this->m_scale = _scale;
	this->updateModelMatrix();
}

void Model::setRotation(D3DXVECTOR3 _rotation)
{
	this->m_rotation = _rotation;
	this->updateModelMatrix();
}

void Model::updateModelMatrix()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, this->m_rotation.x, this->m_rotation.y, this->m_rotation.z);
	
	D3DXMATRIX scalingMatrix;
	D3DXMatrixScaling(&scalingMatrix, this->m_scale.x, this->m_scale.y, this->m_scale.z);

	this->m_modelMatrix = D3DXMATRIX(
		this->m_scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, this->m_scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, this->m_scale.z, 0.0f,
		this->m_position.x, this->m_position.y, this->m_position.z, 1.0f);
	
	D3DXMatrixMultiply(&this->m_modelMatrix, &scalingMatrix, &this->m_modelMatrix);
	D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);
}

void Model::setPosition(FLOAT3 _position)
{
	this->m_position = D3DXVECTOR3(_position.x, _position.y, _position.z);
	this->updateModelMatrix();
}

void Model::setScale(float x, float y, float z)
{
	this->m_scale = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}

void Model::setRotation(float x, float y, float z)
{
	this->m_rotation = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}