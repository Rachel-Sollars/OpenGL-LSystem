#include "MSMaths.h"

const float MSMaths::PI = 3.141593f;
const float MSMaths::TAU = 6.283185f;

float MSMaths::Lerp(float pointA, float pointB, float by)
{
    return pointA + (pointB - pointA) * by;
}

float MSMaths::LerpClamped(float pointA, float pointB, float by)
{
    if (by > 1)
        by = 1;
    else if (by < 0)
        by = 0;
    return pointA + (pointB - pointA) * by;
}

float MSMaths::InverseLerp(float pointA, float pointB, float value)
{
    return (value - pointA) / (pointB - pointA);
}

float MSMaths::InverseLerpClamped(float pointA, float pointB, float value)
{
    if (pointA > pointB)
    {
        if (value > pointA)
            value = pointA;
        else if (value < pointB)
            value = pointB;
    }

    else
    {
        if (value > pointB)
            value = pointB;
        else if (value < pointA)
            value = pointA;
    }
    return (value - pointA) / (pointB - pointA);
}

float MSMaths::Remap(float inMin, float inMax, float outMin, float outMax, float value)
{
    float newValue = InverseLerp(inMin, inMax, value);
    return Lerp(outMin, outMax, newValue);
}

float MSMaths::GetDistanceOptimised(float positionA[], float positionB[])
{
    if (sizeof(positionA) != sizeof(positionB)) {
        return NAN;
    }
    else {
        float returnVal = 0;
        for (int i = 0; i < sizeof(positionA); i++) {
            returnVal += ((positionA[i] - positionB[i]) * (positionA[i] - positionB[i]));
        }
        return returnVal;
    }
}

bool MSMaths::CloserThanOrEqualTo(float positionA[], float positionB[], float Distance)
{
    if (sizeof(positionA) != sizeof(positionB)) {
        return NULL;
    }
    else {
        float distVal = 0;

        for (int i = 0; i < sizeof(positionA); i++) {
            distVal += ((positionA[i] - positionB[i]) * (positionA[i] - positionB[i]));
        }
        return distVal <= Distance;
    }
}

float MSMaths::Quantize(float value, float increment)
{
    float diff = std::fmod(value, increment);
    float half = increment * 0.5f;

    if (diff == 0)
        return value;

    else if (diff < half)
        return value - diff;

    else
        return value + (increment - diff);
}

std::vector<float> MSMaths::FindPointAtAngleDegrees(std::vector<float> currentPosition, float distance, float angle)
{
    float a = angle * MSMaths::PI / 180;
    std::vector<float> pos{ currentPosition[0] + (distance * std::cos(a)), currentPosition[1] + (distance * std::sin(a)) };
    return pos;
}
