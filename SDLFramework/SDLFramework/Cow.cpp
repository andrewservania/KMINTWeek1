#include "Cow.h"
#include "Graph.h"
#include "AStar.h"
#include <string>
#include <memory>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor.
/// Create a cow by
/// 1) Load a picture of the cow.
/// 2) add the cow to items that have to be displayed on screen.    
/// 3) Set the cow's location at x=100 and y=100 on screen  
/// 4) Set the timer counter to 0.
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="id">	The identifier. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Cow::Cow()
{
	mTexture = mApplication->LoadTexture("cow-1.png");
	mApplication->AddRenderable(this);
	mX = 100;
	mY = 100;
	timerCounter = 0;
	drawRectangle = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates cow's movement.
/// 			The cow walks towards the rabbit step by step. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="deltaTime">	The delta time. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::Update(float deltaTime)
{

		if (!shortestPath.empty())
		{

			if (timerCounter >= 17)
			{

				Node* step = shortestPath.top();		// Get the next node to go to.	
				this->setNode(step);					// Set the cow's node to the next node to go to
				shortestPath.pop();
				timerCounter = 0;
			}
			timerCounter++;
		}
		if (drawRectangle) // Flash a rectangle if clicked on the cow for user click fleedback.
		{
			mApplication->SetColor(Color(0, 0, 0, 255));
			mApplication->DrawRect(mX-50, mY-50, 100, 100, true);

			drawRectangle = false;
		}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Cow::~Cow()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets current node and the coordinates of the cow on screen. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="node">	[in,out] If non-null, the node. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::setNode(Node* node)
{
	 currentNode = node; 
	 mX = node->GetBoundingBox().x;
	 mY = node->GetBoundingBox().y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw a picture of the cow on screen. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY,100, 100);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Handle all clicks registered on the cow.</summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="event">	[in,out] The event. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::OnClick(SDL_Event& event)
{
	// Handle clicks that are made within the range in which the cow is situated on
	if (event.motion.x >= static_cast<Sint32>(mX - 90) &&
		event.motion.x <= static_cast<Sint32>(mX + 90) &&
		event.motion.y >= static_cast<Sint32>(mY - 90) &&
		event.motion.y <= static_cast<Sint32>(mY + 90))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			OnLeftClick(event);
		if (event.button.button == SDL_BUTTON_RIGHT)
			OnRightClick(event);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Execute code when rabbit has been left clicked upon. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="event">	[in,out] The event. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::OnLeftClick(SDL_Event &event)
{	
	shared_ptr<AStar> aStar = make_shared<AStar>();

	// Calculate the shortest path based on the current node of both the cow(start) and the rabbit(goal)
	shortestPath = aStar->GetShortestPath(currentNode, Graph::rabbit->getCurrentNode());
	drawRectangle = true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Execute code when rabbit has been right clicked upon. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="event">	[in,out] The event. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Cow::OnRightClick(SDL_Event &event)
{
	shared_ptr<AStar> aStar = make_shared<AStar>();

	// Calculate the shortest path based on the current node of both the cow(start) and the rabbit(goal)
	 shortestPath = aStar->GetShortestPath(currentNode, Graph::rabbit->getCurrentNode());
	 drawRectangle = true;


}