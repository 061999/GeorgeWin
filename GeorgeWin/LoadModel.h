#pragma once
#include <fstream>
#include <string>
using namespace std;
class LoadModel
{
public:
	LoadModel(string path);
	float* vertex;
	int* index;
	int vertexsize = 0;
	int indexsize = 0;
};

