#include "LSystem.h"

struct data {
    float currentRotation = 0;
    std::vector<float> currentPosition{ 0,0 };
};

std::stack<data> saveLoad;

int recursions = 4;
int count = 0;

const int prismSides = 6;
const float prismBaseWidth = 0.04f;

float theta = 30;

int ruleComplexity = 8;

float currentAngle = 90;
float currentLength = 0.7f;
std::vector<float> currentPosition{0,0};

std::vector<Prism> LSystem::GenLSystem(std::string currentString, std::bitset<7> b, std::vector<Prism> allPrisms)
{
    struct points {
        std::vector<float> startPoint, endPoint;
    };
    // increases recursion count
    count++;

    std::string next = "";

    // checks through current string
    for (int i = 0; i < currentString.size(); i++)
    {
        char c = currentString[i];

        // ruleset
        data d;
        points p;
        switch (c)
        {
        case 'F': {
            next += "FF+l";
            next += b[0] ? "+" : "-";
            next += "F";
            next += b[1] ? "+" : "-";
            next += "F";
            next += b[2] ? "+" : "-";
            next += "Fr";
            next += b[3] ? "+" : "-";
            next += "l";
            next += b[4] ? "+" : "-";
            next += "F";
            next += b[5] ? "+" : "-";
            next += "F";
            next += b[6] ? "+" : "-";
            next += "Fr";
            p.startPoint = currentPosition;
            currentPosition = MSMaths::FindPointAtAngleDegrees(currentPosition, currentLength, currentAngle);
            p.endPoint = currentPosition;
            Prism prism(prismSides, prismBaseWidth, p.startPoint, p.endPoint);
            allPrisms.emplace_back(prism);
            break;
        }
        case '+':
            currentAngle += theta;
            next += '+';
            break;
        case '-':
            currentAngle -= theta;
            next += '-';
            break;
        case 'l':
            d.currentRotation = currentAngle;
            d.currentPosition = currentPosition;
            saveLoad.push(d);
            next += 'l';
            break;
        case 'r':
            d = saveLoad.top();
            saveLoad.pop();
            currentAngle = d.currentRotation;
            currentPosition = d.currentPosition;
            next += 'r';
            break;
        default:
            break;
        }
    }

    // update current
    currentString = next;
    // update current length
    currentLength /= 1.2f;

    // adds recursion
    if (count != recursions)
    {
        allPrisms = GenLSystem(currentString, b, allPrisms);
    }

    count = 0;
    return allPrisms;
}