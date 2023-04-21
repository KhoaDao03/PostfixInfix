#include <iostream>
#include <string>
#include "bet.h"

using namespace std;

int main() {
    string postfix;

    // get a postfix expression
    cout << "Enter the first postfix expression: ";
    getline(cin, postfix);

    // create a binary expression tree
    BET bet1(postfix);

    bet1.printInfixExpression();
    cout << endl;
    bet1.printPostfixExpression();
    cout << endl;
    return 0;
}
