#include"GameSprite.h"

GameSprite::GameSprite()
{
	//
	//	Defaulting Sprite Pos to (0,0)
	//

	position.x = 0;
	position.y = 0;
	position.z = 0;

	//
	// If Color Is White Then The Image Looks Like Normal

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;

}

GameSprite::GameSprite(float x, float y)
{
	//
	// Set Position TO X, Y and Z to 0

	position.x = x;
	position.y = y;
	position.z = 0;

	//
	// If Color Is White Then The Image Looks Like Normal

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;
}

bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{

	//
	// Generating Texture From Image File
	//
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		std::string error_msg = "There was an issue creating texture, Make Sure The Image File Exists! FILE: " + file;
		MessageBox(NULL, error_msg.c_str(), NULL, NULL);
		return false;
	}

	//
	// Creating Sprite
	//

	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There Was An Issue Creating The Sprite", NULL, NULL);
		return false;
	}

	initialized = true;
	return true;
}

bool GameSprite::IsInitialized()
{
	return initialized;
}

void GameSprite::Update(float gameTime)
{
	//
	// Update logic here
	//
}


//
// Drawing Sprite
//
void GameSprite::Draw(float gameTime)
{
	if (sprite && tex)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(tex, NULL, NULL, &position, color);
		sprite->End();
	}
}

GameSprite::~GameSprite()
{
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
	if (tex)
	{
		tex->Release();
		tex = 0;
	}
}