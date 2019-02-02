#ifndef FUZZYENGINE_H
#define FUZZYENGINE_H

#include <algorithm>

class FuzzyEngine
{
public:
	//Public Functions
	FuzzyEngine();
	~FuzzyEngine();
	void inputData(float distance, int size);
	int getResponseForceSize();

private:
	// Private Functions

	// Fuzzification
	float fuzzyTrapezoid(float x0, float x1, float x2, float x3, float val);
	float fuzzyTriangle(float x0, float x1, float x2, float val);
	float fuzzyGradeDown(float x0, float x1, float val);
	float fuzzyGradeUp(float x0, float x1, float val);

	// Fuzzy Logic
	float fuzzyAnd(float a, float b);
	float fuzzyOr(float a, float b);
	float fuzzyNot(float a);

	// Private Members

	// Crisp Input
	float m_distanceIn;
	int m_forceSizeIn;

	// Force Size Fuzzy Variables
	float tiny;
	float small;
	float medium;
	float large;

	// Force Distance Fuzzy Variables
	float near;
	float middle;
	float far;

	// Threat Levels
	float low;
	float moderate;
	float severe;
};

#endif // !FUZZYENGINE_H
