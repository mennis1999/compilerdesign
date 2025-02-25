#include <iostream>
#include <vector>
using namespace std;

void removeLeftRecursion(string nonTerminal, vector<string> productions) {
    vector<string> alpha, beta;
    for (string prod : productions) {
        if (prod[0] == nonTerminal[0])
            alpha.push_back(prod.substr(1)); // Store α (recursive part)
        else
            beta.push_back(prod);            // Store β (non-recursive part)
    }

    if (alpha.empty()) { // No left recursion
        cout << nonTerminal << " → ";
        for (size_t i = 0; i < productions.size(); i++) {
            if (i > 0) cout << " | ";
            cout << productions[i];
        }
        cout << endl;
        return;
    }

    // Print transformed grammar
    string newNT = nonTerminal + "'";
    cout << nonTerminal << " → ";
    for (size_t i = 0; i < beta.size(); i++) {
        if (i > 0) cout << " | ";
        cout << beta[i] << newNT;
    }
    cout << endl;

    cout << newNT << " → ";
    for (size_t i = 0; i < alpha.size(); i++)
        cout << alpha[i] << newNT << " | ";
    cout << "ε\n";
}

int main() {
    string nonTerminal;
    int n;
    cout << "Enter non-terminal: ";
    cin >> nonTerminal;
    cout << "Enter number of productions: ";
    cin >> n;

    vector<string> productions(n);
    cout << "Enter productions (without spaces):\n";
    for (int i = 0; i < n; i++)
        cin >> productions[i];

    removeLeftRecursion(nonTerminal, productions);
    return 0;
}
