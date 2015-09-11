#include "Rabbit.h"


Rabbit::Rabbit()
{
	mTexture = mApplication->LoadTexture("rabbit-3.png");
	mApplication->AddRenderable(this);
	mX = 500;
	mY = 400;
}

Rabbit::~Rabbit()
{
}

void Rabbit::Update(float deltaTime)
{

}

void Rabbit::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY, 100, 100);
}

void Rabbit::OnLeftClick()
{
	printf("Left-clicked on rabbit!\n");

}

void Rabbit::OnRightClick()
{
	printf("Right-clicked on rabbit!\n");

}

