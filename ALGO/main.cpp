#include <iostream>
#include <vector>

using namespace std;

void init_tan(vector<vector<int>> &tan, const vector<vector<int>> &coor) {    
    for (auto &i : coor)
        tan[i[1]][i[0]] = 0;
}

typedef enum {
    ALL = 0,
    LEFT_TOP,
    LEFT_BOT,
    RIGHT_TOP,
    RIGHT_BOT = 4,
} MODE;

int count = 1, check = 0;

void fill(vector<vector<int>> &tan, int x1, int x2, int y1, int y2, MODE mode) {
    if ((x2 - x1) == 1) {
        if (tan[y1][x1] && tan[y1][x2] && tan[y2][x1] && tan[y2][x2]) {
            tan[y1][x1] = (mode == RIGHT_BOT) ? count + 1 : count;
            tan[y1][x2] = (mode == LEFT_BOT) ? count + 3 : count;
            tan[y2][x1] = (mode == RIGHT_TOP) ? count + 2 : count;
            tan[y2][x2] = (mode == LEFT_TOP) ? count + 4 : count;

            if (mode == RIGHT_BOT) {
                check = 0;
                count += 2;
            }
            else {
                check = 1;
                count++;
            }

            return;
        }

        tan[y1][x1] = tan[y1][x1] ? count : 0;
        tan[y1][x2] = tan[y1][x2] ? count : 0;
        tan[y2][x1] = tan[y2][x1] ? count : 0;
        tan[y2][x2] = tan[y2][x2] ? count : 0;

        if (mode == RIGHT_BOT && check) {
            count += 2;
            check = 0;
        }
        else 
            count++;

        return;
    }

    fill(tan, x1                 , (x1 + x2) / 2, y1                 , (y1 + y2) / 2, LEFT_TOP);
    fill(tan, x1                 , (x1 + x2) / 2, ((y1 + y2) / 2) + 1, y2           , LEFT_BOT);
    fill(tan, ((x1 + x2) / 2) + 1, x2           , y1                 , (y1 + y2) / 2, RIGHT_TOP);
    fill(tan, ((x1 + x2) / 2) + 1, x2           , ((y1 + y2) / 2) + 1, y2           , RIGHT_BOT);
}

void print_tan(const vector<vector<int>> &tan) {
    for (auto &i : tan) {
        auto j = i.begin();
        for (; j < i.end() - 1; j++)
            cout << j[0] << ' ';
        
        cout << j[0] << endl;
    }
}

int main(void) {
    int numOfDefect, lenOfTan;
    cin >> numOfDefect >> lenOfTan;

    vector<vector<int>> coor(numOfDefect, vector<int>(2));
    for (auto &i : coor)
        cin >> i[0] >> i[1];

    vector<vector<int>> tan(lenOfTan, vector<int>(lenOfTan, 1));
    init_tan(tan, coor);

    fill(tan, 0, lenOfTan - 1, 0, lenOfTan - 1, ALL);

    print_tan(tan);

    return 0;
}