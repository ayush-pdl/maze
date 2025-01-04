#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <algorithm> // For random_shuffle

using namespace std;

const int WIDTH = 15;  // Maze width (odd numbers preferred)
const int HEIGHT = 15; // Maze height (odd numbers preferred)
char maze[HEIGHT][WIDTH];

// Direction vectors for maze generation (up, down, left, right)
int dx[] = { 0, 0, -2, 2 };
int dy[] = { -2, 2, 0, 0 };

// Player's starting position
int playerX = 1, playerY = 1;

// Enemy definition
struct Enemy {
    int x, y;

    void moveRandomly() {
        int direction = rand() % 4; // Random direction: 0 = up, 1 = down, 2 = left, 3 = right
        int nx = x, ny = y;

        if (direction == 0 && maze[y - 1][x] == ' ') ny--;
        else if (direction == 1 && maze[y + 1][x] == ' ') ny++;
        else if (direction == 2 && maze[y][x - 1] == ' ') nx--;
        else if (direction == 3 && maze[y][x + 1] == ' ') nx++;

        if (maze[ny][nx] == ' ') { // Move only to empty spaces
            x = nx;
            y = ny;
        }
    }
};

Enemy enemies[3]; // Example with 3 enemies

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
    int order[] = { 0, 1, 2, 3 };
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

// Function to initialize enemy positions
void initializeEnemies() {
    for (int i = 0; i < 3; i++) {
        do {
            enemies[i].x = rand() % (WIDTH - 2) + 1;
            enemies[i].y = rand() % (HEIGHT - 2) + 1;
        } while (maze[enemies[i].y][enemies[i].x] != ' '); // Place enemies only on empty cells
    }
}

// Move all enemies randomly
void moveEnemies() {
    for (int i = 0; i < 2; i++) {
        enemies[i].moveRandomly();
    }
}

// Check collision between player and enemies
bool checkCollision() {
    for (int i = 0; i < 3; i++) {
        if (enemies[i].x == playerX && enemies[i].y == playerY) {
            cout << "You've been caught by an enemy!" << endl;
            return true;
        }
    }
    return false;
}

//function to render the maze at same position without clearing the screen
void moveCursorTo(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);
}

// Function to display the maze
void displayMaze() {
    moveCursorTo(0, 0); // Move cursor to the top-left corner of the terminal
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == playerY && j == playerX) {
                cout << 'P'; // Player position
            }
            else {
                bool isEnemy = false;
                for (int k = 0; k < 2; k++) {
                    if (i == enemies[k].y && j == enemies[k].x) {
                        cout << '*'; // Enemy position
                        isEnemy = true;
                        break;
                    }
                }
                if (!isEnemy) {
                    cout << maze[i][j];
                }
            }
        }
        cout << endl;
    }
}

//function to solve puzzles 
bool solvePuzzle() {
    int answer;
    cout << "Solve this puzzle to unlock the door: \n";
    cout << "What is 7 + 5? ";
    cin >> answer;

    if (answer == 12) {
        cout << "Correct! The door is unlocked.\n";
        return true;
    }
    else {
        cout << "Incorrect! Try again.\n";
        return false;
    }
}



//function to place puzzle solving doors randomly
void placeRandomDoors(int numberOfDoors) {
    for (int i = 0; i < 3; i++) {
        int x, y;
        do {
            x = rand() % (WIDTH - 2) + 1; // Random X coordinate (within maze boundaries)
            y = rand() % (HEIGHT - 2) + 1; // Random Y coordinate (within maze boundaries)
        } while (maze[y][x] != ' '); // Ensure the chosen cell is an empty path

        maze[y][x] = 'D'; // Place a door at the chosen position
    }
}

bool solveMathPuzzle() {
    int answer;
    cout << "Solve this math puzzle: What is 8 x 6? ";
    cin >> answer;
    return answer == 48;
}

bool solveLogicPuzzle() {
    char answer;
    cout << "True or False: All squares are rectangles. (t/f) ";
    cin >> answer;
    return answer == 't' || answer == 'T';
}

bool solveRiddle() {
    string answer;
    cout << "I speak without a mouth and hear without ears. Who am I? ";
    cin >> answer;
    return answer == "echo" || answer == "Echo";
}

bool solveWordScramble() {
    string answer;
    cout << "Unscramble this word: ELZPUZ ";
    cin >> answer;
    return answer == "PUZZLE" || answer == "puzzle";
}

bool solveRandomPuzzle() {
    int choice = rand() % 4; // Randomly pick a puzzle type
    if (choice == 0) return solveMathPuzzle();
    if (choice == 1) return solveLogicPuzzle();
    if (choice == 2) return solveRiddle();
    if (choice == 3) return solveWordScramble();
    return false; // Default, should not happen
}


// Function to move the player based on input
void movePlayer(char direction) {
    int newX = playerX, newY = playerY;

    if (direction == 'W' || direction == 'w') newY--;
    else if (direction == 'S' || direction == 's') newY++;
    else if (direction == 'A' || direction == 'a') newX--;
    else if (direction == 'D' || direction == 'd') newX++;

    if (maze[newY][newX] == ' ') {
        // Move to an empty path
        playerX = newX;
        playerY = newY;
    }
    else if (maze[newY][newX] == 'D') {
        // Encounter a door
        if (solveRandomPuzzle()) {
            cout << "The door is unlocked!\n";
            maze[newY][newX] = ' '; // Unlock the door
            playerX = newX;
            playerY = newY;
        }
        else {
            cout << "The door remains locked.\n";
        }
    }
    else {
        // Encounter a wall
        cout << "You can't move there!\n";
    }
}



int main() {
    srand(time(0));

    initializeMaze();
    generateMaze(1, 1);

    // Define the starting and ending points
    maze[1][1] = 'S'; // Start point
    maze[HEIGHT - 2][WIDTH - 2] = 'E'; // End point

    //placing random doors for puzzle solving in the maze
    placeRandomDoors(2);

    initializeEnemies();

    char input = ' ';// initialize with a default value

    while (true) {
        displayMaze();

        // Check for win condition
        if (playerY == HEIGHT - 2 && playerX == WIDTH - 2) {
            cout << "Congratulations! You've reached the exit (E)!" << endl;
            break;
        }


        // Detect and process player input without Enter button
        if (_kbhit()) {
            input = _getch();
            movePlayer(input); // Process player movement
        }

        // Prompt for player input
        //cout << "Move (W/A/S/D): ";
        //cin >> input;
        //movePlayer(input); // Process player movement

        // Move enemies after player move
        moveEnemies();

        // Check for collision
        if (checkCollision()) {
            cout << "Game Over!" << endl;
            break;
        }
        // Add delay to prevent excessive loop speed
        Sleep(100); // 100 ms delay
    }

    return 0;
}


