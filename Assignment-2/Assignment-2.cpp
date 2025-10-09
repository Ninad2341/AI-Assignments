#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

vector<string> states = {
    "WA",
    "NT",
    "SA",
    "Q",
    "NSW",
    "V",
    "T"};

map<string, vector<string>> adj = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q", {"NT", "SA", "NSW"}},
    {"NSW", {"Q", "SA", "V"}},
    {"V", {"SA", "NSW", "T"}},
    {"T", {"V"}}};

vector<string> colors = {"Red", "Green", "Blue"};

// Function to check if it's safe to assign a color to a state
bool isSafe(string state, string color, map<string, string> &coloring)
{
    for (string neighbor : adj[state])
    {
        if (coloring[neighbor] == color)
        {
            return false; // Adjacent state has same color
        }
    }
    return true;
}

// Backtracking function
bool colorMap(int index, map<string, string> &coloring)
{
    if (index == states.size())
    {
        return true; // All states colored
    }

    string state = states[index];
    for (string color : colors)
    {
        if (isSafe(state, color, coloring))
        {
            coloring[state] = color; // Assign color

            if (colorMap(index + 1, coloring))
            {
                return true;
            }

            coloring[state] = ""; // Backtrack
        }
    }
    return false; // No valid color found
}

int main()
{
    map<string, string> coloring;

    // Initialize all states with no color
    for (string state : states)
    {
        coloring[state] = "";
    }

    if (colorMap(0, coloring))
    {
        cout << "Map Coloring Solution:\n";
        for (string state : states)
        {
            cout << state << " -> " << coloring[state] << "\n";
        }
    }
    else
    {
        cout << "No solution found.\n";
    }

    return 0;
}
