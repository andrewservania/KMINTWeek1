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


Cow::~Cow()
{
}

// Execute code when rabbit has been left clicked upon
void Cow::OnLeftClick()
{
	printf("Left-clicked on cow!\n");
}

// Execute code when rabbit has been right clicked upon
void Cow::OnRightClick()
{
	printf("Right-clicked on cow!\n");
}

void Cow::setNode(Node* node)
{
	 currentNode = node; 
	 mX = node->GetBoundingBox().x;
	 mY = node->GetBoundingBox().y;
}

// Draw cow texture
void Cow::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY,100, 100);
}
