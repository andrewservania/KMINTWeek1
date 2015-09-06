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
std::shared_ptr<Edge> edge1;

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

	node1 = std::make_shared<Node>();
	node2 = std::make_shared<Node>();
	node3 = std::make_shared<Node>();
	node4 = std::make_shared<Node>();
	node5 = std::make_shared<Node>();
	node6 = std::make_shared<Node>();
	edge1 = std::make_shared<Edge>(100,100,150,200);

	node1->SetOffset(100, 100);
	node2->SetOffset(150, 200);
	node3->SetOffset(200, 300);
	node4->SetOffset(250, 400);
	node5->SetOffset(300, 500);
	node6->SetOffset(350, 600);

	application->AddRenderable(node1.get());
	application->AddRenderable(node2.get());
	application->AddRenderable(node3.get());
	application->AddRenderable(node4.get());
	application->AddRenderable(node5.get());
	application->AddRenderable(node6.get());
	application->AddRenderable(edge1.get());

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
		application->DrawText("Welcome to KMint", 150, 50);

		// For the background
		application->SetColor(Color(255, 255, 255, 255)); // Black color
		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}