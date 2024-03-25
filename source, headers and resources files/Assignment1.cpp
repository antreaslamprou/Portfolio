//Author: Antreas Lamprou
//GNumber: G21070510
//This project purpose is to guide Theseus to the Minotaur through a provided maze. If there is a possiple path and 
//Theseus defeats Minotaur (70% chance) then the path for the Theseus return is printed to the console.


//Includes libraries 
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

#define MAX_SIZE 100 //Max Stack size

#include "Stack.h" //Includes header

using namespace std; //Use the namespace

//Coordinates structure of X and Y
typedef struct Coordinates {
    unsigned short row; 
    unsigned short column;

    //Prints the coordination
    void print() {
        cout << "(" << row << ", " << column << ") " << endl;
    }

    //Prints the coordination for Theseus
    void printT() {
        cout << "(" << row << ", " << column << ") " << "T" << endl;
    }

    //Prints the coordination for Minotaur
    void printM() {
        cout << "(" << row << ", " << column << ") " << "M" << endl;
    }
};

//Maze structure of the maze 
typedef struct Maze {
    char** maze; 
    unsigned short rows; 
    unsigned short columns;
    unsigned short walls;
    unsigned short corridors;
    Coordinates theseus;
    Coordinates minotaur;

    void printMaze() {
        //Makes the upper frame
        cout << "+";
        for (int i = 0; i < columns; i++) {
            cout << "..";
        }
        cout << "+" << endl;

        //Prints the 2d maze
        for (int i = rows - 1; i >= 0; i--) {
            cout << '|';
            for (int j = 0; j < columns; j++) {
                if (maze[i][j] == 'M') { //If its the minotaur
                    cout << "M ";
                }
                else if (maze[i][j] == 'T') { //If its the theseus
                    cout << "T ";
                }
                else if (maze[i][j] == 'W') { //if is a wall
                    cout << "W ";
                    walls += 1;
                }
                else if (maze[i][j] == '0') { //if is an empty space
                    cout << "  ";
                    corridors += 1;
                }
            }
            cout << '|' << endl;
        }

        //Makes the lower frame
        cout << "+";
        for (int i = 0; i < columns; i++) {
            cout << "..";
        }
        cout << "+" << endl;

        //Prints the maze details
        cout << "Theseus: ";
        theseus.print();
        cout << "Minotaur: ";
        minotaur.print();
        cout << "Number of walls: " << walls << endl;
        cout << "Number of corridors: " << corridors << endl << endl;
    }
};

