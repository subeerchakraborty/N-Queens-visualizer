#include <iostream>
#include <vector>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int N;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void printBoard(const vector<int>& positions, int currentRow, int currentCol) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (row < currentRow) {
                if (positions[row] == col)
                    cout << "Q ";
                else
                    cout << ((row + col) % 2 == 0 ? ". " : "# ");
            } else if (row == currentRow) {
                if (col == currentCol)
                    cout << "X ";
                else
                    cout << ((row + col) % 2 == 0 ? ". " : "# ");
            } else {
                cout << ((row + col) % 2 == 0 ? ". " : "# ");
            }
        }
        cout << endl;
    }
}

bool isSafe(const vector<int>& positions, int row, int col) {
    for (int i = 0; i < row; ++i) {
        int otherCol = positions[i];
        if (otherCol == col || abs(otherCol - col) == abs(i - row))
            return false;
    }
    return true;
}

void solveNQueens(vector<int>& positions, int row) {
    if (row == N) {
        clearScreen();
        cout << "Solution Found:" << endl;
        printBoard(positions, N, -1);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    for (int col = 0; col < N; ++col) {
        clearScreen();
        cout << "Trying column " << col + 1 << " in row " << row + 1 << endl;
        printBoard(positions, row, col);
        delay(500);

        if (isSafe(positions, row, col)) {
            positions[row] = col;
            clearScreen();
            cout << "Queen placed at row " << row + 1 << ", column " << col + 1 << endl;
            printBoard(positions, row + 1, -1);
            delay(500);

            solveNQueens(positions, row + 1);

            positions[row] = -1; // Backtrack
            clearScreen();
            cout << "Backtracking from row " << row + 1 << endl;
            printBoard(positions, row, -1);
            delay(500);
        }
    }
}

int main() {
    cout << "Enter the number of queens (N): ";
    cin >> N;

    vector<int> positions(N, -1);

    clearScreen();
    solveNQueens(positions, 0);

    return 0;
}