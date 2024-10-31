#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include "userInput.h"

using namespace std;

// takes the input and parses it into a vector containing the strings for the function, and UFID and/or Nnode
vector<string> userInput::ParseInput() {
    vector<string> parsedParameters;

    istringstream in(input);
    string command;
    string name;
    string UFID;
    in >> command;
    parsedParameters.push_back(command);

    // determines the function
    if (parsedParameters[0] == "insert") {
        getline(in, name, '"');
        getline(in, name, '"');
        parsedParameters.push_back(name);

        // getting the UFID from the user inputted line
        getline(in, UFID, ' ');
        getline(in, UFID);
        parsedParameters.push_back(UFID);
    }

    else if(parsedParameters[0] == "remove") {
        getline(in, UFID, ' ');
        getline(in, UFID);
        parsedParameters.push_back(UFID);
    }

    else if(parsedParameters[0] == "search") {
        string next;
        getline(in, next, ' ');
        getline(in, next);
        parsedParameters.push_back(next);
    }

    else if(parsedParameters[0] == "removeInorder") {
        string stringIndex;
        getline(in, stringIndex, ' ');
        getline(in, stringIndex);
        parsedParameters.push_back(stringIndex);
    }
    return parsedParameters;
};

//checks if all the characters in the name are alpha
bool userInput::checkValidName(string name){
    for(auto j : name) {
        if(!(isalpha(j) || j == ' ')) {
            return false;
        }
    }
    return true;
}

// checks that the UFID is numerical and has 8 digits
bool userInput::checkValidUFID(string UFID){
    if (UFID.length() != 8) {
        return false;
    }
    else{
        for(auto j : UFID) {
            if(!isdigit(j)) {
                return false;
            }
        }
    }
    return true;
}

// checks that all the inputted parameters are valid
bool userInput::checkValidParameters(string name, string UFID, bool isInsert) {
    if (checkValidName(name) && checkValidUFID(UFID) && isInsert) return true;
    else if (name.empty() && checkValidUFID(UFID) && !isInsert) return true;
    else if (checkValidName(name) && UFID.empty() && !isInsert) return true;
    return false;
}

