#include <iostream>
#include <vector>
using namespace std;

void leftFactor(string nt, vector<string> prods) {
    string prefix = prods[0];
    for (string &p : prods)
        while (p.find(prefix) != 0) prefix = prefix.substr(0, prefix.size() - 1);
    
    if (prefix.size() < 2) { // No factoring needed
        cout << nt << " → ";
        for (size_t i = 0; i < prods.size(); i++)
            cout << (i ? " | " : "") << prods[i];
        cout << endl;
        return;
    }

    vector<string> alpha, beta;
    for (string &p : prods)
        (p.find(prefix) == 0 ? alpha : beta).push_back(p.substr(prefix.size()));

    string nt2 = nt + "'";
    cout << nt << " → " << prefix << nt2;
    for (string &b : beta) cout << " | " << b;
    cout << endl << nt2 << " → ";
    for (string &a : alpha) cout << (a.empty() ? "ε" : a) << " | ";
    cout << endl;
}

void removeLeftRecursion(string nt, vector<string> prods) {
    vector<string> alpha, beta;
    for (string &p : prods)
        (p[0] == nt[0] ? alpha : beta).push_back(p.substr(p[0] == nt[0]));

    if (alpha.empty()) return leftFactor(nt, prods);

    string nt2 = nt + "'";
    cout << nt << " → ";
    for (string &b : beta) cout << b << nt2 << " | ";
    cout << endl << nt2 << " → ";
    for (string &a : alpha) cout << a << nt2 << " | ";
    cout << "ε\n";
}

int main() {
    string nt; int n;
    cout << "Enter non-terminal: "; cin >> nt;
    cout << "Enter number of productions: "; cin >> n;
    vector<string> prods(n);
    cout << "Enter productions:\n";
    for (string &p : prods) cin >> p;
    
    removeLeftRecursion(nt, prods);
    return 0;
}
