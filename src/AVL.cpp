#include <iostream>
#include "AVL.h"
#include <vector>

void AVLTree::insert(string name, string UFID) {
    this->root = insertHelper(root, name, UFID);
}

// inspired from module 3 lecture slides
Node* AVLTree::insertHelper(Node *node, std::string name, std::string UFID) {
    if (node == nullptr) {
        cout << "successful" << endl;
        return new Node(name, UFID);
    }
    else if(UFID < node->UFID) {
        node->left = insertHelper(node->left, name, UFID);
    }
    else {
        node->right = insertHelper(node->right, name, UFID);
    }
    // rotates if needed
    rotate(node);
    return node;
}
// searches to find UFID, if not found returns nullptr
Node* AVLTree::searchIDHelper(Node *node, std::string UFID) {
    if (node == nullptr) {
        return nullptr;
    }
    else {
        if (node->UFID == UFID) {
            return node;
        } else if (node->UFID < UFID) {
            return searchIDHelper(node->right, UFID);
        } else if (node->UFID > UFID) {
            return searchIDHelper(node->left, UFID);
        }
    }
    return nullptr;
}

// completes an inorder search to find all the instances where the names are the same
void AVLTree::searchNameHelper(Node *node, std::string name, bool& found) {
    if (node == nullptr) {
        cout << "";
    } else {
        if (node->name == name) {
            cout << node->UFID << endl;
            found = true;
        }
        searchNameHelper(node->left, name, found);
        searchNameHelper(node->right, name, found);
    }
}

// cited from 3 lecture notes
vector<Node*> AVLTree::inorder(Node *node, vector<Node*>& result) {
    if(node == nullptr) {
        cout << "";
    }
    else {
        inorder(node->left, result);
        result.push_back(node);
        inorder(node->right, result);
    }
    return result;
}
// cited from 3 lecture notes
vector<Node*> AVLTree::preorder(Node *node, vector<Node*>& result) {
    if(node == nullptr) {
        cout << "";
    }
    else {
        result.push_back(node);
        preorder(node->left, result);
        preorder(node->right, result);
    }
    return result;
}
// cited from 3 lecture notes
vector<Node*> AVLTree::postorder(Node *node, vector<Node*>& result) {
    if(node == nullptr) {
        cout << "";
    }
    else {
        postorder(node->left,result);
        postorder(node->right,result);
        result.push_back(node);
    }
    return result;
}
// checks if the UFID is unique before inserting
bool AVLTree::checkUniqueHelper(Node* node, std::string UFID) {
    string output = searchID(UFID);
    if (output == "unsuccessful") {
        return true;
    }
    else return false;
}
// finds what traversal the user wants and calls, returns a vector of names
vector<string> AVLTree::returnTraversal(string command) {
    vector<Node*> result;
    vector<string> nameVector;

    if (command == "printInorder") {
        inorder(root, result);
    }
    else if (command == "printPreorder") {
        preorder(root, result);
    }
    else {
        postorder(root, result);
    }
    for (int i = 0; i < int(result.size()); i++) {
        nameVector.push_back(result[i]->name);
    }
return nameVector;
}

// calls the helper function and returns the result to the user
string AVLTree::searchID(string UFID) {
    Node* output = searchIDHelper(root, UFID);
    if(output == nullptr) {
         string result = "unsuccessful";
    }
    else {
        return output->name;
    }
    return "unsuccessful";
}

void AVLTree::searchName(string name) {
    bool nameFound = false;
    searchNameHelper(root, name, nameFound);

    if(!nameFound) {
        cout << "unsuccessful" << endl;
    }
}

bool AVLTree::checkUnique(string UFID) {
    bool isUnique = checkUniqueHelper(root, UFID);
    return isUnique;
}

void AVLTree::remove(string UFID) {
    this->root = removeHelper(root, nullptr, UFID);
}

