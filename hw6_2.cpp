/*
 * Title: hw6_2.cpp
 * Abstract: This program collects maximum number of coins on an n x m board.
 * Author: Justin Mello
 * ID: 2002
 * Date: 04/20/2021
*/

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

static int FILL = 2;
static int EMPTY = -1;

struct coinStruct {
    int max = 0;
    vector<vector<int> > board;
};

coinStruct cResults(vector<vector<int>> coin) {
    int width = coin.size();
    int height = coin[0].size();
    
    vector<vector<int>> side(width, vector<int>(height));

    side[1, 1] = coin[1, 1];
    
    for (int i = 2; i < side[0].size(); i++) {
        if (coin[1][i] == FILL) {
            side[1][i] = EMPTY;
        } else {
            if (side[1][i - 1] == EMPTY)
                side[1][i] = EMPTY;
            else
                side[1][i] = side[1][i - 1] + coin[1][i];
        }
    }

    for (int j = 2; j < side.size(); j++) {

        if (coin[j][1] == FILL) {
            side[j][1] = EMPTY;
        } else {

            if (side[j - 1][1] == EMPTY)
                side[j][1] = EMPTY;
            else
                side[j][1] = side[j - 1][1] + coin[j][1];
        }


        for (int k = 2; k < side[0].size(); k++) {
            if (coin[j][k] == FILL) {
                side[j][k] = EMPTY;
            } else {
                side[j][k] = max(side[j - 1][k], side[j][k - 1]) + coin[j][k];
            }
        }
    }


    int row = coin.size() - 1;
    int col = coin[0].size() - 1;
    coinStruct results;
    results.max = side[row][col];
    results.board = side;
    return results;
}

vector<pair<int, int>> returnPath(vector<vector<int>> vec) {
    vector<pair<int, int>> path;
    int i = vec[0].size() - 1;
    int j = vec.size() - 1;

    while (true) {
        path.push_back(make_pair(i, j));

        if (i > 1 && j > 1) {
            if (vec[j - 1][i] > vec[j][i - 1]) {
                j--;
            } else {
                i--;
            }
        } else if (j > 1) {
            if (vec[j - 1][i] >= vec[j][i - 1])
                j--;
        } else if (i > 1) {
            if (vec[j - 1][i] <= vec[j][i - 1])
                i--;
        } else {
            break;
        }
    }
    return path;
}

int main() {

    vector<vector<int>> coinBoard;
    int height = 0;
    int width = 0;

    //Gather input
    cin >> height;
    cin >> width;
    height++;
    width++;

    coinBoard.resize(width, vector<int>(height));

    for (int i = 1; i < coinBoard.size(); i++) {
        for (int j = 1; j < coinBoard[i].size(); j++) {
            cin >> coinBoard[i][j];
        }
    }

    coinStruct results = cResults(coinBoard);
    vector<pair<int, int>> path = returnPath(results.board);

    //Display
    cout << "Max coins:" << results.max << endl;
    cout << "Path:" << "(" << path[path.size() - 1].first << "," << path[path.size() - 1].second << ")";

    for (int x = path.size() - 2; x >= 0; x--) {
        cout << "->" << "(" << path[x].first << "," << path[x].second << ")";
    }
    cout << endl;

    return 0;
}


