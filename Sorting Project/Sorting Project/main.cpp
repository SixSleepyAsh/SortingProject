#include <stdio.h>
#include <iostream>
#include "GraphicsSystem.h"
#include "Engine.h"

int main()
{
	Engine*	engine = SortingEngine();

	engine->Run();

	return 0;
}
	