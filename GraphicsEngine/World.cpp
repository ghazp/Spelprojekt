#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_models = vector<Model*>();
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize().x, this->m_deviceHandler->getScreenSize().y);
	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_forwardRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getBackBuffer());
	this->m_forwardDepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	
	// Create a font
	D3DX10CreateFontA(this->m_deviceHandler->getDevice(), 30, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &this->m_fpsFont);
}

World::~World()
{
	for(int i = 0; i < this->m_models.size(); i++)
	{
		delete this->m_models[i];
	}

	delete this->m_forwardRendering;
	delete this->m_forwardRenderTarget;
	delete this->m_forwardDepthStencil;
	delete this->m_camera;
}

void World::render()
{
	//Init render stuff
	this->m_camera->updateViewMatrix();

	// Set variables
	this->m_forwardRendering->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_forwardRendering->setProjectionMatrix(this->m_camera->getProjectionMatrix());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	this->m_deviceHandler->setInputLayout(this->m_forwardRendering->getInputLayout());

	//clear render target
	this->m_forwardRenderTarget->clear(this->m_deviceHandler->getDevice());
	this->m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());
	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_forwardRenderTarget->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//Render all models
	for(int i = 0; i < this->m_models.size(); i++)
	{
		this->m_deviceHandler->getDevice()->IASetVertexBuffers(0, 1, &this->m_models[i]->getMesh()->buffer, &stride, &offset);

		this->m_forwardRendering->setModelMatrix(this->m_models[i]->getModelMatrix());
		this->m_forwardRendering->setTexture(this->m_models[i]->getMesh()->m_texture);

		D3D10_TECHNIQUE_DESC techDesc;
		this->m_forwardRendering->getTechniqueRenderModelForward()->GetDesc( &techDesc );

		for( UINT p = 0; p < techDesc.Passes; p++ )
		{
			this->m_forwardRendering->getTechniqueRenderModelForward()->GetPassByIndex( p )->Apply(0);
			this->m_deviceHandler->getDevice()->Draw(this->m_models[i]->getMesh()->nrOfVertices, 0);
		}
	}

	string str  = "KHJHWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWSK";
	RECT rc;
	rc.bottom = 100;
	rc.top = 200;
	rc.left = 400;
	rc.right = 500;
	this->m_fpsFont->DrawTextA(NULL, str.c_str(), -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//Finish render
	this->m_deviceHandler->present();
}

void World::addModel(Model *_model)
{
	this->m_models.push_back(_model);
}

bool World::removeModel(Model *_model)
{
	bool found = false;

	for(int i = 0; i < this->m_models.size() && !found; i++)
	{
		if(this->m_models[i] == _model)
		{
			delete this->m_models[i];
			this->m_models.erase(this->m_models.begin()+i);
			found = true;
		}
	}

	return found;
}

Camera *World::getCamera()
{
	return this->m_camera;
}