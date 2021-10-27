#include <iostream> 
#include <cstdlib>
#include "functions.h"

using std::cout;
using std::endl;


/*================================================================================================*/
/* Provided function: random(int max): returns an integer "random" number in the interval [0,n-1] */
/*================================================================================================*/
int random(int max) // generate number in [0, max-1]
{
  return (rand() % max); 
} 

/*================================================================================================*/
/* Provided function: createMatrix(int m, int n): allocate dynamically a m x n matrix to store the*/
/*                    game matrix.                                                                */
/*================================================================================================*/


struct minePosition** createMatrix (int nRows, int nCols)
{
  struct minePosition** mat; 
  mat = new struct minePosition*[nRows]; 
  for (int i = 0; i < nRows; i++)
    mat[i] = new struct minePosition[nCols];
  return mat;
}

/*================================================================================================*/
/* Provided function: initializeMineMatrix(struct minePosition ** mineMatrix, int nRows,          */
/*                    int nCols, int nMines): initialize the game matrix, choosing nMines         */
/*                    positions of the matrix to the mines.                                       */
/*================================================================================================*/

void initializeMineMatrix (struct minePosition ** mineMatrix, int nRows, int nCols, int nMines)
{

  for(int i = 0; i < nRows; ++i)
    for(int j = 0; j < nCols; j++){
      mineMatrix[i][j].neighborMines = 0;
      mineMatrix[i][j].open = false; 
    }

  int i = 0; 
  while (i < nMines){
    int row = random(nRows); // suppose that random will eventually find 
    int col = random(nCols); // a free spot for a mine. 
    if (mineMatrix[row][col].neighborMines == 0){
      mineMatrix[row][col].neighborMines = MINE;
      i = i + 1; 
    }
  }
}

/*================================================================================================*/
/* Provided function: printMineMatrix(struct minePosition ** mineMatrix, int nRows, int nCols, int nMines):    */
/*          print the game matrix in standard io. If you want to improve it, go ahead! :)         */
/*================================================================================================*/

void printMineMatrix (struct minePosition ** matrix, int nRows, int nCols, int nMines)
{
  int closedPositions = 0; 
  for (int i = 0; i < nCols + 2; i++) cout << "="; 
  cout << endl; 
  for (int i = 0; i < nRows; i ++){
    cout << "|"; 
    for (int j = 0; j < nCols; j++)
      if (matrix[i][j].open)
	if (matrix[i][j].neighborMines == 0) 
	  cout << " "; 
	else if (matrix[i][j].neighborMines == MINE)
	  cout << "*"; 
	else
	  cout << matrix[i][j].neighborMines; 
      else{
        closedPositions = closedPositions + 1; 
	cout << ".";
      } 
    cout << "|"<< endl; 
  }
  for (int i = 0; i < nCols + 2; i++) cout << "="; 
  cout << endl; 
  cout << closedPositions << " closed positions. " << nMines << " mines." << endl; 
}

/*================================================================================================*/
/*  TO DO: int countClosedPositions (struct minePosition **mineMatrix, int nRows, int nCols):     */
/*         counts have many positions of the game matrix remain hidden                            */
/*================================================================================================*/

int countClosedPositions (struct minePosition** mineMatrix, int nRows, int nCols)
{
  int numberOfClosedPositions = 0;
  for (int i=0; i<nRows; i++) {
    for (int j=0; j<nCols; j++) {
      if (mineMatrix[i][j].open == false) {
        numberOfClosedPositions ++;
      }
    }
  }
  return numberOfClosedPositions; 
} 

/*================================================================================================*/
/*  TO DO: int countNeighborMines (struct minePosition **mineMatrix, int nRows, int nCols,        */
/*         int row, int col): given a position (row, col) of the game matrix, returns how many    */
/*         mines are in neighboring positions of the matrix. Be careful to test a position only if*/
/*         it is valid, ie, it is inside the bounds of the game matrix                            */
/*================================================================================================*/

bool isValid(int row, int col, int nRows, int nCols) {
  if ((row >= 0) && (row < nRows) && (col >= 0 ) && (col < nCols)) {
    return true;
  }
  else {
    return false;
  }
}
/*
bool isMine(int row, int col, struct minePosition** matrix) {
  if (matrix[row][col].neighborMines == -1) {
    return true;
  }
  else {
    return false;
  }
}
*/
int countNeighborMines(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col)
{
  int numberOfNeighborMines = 0;
  // top left corner
  if (isValid (row-1, col-1, nRows, nCols) == true) {
    if (mineMatrix[row-1][col-1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // top right corner
  if (isValid (row-1, col+1, nRows, nCols) == true) {
    if (mineMatrix[row-1][col+1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // bottom right corner
  if (isValid (row+1, col+1, nRows, nCols) == true) {
    if (mineMatrix[row+1][col+1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // bottom left corner
  if (isValid (row+1, col-1, nRows, nCols) == true) {
    if (mineMatrix[row+1][col-1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // top
  if (isValid (row-1, col, nRows, nCols) == true) {
    if (mineMatrix[row-1][col].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // left
  if (isValid (row, col+1, nRows, nCols) == true) {
    if (mineMatrix[row][col+1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // bottom
  if (isValid (row+1, col, nRows, nCols) == true) {
    if (mineMatrix[row+1][col].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  // right
  if (isValid (row, col-1, nRows, nCols) == true) {
    if (mineMatrix[row][col-1].neighborMines == -1) {
      numberOfNeighborMines ++;
    }
  }
  return numberOfNeighborMines;
}

/*================================================================================================*/
/*  TO DO: openPosition (struct minePosition **mineMatrix, int nRows, int nCols, int row, int col)*/
/*         *******recursive function******** open position (row, col) chosen by the user. It is a */
/*         mine, return MINE. Otherwise, count how many mines are in neighbor positions, and      */
/*         update the game matrix accordingly. If the position has no neighbor mine, open         */
/*         recursively the neighbor positions. Returns 0 if no mine position was chosen.          */
/*================================================================================================*/

int openPosition(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col)
{
  int numbMines = 0;
  if(mineMatrix[row][col].neighborMines == MINE) {
      cout << "BOOOOOOOOOOOOOOOOOOOOOOM";
      return MINE; 
  }
  else if(mineMatrix[row][col].neighborMines == 0) {
    mineMatrix[row][col].open = true;
    numbMines = countNeighborMines(mineMatrix, nRows, nCols, row, col);
    if(numbMines == 0) {
      mineMatrix[row][col].open == true;
      return 0;
    }
    else if(numbMines != 0) {
      return 0;
    }
  }
}
  
