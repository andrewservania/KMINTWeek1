#include "Rabbit.h"
#include "Graph.h"


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
																	// If Cow is on the same node as the rabbit. 
	if (Graph::cow->getCurrentNode()->id == currentNode->id)
	{
		Node* newLocation = Graph::graphNodes.at(rand() % 8);		// Put the rabbit in a random location
		this->setCurrentNode(newLocation);
		while (Graph::cow->getCurrentNode()->id == currentNode->id) // if it's still on the same location as the cow. Choose a different location for the rabbit.
		{
			newLocation = Graph::graphNodes.at(rand() % 8);
			this->setCurrentNode(newLocation);
		}
		Graph::UpdateShortPathDescription();						// Update the shortest path using the new location of the cow and the rabbit
	}

}

// Draw the rabbit texture
void Rabbit::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY, 100, 100);
}

// Execute code if rabbit has been left-clicked upon
void Rabbit::OnLeftClick()
{
	printf("Left-clicked on rabbit!\n");

}

// Execute code if rabbit has been right-clicked upon
void Rabbit::OnRightClick()
{
	printf("Right-clicked on rabbit!\n");

}

void Rabbit::setCurrentNode(Node* node)
{
	currentNode = node;	
	mX = node->GetBoundingBox().x;
	mY = node->GetBoundingBox().y;
}
