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

//void Cow::OnClick(SDL_Event& event)
//{
//	if (event.button.button == SDL_BUTTON_LEFT)
//		OnLeftClick(event);
//	if (event.button.button == SDL_BUTTON_RIGHT)
//		OnRightClick(event);
//}
//// Execute code when rabbit has been left clicked upon
//void Cow::OnLeftClick(SDL_Event &event)
//{
//	printf("Left-clicked on cow!\n");
//}
//
//// Execute code when rabbit has been right clicked upon
//void Cow::OnRightClick(SDL_Event &event)
//{
//	printf("Right-clicked on cow!\n");
//}