//Maze solver structure
typedef struct MazeSolver {
    
    Maze* maze;

    MazeSolver(Maze* givenMaze) {
        maze = givenMaze;
    }

    unsigned short steps = 0;

    //Creates a stack for Theseus path
    Stack<Coordinates> path;

    //Finds the path to the minotaur
    bool findMinotaur(Maze* maze) {
        
        path.push(maze->theseus); //Adds starting position to Stack

        while (!path.isEmpty()) //While there are available paths
        {
            Coordinates pos = path.top();
            maze->maze[pos.row][pos.column] = 'V';

            //If Theseus finds Minotaur
            if (pos.row == maze->minotaur.row && pos.column == maze->minotaur.column) {
                cout << "Minotaur Found!!! There is a valid path: " << endl;
               
                //Starts printing the stack from the base till top
                for (int i = 0; i < path._top; i++) {
                    if (i == 0) path._data[i].printT();
                    else if (i == path._top - 1) path._data[i].printM();
                    else path._data[i].print();
                }
                cout << endl;
                return true;
            }
            else {

                //Checks Upwards
                if (pos.row + 1 < maze->rows && (maze->maze[pos.row + 1][pos.column] == '0' || maze->maze[pos.row + 1][pos.column] == 'M'))
                {
                    pos.row += 1;
                    maze->maze[pos.row][pos.column] = 'V';
                    path.push(pos);
                    steps += 1;
                }

                //Checks Rightwards
                else if (pos.column + 1 < maze->columns && (maze->maze[pos.row][pos.column + 1] == '0' || maze->maze[pos.row][pos.column + 1] == 'M'))
                {
                    pos.column += 1;
                    maze->maze[pos.row][pos.column] = 'V';
                    path.push(pos);
                    steps += 1;
                }

                //Checks Leftwarads
                else if (pos.column != 0 && (maze->maze[pos.row][pos.column - 1] == '0' || maze->maze[pos.row][pos.column - 1] == 'M'))
                {
                    pos.column -= 1;
                    maze->maze[pos.row][pos.column] = 'V';
                    path.push(pos);
                    steps += 1;
                }

                //Checks Downwards
                else if (pos.row != 0 && (maze->maze[pos.row - 1][pos.column] == '0' || maze->maze[pos.row - 1][pos.column] == 'M'))
                {
                    pos.row -= 1;
                    maze->maze[pos.row][pos.column] = 'V';
                    path.push(pos);
                    steps += 1;
                }

                //Dead end
                else {
                    maze->maze[pos.row][pos.column] = 'W';
                    path.pop();
                    continue;
                }
            }
        }
        cout << "Path not found!!!" << endl << endl;
        return false;
    }

    //Theseus tries to defeat Minotaur
    bool defeatMinotaur() {
        cout << "Trying to defeat the Minotaur (Chance to defeat: 70%)" << endl;

        //70% chance to win minotaur
        if ((1 + (rand() % 100)) <= 70) {
            cout << "Minotaur Defeated !!!" << endl << endl;
            return true;
        }
        else {
            cout << "Theseus Defeated !!!" << endl << endl;
            return false;
        }
    }

    //Prints the escape plan
    void escapeMaze(Maze* maze) {
        cout << "Exiting the maze:" << endl;

        //Prints top element and removes it from stack
        while (path._top > 0) {
            path.top().print();
            path.pop();
        }

        cout << endl;
    }
};


//Loads maze and prints it to the user
Maze* loadMaze(string filename) {

    Maze* problem = new Maze(); //Creates new pointer of type Maze

    ifstream file(filename);

    //Checks if the file cannot be opened
    if (!file.is_open()) {
        cout << "Cannot open the file!" << endl;
        return nullptr;
    }

    //Reads first two lines as rows and columns
    file >> problem->rows;
    file >> problem->columns;

    //Reads theseus position
    file >> problem->theseus.row;
    file >> problem->theseus.column;

    //Reads minotaur position
    file >> problem->minotaur.row;
    file >> problem->minotaur.column;

    //Creates the maze in a 2D character array 
    problem->maze = new char* [problem->rows];
    for (int i = 0; i < problem->rows; i++) {
        problem->maze[i] = new char[problem->columns];
    }

    //Fills the maze with the appropreate character
    for (int i = problem->rows - 1; i >= 0 ; i--) {
        for (int j = 0; j < problem->columns; j++) {
            file >> problem->maze[i][j];
        }
    }

    return problem; //returns the maze
}


int main() {
    srand(time(0));

    Maze* maze = loadMaze("Example1.dat");

    maze->printMaze();
    MazeSolver First (maze);
    if (First.findMinotaur(maze)) if (First.defeatMinotaur()) First.escapeMaze(maze);

    maze = loadMaze("Example2.dat");
    maze->printMaze();
    MazeSolver Second (maze);
    if (Second.findMinotaur(maze)) if (Second.defeatMinotaur()) Second.escapeMaze(maze);

    maze = loadMaze("Example3.dat");
    maze->printMaze();
    MazeSolver Third (maze);
    if (Third.findMinotaur(maze)) if (Third.defeatMinotaur()) Third.escapeMaze(maze);
    
    maze = loadMaze("Example4.dat");
    maze->printMaze();
    MazeSolver Fourth (maze);
    if (Fourth.findMinotaur(maze)) if (Fourth.defeatMinotaur()) Fourth.escapeMaze(maze);

    delete maze;
    maze = nullptr;
}