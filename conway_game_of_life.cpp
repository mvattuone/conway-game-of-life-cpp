#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdlib.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

bool DEBUG = false;
int row = 170;
int grid[6460] = {};
int times = 0;
int x;
int y;

int checkNeighbors(int* neighbors) {
  int total = 0;
  for (int i=0;i<8;i++) {
    if (neighbors[i] == 1) {
      total++;
    }
  }

  return total;
}

void printGrid(int* grid, int size) {
  for (int i=0;i<size;i++) {
    if ((i+1) % row  == 0) {
      if (grid[i] == 0) {
        cout << BLUE << grid[i] << endl;
      } else {
        cout << BOLDMAGENTA << grid[i] << endl;
      }
    } else {
      if (grid[i] == 0) {
        cout << BLUE << grid[i];
      } else {
        cout << BOLDMAGENTA << grid[i];
      }
    }
  }
}

void initializeGrid(int* grid, int size) {
  x = rand() % row + 2;
  int nextState[6460] = {};
  for (int i=0; i<size;i++) {
    int rowIndex = row - 1;
    int sizeIndex = size - 1;
    int left = i % row != 0 ? grid[i-1] : 0;
    int topLeft = i % row != 0 && i > rowIndex ? grid[i-row-1] : 0;
    int top = i > rowIndex ? grid[i-row] : 0;
    int topRight = i % row != 3 && i > rowIndex ? grid[i-row+1] : 0;
    int right = i % row != 3 ? grid[i+1] : 0;
    int bottomRight = i % row != 3 && i < size - row ? grid[i+row+1] : 0;
    int bottom = i < size - row ? grid[i+row] : 0;
    int bottomLeft = i % rowIndex == 1 && i < sizeIndex - rowIndex ? grid[i + row - 1] : 0;

    if (DEBUG) {
      cout << "index is" << endl;
      cout << i << endl;
      cout << "grid value is" << endl;
      cout << grid[i] << endl;
      cout << "left is " << endl;
      cout << left << endl;
      cout << "top left is " << endl;
      cout << topLeft << endl;
      cout << "top is " << endl;
      cout << top << endl;
      cout << "top right is " << endl;
      cout << topRight << endl;
      cout << "right " << endl;
      cout << right << endl;
      cout << "bottom right " << endl;
      cout << bottomRight << endl;
      cout << "bottom is" << endl;
      cout << bottom << endl;
      cout << "bottom left is " << endl;
      cout << bottomLeft << endl;
      this_thread::sleep_for(chrono::milliseconds(1000));
     }

    int neighbors[8] = {
      left, topLeft, top, topRight, right, bottomRight, bottom, bottomLeft
    };

    int liveNeighbors = checkNeighbors(neighbors);

    if (grid[i] == 0) {
      if (liveNeighbors == 3) {
        nextState[i] = 1;
      }
    } else {
      if (liveNeighbors < 2 || liveNeighbors > 3) { 
        nextState[i] = 0;
      } else {
        nextState[i] = grid[i];
      }
    }
  }

  for (int i=0; i<size; i++) {
    grid[i] = nextState[i];
  }
}

void seedGrid(int* grid, int size) {
  for (int long i=0; i<size ;i++) {
    grid[i] = rand() % 2;
  }
}


int main() {
  srand(time(NULL));
  int size = sizeof(grid)/sizeof(grid[0]);
  seedGrid(grid, size); 
  if (DEBUG) {
    cout << "initial grid" << endl;
    printGrid(grid, size);
    this_thread::sleep_for(chrono::milliseconds(1000));
  }
  while (times < 20000) {
    initializeGrid(grid, size);
    printGrid(grid, size);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    times++;
   }

   cout << "Program completed";

  return 0;
}
