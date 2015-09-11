#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Node.h"
#include <memory>
#include "Edge.h"
#include "AStar.h"
#include "Cow.h"
#include "Rabbit.h"

std::shared_ptr<Node> node1;
std::shared_ptr<Node> node2;
std::shared_ptr<Node> node3;
std::shared_ptr<Node> node4;
std::shared_ptr<Node> node5;
std::shared_ptr<Node> node6;
std::shared_ptr<Node> node7;
std::shared_ptr<Node> node8;

Cow* cow;
Rabbit* rabbit;

void CreateGraph(FWApplication* _application);
void OnClick(SDL_Event &event);


// Entry point
int main(int args[])
{

	auto application = new FWApplication();

	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);

	CreateGraph(application);							// Create graph

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
					OnClick(event);
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


	node1 = std::make_shared<Node>(1);
	node2 = std::make_shared<Node>(2);
	node3 = std::make_shared<Node>(3);
	node4 = std::make_shared<Node>(4);
	node5 = std::make_shared<Node>(5);
	node6 = std::make_shared<Node>(6);
	node7 = std::make_shared<Node>(7);
	node8 = std::make_shared<Node>(8);
	
	node1->SetOffset(800, 450);
	node2->SetOffset(500, 400);
	node3->SetOffset(600, 100);
	node4->SetOffset(730, 240);
	node5->SetOffset(900, 100);
	node6->SetOffset(930, 400);
	node7->SetOffset(1050, 550);
	node8->SetOffset(1050, 300);

	node1->AddEdge(node2.get(), 10000);
	node1->AddEdge(node7.get(), 10000);
	node1->AddEdge(node6.get(), 10000);
	node2->AddEdge(node3.get(), 10000);
	node2->AddEdge(node4.get(), 10000);
	node2->AddEdge(node8.get(), 10000);
	node3->AddEdge(node4.get(), 10000);
	node3->AddEdge(node5.get(), 10000);
	node4->AddEdge(node6.get(), 10000);
	node4->AddEdge(node5.get(), 10000);
	node5->AddEdge(node6.get(), 10000);
	node5->AddEdge(node8.get(), 10000);
	node7->AddEdge(node8.get(), 10000);

	cow = new Cow();
	rabbit = new Rabbit();

	AStar* aStar = new AStar(node7.get(), node3.get());

	auto shortestPath = aStar->Find();
	printf("Shortest path: ");
	while (!shortestPath.empty())
	{
		Node* step = shortestPath.top();
		printf(std::to_string(step->id).c_str());
		shortestPath.pop();
		if (!shortestPath.empty())
		printf(" -> ");
	}
	printf("\n");

}


// Method responsible for handling mouse clicks
void OnClick(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (event.motion.x >= cow->GetBoundingBox().x - 90 &&
			event.motion.x <= cow->GetBoundingBox().x + 90 &&
			event.motion.y >= cow->GetBoundingBox().y - 90 &&
			event.motion.y <= cow->GetBoundingBox().y + 90)
			{
				cow->OnLeftClick();
			}

		if (event.motion.x >= rabbit->GetBoundingBox().x - 90 &&
			event.motion.x <= rabbit->GetBoundingBox().x + 90 &&
			event.motion.y >= rabbit->GetBoundingBox().y - 90 &&
			event.motion.y <= rabbit->GetBoundingBox().y + 90)
			{
				rabbit->OnLeftClick();
			}
	
	}

	if (event.button.button == SDL_BUTTON_RIGHT){
		if (event.motion.x >= cow->GetBoundingBox().x - 90 &&
			event.motion.x <= cow->GetBoundingBox().x + 90 &&
			event.motion.y >= cow->GetBoundingBox().y - 90 &&
			event.motion.y <= cow->GetBoundingBox().y + 90)
			{
				cow->OnRightClick();
			}

		if (event.motion.x >= rabbit->GetBoundingBox().x - 90 &&
			event.motion.x <= rabbit->GetBoundingBox().x + 90 &&
			event.motion.y >= rabbit->GetBoundingBox().y - 90 &&
			event.motion.y <= rabbit->GetBoundingBox().y + 90)
			{
				rabbit->OnRightClick();
			}
	}
}

