#pragma once

#include "stdafx.h"

class DeviceHandler
{
private:
	D3D10_DRIVER_TYPE m_driverType;
	ID3D10Device* m_device;
	IDXGISwapChain*	m_swapChain;
	HWND m_hWnd;
	D3DXVECTOR2 m_screenSize;
	ID3D10RenderTargetView *m_renderTarget;
	ID3D10DepthStencilView *m_depthStencilView;

	ID3D10RenderTargetView *createRenderTargetView();
	ID3D10DepthStencilView *createDepthStencilView(D3DXVECTOR2 size);
public:
	DeviceHandler(HWND _hWnd);
	~DeviceHandler();

	ID3D10Device* getDevice()const;
	HRESULT present()const;

	D3DXVECTOR2 getScreenSize();
	ID3D10RenderTargetView *getForwardRenderTarget();
	ID3D10DepthStencilView *getForwardDepthStencil();

	void setInputLayout(ID3D10InputLayout *inputLayout);
};