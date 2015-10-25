#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include <time.h>
#include "AStar.h"
#include "Graph.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Main entry-point for this application.
/// 			Initialize SDL and all game entities.
///
/// 			</summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="args">	Number of command-line arguments. </param>
///
/// <returns>	Exit-code for the process - 0 for success, else an error code. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int args[])
{
	srand(static_cast<unsigned int>(time(nullptr)));						// initialize random seed

	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}

	application->SetTargetFPS(60);

	auto graph = new Graph(application);									// Create a graph

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
				graph->cow->OnClick(event);								// Handle mouse clicks for the cow
				break;
			}
		}

		application->SetColor(Color(0, 0, 0, 255));							// White color
		application->DrawText("Andrew Servania - KMINT Week 1", 200, 50);
		application->DrawText("Click on the cow to walk towards the rabbit via the shortest path.", 200, 70);
		graph->DrawShortPathDescription();
		// For the background
		application->SetColor(Color(255, 255, 255, 255));					// Black color
		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}

	return EXIT_SUCCESS;
}