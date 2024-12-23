#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For random_shuffle
#include <stack>

using namespace std;

const int WIDTH = 15;  // Maze width (odd numbers preferred)
const int HEIGHT = 15; // Maze height (odd numbers preferred)
char maze[HEIGHT][WIDTH];

// Direction vectors for movement (up, down, left, right)
int dx[] = {0, 0, -2, 2};
int dy[] = {-2, 2, 0, 0};

// Player's starting position
int playerX = 1, playerY = 1;

// Function to initialize the maze with walls
void initializeMaze() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            maze[i][j] = '#';  // Represents walls
        }
    }
}

// Function to check if a cell is valid and within bounds
bool isValid(int x, int y) {
    return x > 0 && x < HEIGHT - 1 && y > 0 && y < WIDTH - 1;
}

// Function to generate the maze using Recursive Backtracking
void generateMaze(int x, int y) {
    maze[x][y] = ' '; // Mark current cell as a path

    // Shuffle directions for random movement
    int order[] = {0, 1, 2, 3};
    random_shuffle(order, order + 4);

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[order[i]];
        int ny = y + dy[order[i]];

        // Check if the next cell is valid and surrounded by walls
        if (isValid(nx, ny) && maze[nx][ny] == '#') {
            // Remove the wall between current cell and next cell
            maze[x + dx[order[i]] / 2][y + dy[order[i]] / 2] = ' ';
            // Recur to the next cell
            generateMaze(nx, ny);
        }
    }
}

// Function to display the maze
void displayMaze() {
    system("clear"); // For Linux/macOS; use "cls" for Windows
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == playerY && j == playerX) {
                cout << 'P'; // Player position
            } else {
                cout << maze[i][j];
            }
        }
        cout << endl;
    }
}

// Function to move the player based on input
void movePlayer(char direction) {
    if (direction == 'W' || direction == 'w') {
        if (maze[playerY - 1][playerX] != '#') playerY--;
    } else if (direction == 'S' || direction == 's') {
        if (maze[playerY + 1][playerX] != '#') playerY++;
    } else if (direction == 'A' || direction == 'a') {
        if (maze[playerY][playerX - 1] != '#') playerX--;
    } else if (direction == 'D' || direction == 'd') {
        if (maze[playerY][playerX + 1] != '#') playerX++;
    }
}

int main() {
    srand(time(0));

    initializeMaze();

    // Generate the maze starting from the player's position
    generateMaze(1, 1);

    // Define the starting and ending points
    maze[1][1] = 'S'; // Start point
    maze[HEIGHT - 2][WIDTH - 2] = 'E'; // End point

    char input;

    while (true) {
        displayMaze();

        // Check if the player has reached the end
        if (playerY == HEIGHT - 2 && playerX == WIDTH - 2) {
            cout << "Congratulations! You've reached the exit (E)!" << endl;
            break;
        }

        cout << "Move (W/A/S/D): ";
        cin >> input;
        movePlayer(input);
    }

    return 0;
}
