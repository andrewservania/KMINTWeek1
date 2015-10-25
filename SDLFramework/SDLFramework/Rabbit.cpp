#include "Rabbit.h"
#include "Graph.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor.
/// 			Create a rabbit by providing it an id.
/// 			1) Load a picture of the rabbit.
/// 			2) Instantiate the state machine of the rabbit.
/// 			3) Set the state of the rabbit to Wandering
///
/// 			  </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="id">	The identifier. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit()
{
	mTexture = mApplication->LoadTexture("rabbit-3.png");
	mApplication->AddRenderable(this);
	mX = 500;
	mY = 400;
	timerCounter = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Rabbit::~Rabbit()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the rabbit and the state machine of the rabbit. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="deltaTime">	The delta time. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Rabbit::Update(float deltaTime)
{
	if (Graph::cow->getCurrentNode()->id == currentNode->id)
	{
		if (timerCounter == 10)
		{
			Node* newLocation = Graph::graphNodes.at(rand() % 8);		// Put the rabbit in a random location
			this->setCurrentNode(newLocation);
			while (Graph::cow->getCurrentNode()->id == currentNode->id) // if it's still on the same location as the cow. Choose a different location for the rabbit.
			{
				newLocation = Graph::graphNodes.at(rand() % 8);
				this->setCurrentNode(newLocation);
			}
			Graph::UpdateShortPathDescription();						// Update the shortest path using the new location of the cow and the rabbit
			timerCounter = 0;
		}
		timerCounter++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw a picture of the rabbit on screen. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Rabbit::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY, 100, 100);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Execute code if rabbit has been left-clicked upon. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Rabbit::OnLeftClick()
{
	printf("Left-clicked on rabbit!\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Execute code if rabbit has been right-clicked upon. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Rabbit::OnRightClick()
{
	printf("Right-clicked on rabbit!\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Set the current node and coordinates of the rabbit. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="node">	[in,out] If non-null, the node. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Rabbit::setCurrentNode(Node* node)
{
	currentNode = node;
	mX = node->GetBoundingBox().x;
	mY = node->GetBoundingBox().y;
}