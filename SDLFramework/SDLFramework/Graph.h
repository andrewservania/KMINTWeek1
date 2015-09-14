#pragma once
#include "Rabbit.h"
#include "Cow.h"
class Graph
{
public:
	Cow* cow;
	Rabbit* rabbit;
	Node* node1;
	Node* node2;
	Node* node3;
	Node* node4;
	Node* node5;
	Node* node6;
	Node* node7;
	Node* node8;
	std::vector<Node*> graphNodes;

	Graph(FWApplication* _application);
	~Graph();

};

