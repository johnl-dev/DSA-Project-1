#include <string>
#include <vector>

using namespace std;

class userInput {
public:
    string input;
    vector<string> output;
    userInput(string input) {
        this->input = input;
    }

    vector<string> ParseInput();
    bool checkValidName(string name);
    bool checkValidParameters(string name, string UFID, bool isInsert);
    bool checkValidUFID(string UFID);
};
