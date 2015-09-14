#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Node.h"

#include "AStar.h"
#include "Graph.h"



Graph *graph;


// Method declarations

void OnClick(SDL_Event &event, FWApplication * _application);


// Entry point
int main(int args[])
{
	/* initialize random seed: */
	srand(static_cast<unsigned int>(time(nullptr)));

	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);

	graph = new Graph(application);

	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					application->Quit();
					break;
				case SDL_KEYDOWN:

				switch (event.key.keysym.sym){

					case SDLK_0:

					break;

					default:

						break;
				}
				break;
				case SDL_MOUSEBUTTONDOWN:
					OnClick(event, application);
					break;


			}
		}
		
		application->SetColor(Color(0, 0, 0, 255)); // White color
		application->DrawText("KMINT Week 1", 150, 50);

		// For the background
		application->SetColor(Color(255, 255, 255, 255)); // Black color
		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}

// Method responsible for creating nodes and edges that would ultimately form a graph
void CreateGraph(FWApplication* _application)
{


}


// Method responsible for handling mouse clicks
void OnClick(SDL_Event &event, FWApplication * _application)
{
	//_application->cow->OnClick(event);
	//if (event.button.button == SDL_BUTTON_LEFT)
	//{
	//	if (event.motion.x >= cow->GetBoundingBox().x - 90 &&
	//		event.motion.x <= cow->GetBoundingBox().x + 90 &&
	//		event.motion.y >= cow->GetBoundingBox().y - 90 &&
	//		event.motion.y <= cow->GetBoundingBox().y + 90)
	//		{
	//			
	//			AStar* aStar = new AStar();

	//			// Calculate the shortest path based on the current node of both the cow(start) and the rabbit(goal)
	//			auto shortestPath = aStar->GetShortestPath(cow->getCurrentNode(), rabbit->getCurrentNode());
	//			printf("Shortest path: ");
	//			while (!shortestPath.empty())
	//			{
	//				Node* step = shortestPath.top();

	//				
	//				cow->setNode(step);

	//				printf(std::to_string(step->id).c_str());
	//				shortestPath.pop();
	//				if (!shortestPath.empty())
	//					printf(" -> ");
	//			}
	//			printf("\n");
	//			cow->OnLeftClick();
	//			while (cow->getCurrentNode()->id == rabbit->getCurrentNode()->id)
	//			rabbit->setCurrentNode(graph.at(rand() % 8));
	//		}

	//	if (event.motion.x >= rabbit->GetBoundingBox().x - 90 &&
	//		event.motion.x <= rabbit->GetBoundingBox().x + 90 &&
	//		event.motion.y >= rabbit->GetBoundingBox().y - 90 &&
	//		event.motion.y <= rabbit->GetBoundingBox().y + 90)
	//		{
	//			rabbit->OnLeftClick();
	//		}
	//
	//}

	//if (event.button.button == SDL_BUTTON_RIGHT){
	//	if (event.motion.x >= cow->GetBoundingBox().x - 90 &&
	//		event.motion.x <= cow->GetBoundingBox().x + 90 &&
	//		event.motion.y >= cow->GetBoundingBox().y - 90 &&
	//		event.motion.y <= cow->GetBoundingBox().y + 90)
	//		{
	//			cow->OnRightClick();
	//		}

	//	if (event.motion.x >= rabbit->GetBoundingBox().x - 90 &&
	//		event.motion.x <= rabbit->GetBoundingBox().x + 90 &&
	//		event.motion.y >= rabbit->GetBoundingBox().y - 90 &&
	//		event.motion.y <= rabbit->GetBoundingBox().y + 90)
	//		{
	//			rabbit->OnRightClick();
	//		}
	//}
}

