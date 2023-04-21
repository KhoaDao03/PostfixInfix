#include "bet.h"
#include <iostream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

BET:: BET(){
    root = nullptr;
}

BET::BET(const string& postfix){
   if (buildFromPostfix(postfix)){
        cout << "Successfully built the tree given " << postfix << endl;
   } else {
        cout << "Cannot build the tree" << endl;
   }
}


BET::BET(const BET &rhs) {
    root = clone(rhs.root);
}

BET::~BET() {
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string &postfix){
    
    bool flag = false;
    
    string t;
    BinaryNode* temp = nullptr;
    BinaryNode* temp1 = nullptr;

    stack<BinaryNode*> operands;
    for (auto i : postfix){
        if(i != '+' && i != '-' && i != '*' && i != '/' && i != ' ' ){
            // push the operand into the stack
            t = t + i;
            flag = true;
        } else if (i == ' ' && !flag){
            //continue
            t = "";
        } else if (i == ' ' && flag){
            operands.push(new BinaryNode(t,nullptr, nullptr));
            flag = false;
            t = "";

        } else if ((i == '+' || i == '-' || i == '*' || i == '/') && !flag){
            if (operands.size() >= 2){
                temp = operands.top();
                operands.pop();
                temp1 = operands.top();
                operands.pop();
                string tm(1,i);
                operands.push( new BinaryNode(tm, temp1, temp));
                flag = false;
            } else {
                return false;
            }
        }
    }
    if(operands.size()>0){
        root = operands.top();
        operands.pop();
    }
    
    if (t.size()!=0){
        return false;
    }
    return true;
}

void BET::makeEmpty(BinaryNode* &root){
    if (root != nullptr){
        makeEmpty(root->left);
        makeEmpty(root->right);
        delete root;
    }
}


void BET::printInfixExpression(BinaryNode *n) const{

    bool par = false;   //par for parentheses
    if(!n){
        return;
    }

    if (n->element == "/" ||n->element == "*"){
        if(n->left->element == "+" || n->element == "-"){
            par = true;
        }
    }



    if(par){
        cout << "( ";
    }
    printInfixExpression(n->left);

    if(par){
        cout << ") ";
        par = false;
    }

    cout << n->element << " ";


    if (n->element == "/" ||n->element == "*"){
        if(n->right->element == "+" || n->right->element == "-" 
        || n->right->element == "/" ||n->right->element == "*"){
            par = true;
        }
    }
    if (n->element == "+" ||n->element == "-"){
        if(n->right->element == "+" ||n->right->element == "-"){
            par = true;
        }
    }

    if(par){
        cout << "( ";
    }
    printInfixExpression(n->right);
    if(par){
        cout << ") ";
        par = false;
    }
}


void BET::printInfixExpression() const{
    printInfixExpression(root);
    cout << endl;

}


void BET::printPostfixExpression(BinaryNode *n) const{

    if(n != nullptr){
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";

    }
}

void BET::printPostfixExpression() const{
    printPostfixExpression(root);
    cout << endl;
}

bool BET::empty(){
    return root == nullptr;
}

const BET& BET::operator = (const BET& n){
    if (this != &n) {
        makeEmpty(root);
        root = clone(n.root);
    }
    return *this;
}


size_t BET::size() const{
    return size(root);
}

size_t BET::leaf_nodes() const{
    return leaf_nodes(root);
}

BET::BinaryNode* BET::clone(BinaryNode *t) const{
    if(!t){
        return nullptr;
    } else {
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
}

size_t BET::size(BinaryNode* t) const{
    if (!t){
        return 0;
    } else {
        return 1+ size(t->left) + size(t->right); 
    }
}

size_t BET::leaf_nodes(BinaryNode* t) const{
    if (!t){
        return 0;
    }

    if(t->left == t->right){
        return 1;
    }

    return leaf_nodes(t->left)+leaf_nodes(t->right);
}


