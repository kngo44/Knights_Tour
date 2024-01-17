#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"
// #include "ArgumentManager.h"
using namespace std;

void DrawBoard(int** board, int numRows, int numCols);
void ResetBoard(int** board, int numRows, int numCols);
bool CheckMove(int** board, int row, int col, int numRows, int numCols);
bool PlaceKnight(int** board, int row, int col, int numRows, int numCols, int moves);

int main() {
  // ArgumentManager am(argc, argv);
  // ifstream fin(am.get("input"));
  // ofstream fout(am.get("output"));
  
  ifstream fin("input3.txt");
  ofstream fout("output.txt");
  
  int numRows, numCols;
  fin >> numRows >> numCols;
  // numRows = 5;
  // numCols = 8;
  
  int** board = new int*[numRows];
  for(int i = 0; i < numRows; i++){
    board[i] = new int[numCols];
  }

  ResetBoard(board, numRows, numCols);

  bool closedTour = false;
  board[0][0] = 1;
  closedTour = PlaceKnight(board, 0, 0, numRows, numCols, 1);

  if(closedTour){
    fout << "A closed tour exists!" << endl;
  }else{
    fout << "A closed tour does not exist!" << endl;
  }
  
  DrawBoard(board, numRows, numCols);
  
  for(int i = 0; i < numRows; i++){
    delete[] board[i];
    board[i] = NULL;
  }
  delete[] board;
  board = NULL;
  fin.close();
  fout.close();
  
  return 0;
}

void DrawBoard(int** board, int numRows, int numCols){
    cout << "+";

    for(int i = 0; i < numCols; i++){
        cout << "--+";
    }
    cout << endl;

    for(int j = 0; j < numRows; j++){
        cout << "|";
        for(int i = 0; i < numCols; i++){
            if(board[j][i] > 0){
                cout << setw(2) << board[j][i] << "|";
            }
            else {
                cout << "  |";
            }
        }
        cout << endl;
        cout << "+";
    
        for(int i = 0; i < numCols; i++){
            cout << "--+";
        }
        cout << endl;
    }
    cout << endl;
}

void ResetBoard(int** board, int numRows, int numCols){
  for(int row = 0; row < numRows; row++){
    for(int col = 0; col < numCols; col++){
      board[row][col] = 0;
    }
  }
}

bool CheckMove(int** board, int row, int col, int numRows, int numCols){
  if(row >= 0 && row < numRows && col >= 0 && col < numCols){
    return (board[row][col] == 0);
  }else{
    return false;
  }
}

bool PlaceKnight(int** board, int row, int col, int numRows, int numCols, int moves){
  if(numRows == 1 && numCols == 1){
    cout << "Closed Tour" << endl;
    return true;
  }else if(moves == numRows*numCols){
    if(board[1][2] == moves || board[2][1] == moves){
      cout << "Closed Tour" << endl;
      return true;
    }
    return false;
  }

  int possibleRow[] = {-2,-2,2,2,-1,-1,1,1};
  int possibleCol[] = {-1,1,-1,1,-2,2,-2,2};
  
  Queue q;
  q.Push(row, col);
  while(!q.IsEmpty()){
    int startRow = q.Peek()->row;
    int startCol = q.Peek()->col;
    q.Pop();
    for(int i = 0; i < 8; i++){
      int currentRow = startRow + possibleRow[i];
      int currentCol = startCol + possibleCol[i];
      if(CheckMove(board, currentRow, currentCol, numRows, numCols)){
        board[currentRow][currentCol] = moves+1;
        //DrawBoard(board, numRows, numCols);
        if(PlaceKnight(board, currentRow, currentCol, numRows, numCols, moves+1)){
          return true;
        }else{
          board[currentRow][currentCol] = 0;
        }
      }
    }
  }
  
  return false;
}