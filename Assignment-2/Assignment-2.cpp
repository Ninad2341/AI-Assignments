#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// List of all states to color
vector<string> stateList = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};

// Neighbouring relationships
map<string, vector<string>> neighbours = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q", {"NT", "SA", "NSW"}},
    {"NSW", {"Q", "SA", "V"}},
    {"V", {"SA", "NSW", "T"}},
    {"T", {"V"}}};

// Allowed colors
vector<string> availableColors = {"Red", "Green", "Blue"};

// Check if assigning color is valid
bool canColor(string currentState, string chosenColor, map<string, string> &stateColor)
{
    for (string nb : neighbours[currentState])
    {
        if (stateColor[nb] == chosenColor)
            return false; // neighbour already has same color → bad
    }
    return true; // safe to use this color
}

// Try coloring using backtracking
bool assignColor(int stateIndex, map<string, string> &stateColor)
{
    if (stateIndex == stateList.size())
        return true; // all states colored

    string currentState = stateList[stateIndex];

    for (string chosenColor : availableColors)
    {
        if (canColor(currentState, chosenColor, stateColor))
        {
            stateColor[currentState] = chosenColor; // choose color

            if (assignColor(stateIndex + 1, stateColor)) // go to next state
                return true;

            stateColor[currentState] = ""; // undo (backtrack)
        }
    }
    return false; // nothing worked → backtrack
}

int main()
{
    map<string, string> stateColor;

    for (string s : stateList)
        stateColor[s] = ""; // initially no colors assigned

    if (assignColor(0, stateColor))
    {
        cout << "Solution Found:\n";
        for (string s : stateList)
            cout << s << " -> " << stateColor[s] << endl;
    }
    else
        cout << "No solution possible.\n";

    return 0;
}
