#include <string>
#include <vector>

using namespace std;

struct Node {
public:
    string UFID;
    string name;
    Node *left;
    Node *right;

    Node(string name, string UFID) {
        this->name = name;
        this->UFID = UFID;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree {
private:
    Node* root = nullptr;

    //helper functions to keep memory away from user
    Node* insertHelper(Node* node, string name, string UFID);
    Node* searchIDHelper(Node* node, string UFID);
    void searchNameHelper(Node* node, string name, bool& found);
    vector<Node*> inorder(Node* node, vector<Node*>& result);
    vector<Node*> preorder(Node* node, vector<Node*>& result);
    vector<Node*> postorder(Node* node, vector<Node*>& result);
    bool checkUniqueHelper(Node* node, string UFID);
    Node* removeHelper(Node* node, Node* parent, string UFID);
    void removeInorderHelper(Node *&node, int index);
    int findHeight(Node *node);
    void rotate(Node *&node);
    Node* rotateLeft(Node *node);
    Node* rotateRight(Node *node);
    Node* rotateLeftRight(Node *node);
    Node* rotateRightLeft(Node *node);
    Node* findInorderSuccessor(Node *node, Node*& parent);
public:
    void insert(string name, string UFID);
    string searchID(string UFID);
    void searchName(string name);
    bool checkUnique(string UFID);
    int printLevelCount();
    vector<string> returnTraversal(string traversal);
    void remove(string UFID);
    void removeInorder(int index);
    void deleteNodes(Node* node);

    ~AVLTree();
};
