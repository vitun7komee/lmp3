#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 15;
const int WALL = 0;
const int OPEN = 1;

int start_i, start_j, end_i, end_j;

void generateMaze(int maze[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = WALL;
        }
    }

    //start_i = 0;
    //start_j = 0;
    //end_i = 14;
    //end_j = 14;
    
    // Генерируем проходы случайным образом
    srand(time(nullptr));
    start_i = rand() % SIZE;
    start_j = rand() % SIZE;
    end_i = rand() % SIZE;
    end_j = rand() % SIZE;
    maze[start_i][start_j] = OPEN;
    maze[end_i][end_j] = OPEN;

    // Проводим крысу из стартовой точки к конечной, случайным образом открывая проходы
    int i = start_i, j = start_j;
    while (i != end_i || j != end_j) {
        if (rand() % 2 == 0) {
            if (i < end_i) i++;
            else if (i > end_i) i--;
        }
        else {
            if (j < end_j) j++;
            else if (j > end_j) j--;
        }
        maze[i][j] = OPEN;
    }
}
// Вывод лабиринта
void printMaze(int maze[][SIZE], int row, int col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == row && j == col) cout << "R ";
            else if (maze[i][j] == WALL) cout << "X ";
            else if (maze[i][j] == OPEN) cout << "  ";
        }
        cout << endl;
    }
}

bool solveMaze(int maze[][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false; // если вышли за границы лабиринта
    if (maze[row][col] == WALL) return false; // если попали в стену
    maze[row][col] = OPEN;
    printMaze(maze, row, col);
    if (row == end_i && col == end_j) {
        // если это конечная точка
        return false;
    }
    char c;
    cin >> c;
    c = tolower(c); 
    if (c == 'w') {
        if (solveMaze(maze, row - 1, col)) return true;
    }
    else if (c == 'a') { 
        if (solveMaze(maze, row, col - 1)) return true;
    }
    else if (c == 's') {
        if (solveMaze(maze, row + 1, col)) return true;
    }
    else if (c == 'd') {
        if (solveMaze(maze, row, col + 1)) return true;
    }
    return false;
}

int main() {
    int maze[SIZE][SIZE];
    generateMaze(maze);
    cout << "Select the direction of travel using the keyboard (WASD).\n";
    solveMaze(maze, start_i, start_j);
    return 0;
}