#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Node.h"
#include <memory>
#include "Edge.h"

std::shared_ptr<Node> node1;
std::shared_ptr<Node> node2;
std::shared_ptr<Node> node3;
std::shared_ptr<Node> node4;
std::shared_ptr<Node> node5;
std::shared_ptr<Node> node6;
std::shared_ptr<Node> node7;
std::shared_ptr<Node> node8;


void CreateGraph(FWApplication* _application);

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
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
	



	node1->SetOffset(800, 400);
	node2->SetOffset(500, 400);
	node3->SetOffset(600, 100);
	node4->SetOffset(730, 240);
	node5->SetOffset(900, 100);
	node6->SetOffset(930, 400);
	node7->SetOffset(1050, 550);
	node8->SetOffset(1050, 300);

	node1->AddEdge(node2.get(), 1000);
	node1->AddEdge(node7.get(), 1000);
	node1->AddEdge(node6.get(), 1000);
	node2->AddEdge(node3.get(), 1000);
	node2->AddEdge(node4.get(), 1000);
	node2->AddEdge(node8.get(), 1000);
	node3->AddEdge(node4.get(), 1000);
	node3->AddEdge(node5.get(), 1000);
	node4->AddEdge(node6.get(), 1000);
	node4->AddEdge(node5.get(), 1000);
	node5->AddEdge(node6.get(), 1000);
	node5->AddEdge(node8.get(), 1000);
	node7->AddEdge(node8.get(), 1000);

	_application->AddRenderable(node1.get());
	_application->AddRenderable(node2.get());
	_application->AddRenderable(node3.get());
	_application->AddRenderable(node4.get());
	_application->AddRenderable(node5.get());
	_application->AddRenderable(node6.get());
	_application->AddRenderable(node7.get());
	_application->AddRenderable(node8.get());

	for (Edge* e : node1->GetEdges())
		_application->AddRenderable(e);
	for (Edge* e : node2->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node3->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node4->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node5->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node6->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node7->GetEdges())
		_application->AddRenderable(e);	
	for (Edge* e : node8->GetEdges())
		_application->AddRenderable(e);
}
