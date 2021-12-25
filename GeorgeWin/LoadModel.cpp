#include "LoadModel.h"

LoadModel::LoadModel(string path)
{
	ifstream file(path, ios::binary);
	if (!file.is_open())
	{
		return;
	}

	file.read((char*)&vertexsize, sizeof(int));
	vertex = new float[vertexsize];
	file.read((char*)vertex, vertexsize * sizeof(float));

	file.read((char*)&indexsize, sizeof(int));
	index = new int[indexsize];
	file.read((char*)index, sizeof(int) * indexsize);

	file.close();
}
