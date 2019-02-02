#include "FuzzyEngine.h"

FuzzyEngine::FuzzyEngine() {}

FuzzyEngine::~FuzzyEngine() {}

void FuzzyEngine::inputData(float distance, int size)
{
	// Distance Fuzzification
	m_distanceIn = distance;
	near = fuzzyGradeDown(75, 125, distance);
	middle = fuzzyTrapezoid(75, 125, 200, 250, distance);
	far = fuzzyGradeUp(200, 250, distance);

	// Size Fuzzification
	m_forceSizeIn = size;
	tiny = fuzzyGradeDown(5, 10, size);
	small = fuzzyTrapezoid(5, 10, 15, 20, size);
	medium = fuzzyTrapezoid(15, 20, 25, 30, size);
	large = fuzzyGradeUp(25, 30, size);
}

int FuzzyEngine::getResponseForceSize()
{
	low = fuzzyAnd(fuzzyAnd(fuzzyNot(near), fuzzyNot(large)), fuzzyNot(fuzzyAnd(medium, medium)));
	moderate = fuzzyOr(fuzzyOr(fuzzyAnd(near, tiny), fuzzyAnd(middle, small)), fuzzyAnd(large, far));
	severe = fuzzyOr(fuzzyAnd(near, fuzzyNot(tiny)), fuzzyAnd(large, middle));
 	return low * 10 + medium * 30 + large * 50;
}

float FuzzyEngine::fuzzyTrapezoid(float x0, float x1, float x2, float x3, float val)
{
	float result;
	if (val <= x0 || val >= x3)
	{
		result = 0.f;
	}
	else if (val >= x1 && val <= x2) 
	{
		result = 1.f;
	}
	else if (val < x1)
	{
		result = ((val - x0) / (x1 - x0));
	}
	else
	{
		result = (x3 - val) / (x3 - x2);
	}
	return result;
}

float FuzzyEngine::fuzzyTriangle(float x0, float x1, float x2, float val)
{
	float result;
	if (val <= x0 || val >= x2)
	{
		result = 0.f;
	}
	else if (val == x1)
	{
		result = 1.f;
	}
	else if (val < x1)
	{
		result = ((val - x0) / (x1 - x0));
	}
	else
	{
		result = ((x2 - val) / (x2 - x1));
	}
	return result;
}

float FuzzyEngine::fuzzyGradeUp(float x0, float x1, float val)
{
	float result;
	if (val <= x0)
	{
		result = 0.f;
	}
	else if (val >= x1)
	{
		result = 1.f;
	}
	else
	{
		result = ((val - x0) / (x1 - x0));
	}

	return result;
}

float FuzzyEngine::fuzzyGradeDown(float x0, float x1, float val)
{
	float result;
	if (val <= x0)
	{
		result = 1.f;
	}
	else if (val >= x1)
	{
		result = 0.f;
	}
	else
	{
		result = 1.f - ((val - x0) / (x1 - x0));
	}

	return result;
}

float FuzzyEngine::fuzzyAnd(float a, float b)
{
	return std::min(a, b);
}

float FuzzyEngine::fuzzyOr(float a, float b)
{
	return std::max(a, b);
}

float FuzzyEngine::fuzzyNot(float a)
{
	return (1.f - a);
}
