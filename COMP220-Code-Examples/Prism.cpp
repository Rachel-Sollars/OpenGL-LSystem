#include "Prism.h"

Prism::Prism(int _numBaseVerts, float _baseRadius, std::vector<float>& _startPoint, std::vector<float>& _endPoint) {
    numBaseVerts = _numBaseVerts;
    baseRadius = _baseRadius;
    startPoint = { MSMaths::Quantize(_startPoint[0], 0.001f), MSMaths::Quantize(_startPoint[1], 0.001f) };
    endPoint = { MSMaths::Quantize(_endPoint[0], 0.001f), MSMaths::Quantize(_endPoint[1], 0.001f) };
}

void Prism::SetVerticesArray(std::vector<float>& vertices)
{
    // finds points in a ring around start and end points
    float angleSeparation = 360.0f / numBaseVerts;
    std::vector<float> tempVertices;
    std::vector<int> indicesPattern{0,2,3,3,1,0};
    for (int i = 0; i < numBaseVerts; i++) {
        std::vector<float> startPointAtAngle = MSMaths::FindPointAtAngleDegrees({ startPoint[0], 0.f }, baseRadius, angleSeparation * i);
        std::vector<float> endPointAtAngle = MSMaths::FindPointAtAngleDegrees({ endPoint[0], 0.f }, baseRadius, angleSeparation * i);
        
        tempVertices.push_back(startPointAtAngle[0]);
        tempVertices.push_back(startPoint[1]);
        tempVertices.push_back(startPointAtAngle[1]);
        
        tempVertices.push_back(endPointAtAngle[0]);
        tempVertices.push_back(endPoint[1]);
        tempVertices.push_back(endPointAtAngle[1]);
    }
    for (int i = 0; i < tempVertices.size(); i += 6) {
        if (i != tempVertices.size() - 6) {
            for (int j = 0; j < indicesPattern.size(); j++) {
                vertices.push_back(tempVertices[i + indicesPattern[j] * 3]);
                vertices.push_back(tempVertices[1 + i + indicesPattern[j] * 3]);
                vertices.push_back(tempVertices[2 + i + indicesPattern[j] * 3]);
            }
        }
        else {
            vertices.push_back(tempVertices[i]);
            vertices.push_back(tempVertices[i + 1]);
            vertices.push_back(tempVertices[i + 2]);

            vertices.push_back(tempVertices[0]);
            vertices.push_back(tempVertices[1]);
            vertices.push_back(tempVertices[2]);

            vertices.push_back(tempVertices[3]);
            vertices.push_back(tempVertices[4]);
            vertices.push_back(tempVertices[5]);

            vertices.push_back(tempVertices[3]);
            vertices.push_back(tempVertices[4]);
            vertices.push_back(tempVertices[5]);

            vertices.push_back(tempVertices[i + 3]);
            vertices.push_back(tempVertices[i + 4]);
            vertices.push_back(tempVertices[i + 5]);

            vertices.push_back(tempVertices[i]);
            vertices.push_back(tempVertices[i + 1]);
            vertices.push_back(tempVertices[i + 2]);
        }
    }
}