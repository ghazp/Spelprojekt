#pragma once

#include "stdafx.h"

class Terrain
{
private:
	float m_width;
	float m_widthBetweenVertices;
	float m_height;
	float m_heightBetweenVertices;
	int m_rows;
	int m_cols;
	int m_nrOfVertices;
	vector<ID3D10ShaderResourceView*> m_textures;
	vector<ID3D10ShaderResourceView*> m_alphaMaps;
	D3DXVECTOR3 m_topLeft;
	D3DXVECTOR3 m_bottomRight;
	ID3D10Buffer* m_vertexBuffer;
public:
	Terrain();
	Terrain(ID3D10Device* device, D3DXVECTOR3 v1, D3DXVECTOR3 v2, int rows, int cols, vector<ID3D10ShaderResourceView*> _textures, vector<ID3D10ShaderResourceView*> _alphaMaps);
	virtual ~Terrain();
	
	ID3D10Buffer* getVertexBuffer()const { return this->m_vertexBuffer; }
	void render(ID3D10EffectTechnique* tech, ID3D10EffectTechnique* _tech2, ID3D10Effect* effect, int pass, ID3D10InputLayout* _particleLayout);
};