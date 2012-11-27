#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "DeferredRenderingEffectFile.h"
#include "DeferredSamplerEffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"
#include "VertexStructs.h"
#include "RenderTarget.h"
#include "DepthStencil.h"
#include "Sprite.h"
#include "FullScreenPlane.h"

class World
{
private:
	ID3DX10Font* m_fpsFont;
	Camera *m_camera;

	//Forward rendering
	ForwardRenderingEffectFile* m_forwardRendering;
	RenderTarget *m_forwardRenderTarget;
	DepthStencil *m_forwardDepthStencil;

	//Deferred sampling
	DeferredSamplerEffectFile *m_deferredSampler;
	DeferredRenderingEffectFile* m_deferredRendering;
	RenderTarget *m_positionBuffer;
	RenderTarget *m_normalBuffer;
	RenderTarget *m_diffuseBuffer;
	FullScreenPlane *m_deferredPlane;

	DeviceHandler* m_deviceHandler;

	vector<Model*> m_models;
	vector<Sprite*> m_sprites;
public:
	World();
	World(DeviceHandler* _deviceHandler);
	~World();

	void render();

	void addModel(Model *_model);
	bool removeModel(Model *_model);

	void addSprite(Sprite *sprite);
	bool removeSprite(Sprite *sprite);

	Camera *getCamera();
};