// pseudocode from Aman module 3 presentation
Node* AVLTree::removeHelper(Node* node, Node* parent, string UFID) {
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    else {
        // calls the function recursively until the UFID matches the node we want to remove
        if (node->UFID < UFID) {
            removeHelper(node->right, node, UFID);
        } else if (node->UFID > UFID) {
            removeHelper(node->left, node, UFID);
        } else {
            cout << "successful" << endl;

            // checks if the node is a leaf node
            if (node->left == nullptr && node->right == nullptr) {
                if (root == node) {
                    root = nullptr;
                    return root;
                } else if (parent->left == node) {
                    parent->left = nullptr;
                    node = nullptr;

                    return node;
                } else if (parent->right == node) {
                    parent->right = nullptr;
                    node = nullptr;
                    return node;
                }
            }
            // checks if the node has 1 child, and determines if it's a left or right child
            else if (node->left == nullptr && node->right != nullptr) {
                if (node == root) {
                    root = node->right;
                    return root;
                }
                else {
                    parent->right = node->right;
                    return parent;
                }
            } else if (node->left != nullptr && node->right == nullptr) {
                if (node == root) {
                    root = node->left;
                    return root;
                }
                else {
                    parent->left = node->left;
                    return parent;
                }
            }
                // if the node has 2 children
            else {
                // if the node->right doesn't have a left child
                if (node->right->left == nullptr) {
                    // seeing if the node's UFID is less than or greater than the parent's UFID
                    if (node == root) {
                        node->right->left = root->left;
                        root = node->right;
                        return root;
                    }
                    if (node->UFID < parent->UFID) {
                        Node *newParent = findInorderSuccessor(node->right, node);
                        newParent->left = node->left;
                        parent->left = newParent;
                        return parent;
                    }
                    else {
                        Node *newParent = findInorderSuccessor(node->right, node);
                        newParent->left = node->left;
                        parent->right = newParent;

                        return parent;
                    }
                } else {
                    if (node == root) {
                        Node *newParent = findInorderSuccessor(node->right, node);
                        string tempUFID = newParent->UFID;
                        string tempName = newParent->name;
                        remove(newParent->UFID);

                        root->UFID = tempUFID;
                        root->name = tempName;
                        return root;
                    }
                    else {
                        Node *newParent = findInorderSuccessor(node->right, node);
                        string tempUFID = newParent->UFID;
                        string tempName = newParent->name;
                        remove(newParent->UFID);

                        node->UFID = tempUFID;
                        node->name = tempName;
                        return node;
                    }
                }
            }
        }
    }
    return node;
}

//finds the height of the root and retuns it
int AVLTree::printLevelCount() {
        return findHeight(root);
}

// inspired by Amam module 3 presentation
int AVLTree::findHeight(Node* node) {
    int height = 1;
    if (node == nullptr) {
        return 0;
    }
    else if (node->left == nullptr && node->right == nullptr){
        return height;
    }
    else {
        int leftHeight = 0;
        int rightHeight = 0;
        if(node->left != nullptr) {
            leftHeight = findHeight(node->left);
        }
        if(node->right != nullptr) {
            rightHeight = findHeight(node->right);
        }
        height = 1 + max(leftHeight, rightHeight);
        return height;
    }
}

// pseudocode from Aman module 4 lecture slides
void AVLTree::rotate(Node *&node) {
    int balanceFactor = 0;
    if (node->right == nullptr && node->left == nullptr) {}
    else {
        balanceFactor = findHeight(node->left) - findHeight(node->right);

        if (balanceFactor == -1 || balanceFactor == 0 || balanceFactor == 1) {}

        // inspired from Aman module 4 lecture slides
        else {
            if (balanceFactor == -2) {
                balanceFactor = findHeight(node->right->left) - findHeight(node->right->right);
                if (balanceFactor == -1) {
                    node = rotateLeft(node);
                }
                else if (balanceFactor == 1) {
                    node = rotateRightLeft(node);
                }
            }
            else if (balanceFactor == 2) {
                balanceFactor = findHeight(node->left->left) - findHeight(node->left->right);
            if (balanceFactor == 1) {
                    node = rotateRight(node);
                }
                else if(balanceFactor == -1){
                    node = rotateLeftRight(node);
                }
            }
        }
    }
}

// from aman module 4 slides
Node *AVLTree::rotateLeft(Node *node) {
    Node* grandchild = node->right->left;
    Node* parent = node->right;
    parent->left = node;
    node->right = grandchild;
    return parent;
}
// inspired by Aman module 4 slides
Node *AVLTree::rotateRight(Node *node) {
    Node* grandchild = node->left->right;
    Node* Parent = node->left;
    Parent->right = node;
    node->left = grandchild;
    return Parent;
}

// inspired by module 4 tree rotation pdf
Node *AVLTree::rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    node = rotateRight(node);
    return node;
}
// inspired by module 4 tree rotation pdf
Node *AVLTree::rotateRightLeft(Node *node) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    return node;
}
// inspired by Aman module 4 slides
Node* AVLTree::findInorderSuccessor(Node *node, Node*& parent) {
    while (node->left != nullptr) {
        parent = node;
        node = node->left;
   }
    return node;
}

void AVLTree::removeInorder(int index) {
    removeInorderHelper(root, index);
}

// does an inorder traversal until it reaches an index, then removes
void AVLTree::removeInorderHelper(Node *&node, int index) {
    vector<Node *> result;

    inorder(node, result);
    if (index + 1 > int(result.size())) {
        cout << "unsuccessful" << endl;
    } else {
        remove(result[index]->UFID);
    }
}

// helper for the destructor
void AVLTree::deleteNodes(Node* node) {
    if (node == nullptr) {
        return;
    }
    else {
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }
}

AVLTree::~AVLTree() {
    deleteNodes(root);
}