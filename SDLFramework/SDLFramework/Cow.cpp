#include "Cow.h"


Cow::Cow()
{
	mTexture = mApplication->LoadTexture("cow-1.png");
	mApplication->AddRenderable(this);
	mX = 100;
	mY = 100;
}


void Cow::Update(float deltaTime)
{

}

void Cow::OnLeftClick()
{
	printf("Left-clicked on cow!\n");
}

void Cow::OnRightClick()
{
	printf("Right-clicked on cow!\n");
}

void Cow::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY,100, 100);
}

Cow::~Cow()
{
}
