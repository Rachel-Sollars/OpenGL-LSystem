#pragma once

#include <cmath>
#include <omp.h>
#include <vector>

class MSMaths
{
public:
	static const float PI;
	static const float TAU;

	/// <summary>
	/// Linearly interpolates from "pointA" to "pointB" through "by".
	/// </summary>
	/// <param name="pointA"></param>
	/// <param name="pointB"></param>
	/// <param name="by"></param>
	/// <returns>
	/// float
	/// </returns>
	static float Lerp(float pointA, float pointB, float by);

	/// <summary>
	/// Linearly interpolates from "pointA" to "pointB" through "by".
	/// </summary>
	/// <param name="pointA"></param>
	/// <param name="pointB"></param>
	/// <param name="by"></param>
	/// <returns>
	/// float
	/// </returns>
	static float LerpClamped(float pointA, float pointB, float by);

	/// <summary>
	/// Inversely interpolates between a min "pointA" and max "pointB" at a given "value".
	/// </summary>
	/// <param name="pointA"></param>
	/// <param name="pointB"></param>
	/// <param name="by"></param>
	/// <returns>
	/// float
	/// </returns>
	static float InverseLerp(float pointA, float pointB, float value);

	/// <summary>
	/// Inversely interpolates between a min "pointA" and max "pointB" at a given "value".
	/// </summary>
	/// <param name="pointA"></param>
	/// <param name="pointB"></param>
	/// <param name="by"></param>
	/// <returns>
	/// float
	/// </returns>
	static float InverseLerpClamped(float pointA, float pointB, float value);

	/// <summary>
	/// Remaps a value from between an input min and max to an output min and max.
	/// </summary>
	/// <param name="inMin"></param>
	/// <param name="inMax"></param>
	/// <param name="outMin"></param>
	/// <param name="outMax"></param>
	/// <param name="value"></param>
	/// <returns>
	/// float
	/// </returns>
	static float Remap(float inMin, float inMax, float outMin, float outMax, float value);

	/// <summary>
	/// !!!IMPORTANT!!! <br/> Returns the distance between "positionA" and "positionB" prior to squareroot.
	/// </summary>
	/// <param name="positionA"></param>
	/// <param name="positionB"></param>
	/// <returns>
	/// float
	/// </returns>
	static float GetDistanceOptimised(float positionA[], float positionB[]);

	/// <summary>
	/// Returns a boolean that is true if "Distance" is less than or equal to the distance between "positionA" and "positionB".
	/// </summary>
	/// <param name="positionA"></param>
	/// <param name="positionB"></param>
	/// <returns>
	/// bool
	/// </returns>
	static bool CloserThanOrEqualTo(float positionA[], float positionB[], float Distance);

	/// <summary>
	/// Qauntizes a given "Value" to the neares multiple of "increment".
	/// </summary>
	/// <param name="value"></param>
	/// <param name="increment"></param>
	/// <returns>
	/// float
	/// </returns>
	static float Quantize(float value, float increment);

	/// <summary>
	/// Finds a point in space at a given angle, in degrees, and distance from the current position. 
	/// </summary>
	/// <param name="currentPosition"></param>
	/// <param name="distance"></param>
	/// <param name="angle"></param>
	/// <returns>
	/// Vector2
	/// </returns>
	static std::vector<float> FindPointAtAngleDegrees(std::vector<float> currentPosition, float distance, float angle);
};