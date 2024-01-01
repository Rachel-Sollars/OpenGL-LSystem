#pragma once
#include <vector>
#include "MSMaths.h"

class Prism
{
public:
	Prism(int _numBaseVerts, float _baseRadius, std::vector<float>& _startPoint, std::vector<float>& _endPoint);
	void SetVerticesArray(std::vector<float>& vertices);
private:
	std::vector<float> startPoint, endPoint;
	int numBaseVerts;
	float baseRadius;
};