#include<Windows.h>
#include"GraphicsDevice.h"
#include"GameSprite.h"

//
//   Generic Generate Window Functions
//
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow,
					LPCSTR className, LPCSTR windowTitle,
					int width, int height,
					HWND& hWnd);


bool GenerateWindow(HINSTANCE hInstance, int nCmdShow,
					LPCSTR className, LPCSTR windowTitle,
					int x, int y,
					int width, int height,
					HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
							WPARAM wParam, LPARAM lParam);

//
// UPDATE AND DRAW
//
void Update(float gameTime);
void Draw(GraphicsDevice *gDevice, float gameTime);

//
// GLOBAL PLATER SPRITES
//
GameSprite *player;

//
//	WinMain function set up window and enter message loop
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	if (GenerateWindow(hInstance, nCmdShow, "Win32_Window", "Arsenic", 640, 480, hWnd))
	{
		MSG msg;
		GraphicsDevice *gDevice = new GraphicsDevice();
		gDevice->Initialize(hWnd, true);

		player = new GameSprite((640 - 100) / 2, (480 - 100) / 2);
		player->Initialize(gDevice->device, "def_tex.png", 100, 100);

		while (true)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
				break;
			else
			{
				Update(0.0f);
				Draw(gDevice, 0.0f);
			}
		}
		delete gDevice;
		delete player;
		return msg.wParam;
	}
	
	return 0;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow,
					LPCSTR className, LPCSTR windowTitle,
					int width, int height,
					HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow,
						className, windowTitle,
						(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
						width, height,
						hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow,
					LPCSTR className, LPCSTR windowTitle, 
					int x, int y,
					int width, int height,
					HWND& hWnd)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, 
						windowTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
						x, y,
						width, height,
						NULL, NULL,
						hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	return true;
}

//
// WindowProc = Handles Input Sent To Window 
//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Update(float gameTime)
{
	//
	//	Update our sprites and other game logic
	//
}

void Draw(GraphicsDevice *gDevice, float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(151, 184, 224));
	gDevice->Begin();

	if (player && player->IsInitialized())
		player->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}