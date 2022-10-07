#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> front(9, vector<bool>(9)), back(9, vector<bool>(9)), frontTmp(9, vector<bool>(9)), backTmp(9, vector<bool>(9));
int nDominos;

struct dominoT {
    int leftDots;
    int rightDots;
};

bool FormsDominoChain(vector<dominoT> & dominos);
bool valid(int& firstPart, int& secondPart);
void rebuild();
void recur(int i, int j, bool face, vector<char> container);

int main() {
    vector<dominoT> dominoSet;
    cout << "Enter the number of dominos: ";
    cin >> nDominos;
    dominoSet.resize(nDominos);
    for (int i = 1; i <= nDominos; ++i) {
        int firstPart, secondPart;
        while (true){
            cout << "Enter the domino (digit|digit) of number " << i << ": ";
            cin >> firstPart >> secondPart;
            if(valid(firstPart, secondPart)){
                dominoT newDomino;
                newDomino.leftDots = (firstPart);
                newDomino.rightDots = (secondPart);
                dominoSet[i-1] = newDomino;
                break;
            }
            cout << "Enter correct format!\n";
        }
    }
    cout << (FormsDominoChain(dominoSet) ? "YES" : "NO");
}

bool valid(int& firstPart, int& secondPart){
    return (firstPart >= 0 && firstPart <= 6 && secondPart >=0 && secondPart <= 6);
}

void rebuild(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            front[i][j] = frontTmp[i][j];
            back[i][j] = backTmp[i][j];
        }
    }
}

bool FormsDominoChain(vector<dominoT> & dominos){
    for(auto val : dominos){
        frontTmp[val.leftDots][val.rightDots] = 1;
        backTmp[val.rightDots][val.leftDots] = 1;
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(frontTmp[i][j]){
                rebuild();
                recur(i, j, 0, {char(i + '0'),char(j + '0')});
            }
            if(backTmp[i][j]){
                rebuild();
                recur(i, j, 1, {char(i + '0'),char(j + '0')});
            }
        }
    }
    return false;
}

void recur(int i, int j, bool face, vector<char> container){
    if(container.size() - 1 == nDominos){
        cout << "YES\n";
        cout << container[0] << '|' << container[1];
        char lst = container[1];
        for (int k = 2; k <= nDominos; ++k) {
            cout << " - " << lst << '|' << container[k];
            lst = container[k];
        }
        exit(0);
    }
    if(!face){
        front[i][j] = 0;
        back[j][i] = 0;
    }else{
        back[i][j] = 0;
        front[j][i] = 0;
    }

    for (int k = 0; k < 9; ++k) {
        if(front[j][k]){
            container.push_back(char(k + '0'));
            recur(j, k, 0, container);
            container.pop_back();
        }
        if(back[j][k]){
            container.push_back(char(k + '0'));
            recur(j, k, 1,container);
            container.pop_back();
        }
    }
    if(!face){
        front[i][j] = 1;
        back[j][i] = 1;
    }else{
        back[i][j] = 1;
        front[j][i] = 1;
    }
}