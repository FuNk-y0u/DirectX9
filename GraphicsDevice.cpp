//
// Make Sure You Have Linked DirectX SDK (JUNE 2010)
//

#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
	//
	// Constructor Logic
	//
}

GraphicsDevice::~GraphicsDevice()
{
	if (device)
	{
		device->Release();
		device = NULL;
	}
	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

void GraphicsDevice::Initialize(HWND hWnd, bool windowed)
{
	//
	// Create Direct 3D Pointer
	//
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams,  sizeof(presentationParams));
	presentationParams.Windowed = windowed;
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParams.hDeviceWindow = hWnd;

	//
	//	Create The Device
	//	ADADAPTER_DEFAULT = Primary Display Adapter
	//	D3DDEVTYPE_HAL = Hardware rasterization
	//	D3DCREATE_MIXED_VERTEXPROCESSING = Uses both hardware and software for vertex processing
	//
	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
							hWnd, D3DCREATE_MIXED_VERTEXPROCESSING,
							&presentationParams, &device);

}


void GraphicsDevice::Clear(D3DCOLOR color)
{
	//
	//	2nd PARAM null So it clears all the back buffer
	//
	device->Clear(0, NULL,  D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	//
	//	presents our scene to window
	//

	device->Present(NULL, NULL, NULL, NULL);
}