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

Node* node1;
Node* node2;
Node* node3;
Node* node4;
Node* node5;
Node* node6;
Node* node7;
Node* node8;

Cow* cow;
Rabbit* rabbit;

std::vector<Node*> graph;
// Method declarations
void CreateGraph(FWApplication* _application);
void OnClick(SDL_Event &event);


// Entry point
int main(int args[])
{
	/* initialize random seed: */
	srand(time(NULL));

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

	// Create nodes
	node1 = new Node(1);
	node2 = new Node(2);
	node3 = new Node(3);
	node4 = new Node(4);
	node5 = new Node(5);
	node6 = new Node(6);
	node7 = new Node(7);
	node8 = new Node(8);
	
	// Set their position on screen
	node1->SetOffset(800, 450);
	node2->SetOffset(500, 400);
	node3->SetOffset(600, 100);
	node4->SetOffset(730, 240);
	node5->SetOffset(900, 100);
	node6->SetOffset(930, 400);
	node7->SetOffset(1050, 550);
	node8->SetOffset(1050, 300);

	// Connect nodes with edges and add weight to the edges
	node1->AddEdge(node2, 10000);
	node1->AddEdge(node7, 10000);
	node1->AddEdge(node6, 10000);
	node2->AddEdge(node3, 10000);
	node2->AddEdge(node4, 10000);
	node2->AddEdge(node8, 10000);
	node3->AddEdge(node4, 10000);
	node3->AddEdge(node5, 10000);
	node4->AddEdge(node6, 10000);
	node4->AddEdge(node5, 10000);
	node5->AddEdge(node6, 10000);
	node5->AddEdge(node8, 10000);
	node7->AddEdge(node8, 10000);

	// Add the nodes to a vector
	graph.push_back(node1);
	graph.push_back(node2);
	graph.push_back(node3);
	graph.push_back(node4);
	graph.push_back(node5);
	graph.push_back(node6);
	graph.push_back(node7);
	graph.push_back(node8);

	// Create a cow and put it on a random node on the screen
	cow = new Cow();
	cow->setNode(graph.at(rand() % 8));

	// Create a rabbit and put it on a random node on the screen
	rabbit = new Rabbit();
	rabbit->setCurrentNode(graph.at(rand() % 8));

	//if rabbit's current node is equal to the node of the code, pick a new node for the rabbit
	while (cow->getCurrentNode()->id == rabbit->getCurrentNode()->id)
		rabbit->setCurrentNode(graph.at(rand() % 8));





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
				
				AStar* aStar = new AStar(cow->getCurrentNode(), rabbit->getCurrentNode());

				// Calculate the shortest path based on the current node of both the cow(start) and the rabbit(goal)
				auto shortestPath = aStar->Find();
				printf("Shortest path: ");
				while (!shortestPath.empty())
				{
					Node* step = shortestPath.top();

					
					cow->setNode(step);

					printf(std::to_string(step->id).c_str());
					shortestPath.pop();
					if (!shortestPath.empty())
						printf(" -> ");
				}
				printf("\n");
				cow->OnLeftClick();
				while (cow->getCurrentNode()->id == rabbit->getCurrentNode()->id)
				rabbit->setCurrentNode(graph.at(rand() % 8));
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

