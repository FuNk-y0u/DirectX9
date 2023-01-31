#pragma once

//
// d3d9.h for d3d logic
//
#include<d3d9.h>

class GraphicsDevice
{
	public:
		GraphicsDevice();
		~GraphicsDevice();

		//
		// d3d functions
		//

		void Initialize(HWND hWnd, bool windowed);
		void Clear(D3DCOLOR color);
		void Begin();
		void End();
		void Present();

		//
		//	Shorthand for IDirect3DDevice9 *device;
		//
		LPDIRECT3DDEVICE9 device;

	private:
		LPDIRECT3D9 direct3d;


};
