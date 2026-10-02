#include <iostream>
#include <utility> // for pair
#include <math.h> // for hypot
#include <cstdlib> // for exit
#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

char quit = 'Q';

pair<int, int> mapSize = {10, 10}; // .first -> y .second -> x
    pair<size_t, size_t> player = {0, 0};
    pair<size_t, size_t> goal = {9, 9};
    char distancestate[] = {'N','W','E','S'};
    string stringdist[] = {"NORTH","WEST","EAST","SOUTH"};

enum Directions {
    NORTH,
    WEST,
    EAST,
    SOUTH
};

inline static const unordered_map<string, Directions> directionMap = {
        {"NORTH", NORTH},
        {"WEST", WEST},
        {"EAST", EAST},
        {"SOUTH", SOUTH}
};

// This is a char case-insensitive function, which takes 2 chars, lowers and compares them.
bool checkch(char& ch1, char& ch2){
        if(char(tolower(ch1)) != char(tolower(ch2))){
            return false;
        }
    return true;
}

void movePair(pair<size_t, size_t>& position, Directions direction, uint16_t distance) {
    switch (direction){
    case NORTH:
        if (position.second - distance < mapSize.first) {
            position.second -= distance;
        } else {
            cout << "Invalid move" << endl;
        }
        break;
    case WEST:
        if (position.first - distance >= 0) {
            position.first -= distance;
        } else {
            cout << "Invalid move" << endl;
        }
        break;

    case EAST:
        if (position.first + distance < mapSize.second) {
            position.first += distance;
        } else {
            cout << "Invalid move" << endl;
        }
        break;

    case SOUTH:
        if (position.second + distance >= 0) {
            position.second += distance;
        } else {
            cout << "Invalid move" << endl;
        }
        break;

    default:
        cout << "Invalid direction" << endl;
        break;
    }
}

pair<Directions, uint16_t> printAllOptions(){
    char direction;
    uint16_t distance;
    uint8_t counter = 0;


    cout << "State movement direction (N|W|E|S) + the amount to move or (Q) to quit: ";
    cin >> direction;
    Directions parsedDirection;   
    
    if(checkch(direction, quit)){
        throw runtime_error("exit case used");
    }
    
    // By mapping the enums you could create an array of strings then bind them.
    for(uint8_t i = 0u; i<stringdist->length();i++){        
        if(checkch(direction, distancestate[i])){
            parsedDirection = directionMap.at(stringdist[i]);
        } else {
            counter += 1u;
            if (counter >= stringdist->length()){
                    cout << "Invalid direction" << endl;
                return {NORTH, 0};
            }
        }
    }
    
    cin >> distance;
    pair<Directions, uint16_t> move = {parsedDirection, distance};
    return move;
}

int main() {
    string sPlayer = " @ ";
    string sGoal = " X ";
    string sEmpty = " * ";

    double distanceToGoal = -1;
    // main game cycle
    for(;;) {
        if(player == goal){
            cout << "YOU WIN!!" << endl;
            break;
        }
        for (size_t y = 0; y < mapSize.first; y++) {
            for (size_t x = 0; x < mapSize.second; x++){
                pair<size_t, size_t> mapPos = {x, y};
                if(mapPos == player){
                    cout << sPlayer;
                    continue;
                } else if(mapPos == goal){
                    cout << sGoal;
                    continue;
                } else {
                    cout << sEmpty;
                    continue;
                }
            }
            cout << endl;
        }
        pair<Directions, uint16_t> move;
        try {
            move = printAllOptions();
        }
        catch(const runtime_error& e){
            return 0;
        }
        movePair(player, move.first, move.second);
        distanceToGoal = hypot(goal.first - player.first, goal.second - player.second);
    }
    return 0;
}
