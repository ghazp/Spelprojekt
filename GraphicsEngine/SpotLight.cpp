#include "SpotLight.h"

SpotLight::SpotLight()
{

}

SpotLight::SpotLight(ID3D10Device* _device, FLOAT3 _position, FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, FLOAT2 _angle, float _range)
{
	m_direction = _direction;
	D3DXMATRIX mat;
	D3DXMatrixRotationYawPitchRoll(&mat, 0.0f, D3DX_PI/2.0f, 0.0f);
	D3DXVECTOR4 temp;
	D3DXVec3Transform(&temp, &D3DXVECTOR3(m_direction.x, m_direction.y, m_direction.z), &mat);
	m_up = D3DXVECTOR3(temp.x, temp.y, temp.z);

	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
	this->m_angle = FLOAT2(cos(_angle.x / 2), cos(_angle.y / 2));
	this->m_range = _range;

	m_shadowMap = new DepthStencil(_device, INT2(1024, 1024));
	this->setPosition(_position);
}

SpotLight::~SpotLight()
{
	delete m_shadowMap;
}

void SpotLight::clearShadowMap(ID3D10Device* _device)
{
	this->m_shadowMap->clear(_device);
}

void SpotLight::setShadowMapAsRenderTarget(ID3D10Device* _device)
{
	_device->OMSetRenderTargets(0, NULL, m_shadowMap->getDepthStencilView());
}

FLOAT3 SpotLight::getPosition()
{
	return this->m_position;
}

FLOAT3 SpotLight::getDirection()
{
	return this->m_direction;
}

FLOAT3 SpotLight::getAmbientColor()
{
	return this->m_la;
}

FLOAT3 SpotLight::getDiffuseColor()
{
	return this->m_ld;
}

FLOAT3 SpotLight::getSpecularColor()
{
	return this->m_ls;
}

FLOAT2 SpotLight::getAngle()
{
	return this->m_angle;
}

float SpotLight::getRange()
{
	return this->m_range;
}

void SpotLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
	
	D3DXMATRIX projMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMatrixPerspectiveFovLH(&projMatrix, D3DX_PI/2.0f, 1.0f, 0.1f, 500000.0f);
	D3DXVECTOR3 eye(m_position.x, m_position.y, m_position.z);
	FLOAT3 dampDirection(m_direction.x, -m_direction.y, m_direction.z);
	FLOAT3 temp(m_position+dampDirection);
	D3DXVECTOR3 at(temp.x, temp.y, temp.z);

	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &m_up);
	D3DXMatrixMultiply(&m_wvp, &viewMatrix, &projMatrix);
}

void SpotLight::setDirection(FLOAT3 _direction)
{
	this->m_direction = _direction;
}

void SpotLight::setAmbientColor(FLOAT3 _la)
{
	this->m_la = _la;
}

void SpotLight::setDiffuseColor(FLOAT3 _ld)
{
	this->m_ld = _ld;
}

void SpotLight::setSpecularColor(FLOAT3 _ls)
{
	this->m_ls = _ls;
}

void SpotLight::setAngle(FLOAT2 _angle)
{
	this->m_angle = FLOAT2(cos(_angle.x / 2), cos(_angle.y / 2));
}

void SpotLight::setRange(float _range)
{
	this->m_range = _range;
}