//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:
 
     Mallika Patil
     Lab: Tues, 9am 
     UIC CS 141, Spring 2019
     Welcome to 1024.
     This program is based off of Gabriele Cirulli's game online at
     bit.ly/great2048
 
     For each move enter a direction as a letter key, as follows:
         W
       A S D
     where A=left,W=up, D=right and S=down.
 
     After a move, when two identical valued tiles come together they
     join to become a new single tile with the value of the sum of the
     two originals. This value gets added to the score.  On each move
     one new randomly chosen value of 2 or 4 is placed in a random open
     square.  User input of x exits the game.
 
     Game ends when you reach 1024.
 
     Score: 0
	 .     4     .     .

	 .     .     .     .

	 .     .     4     .

	 .     .     .     .
 
     1. Your move: a
 
     Score: 0
	 4     .     .     .

	 .     .     .     .

	 4     .     .     .

	 .     .     2     .
 
     2. Your move: a
     .
     .
     .
*/

#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to 1024. \n"
         << "  \n"
         << "For each move enter a direction as a letter key, as follows: \n"
		 << "    W    \n"
		 << "  A S D  \n"
		 << "where A=left,W=up, D=right and S=down. \n"
		 << "  \n"
		 << "After a move, when two identical valued tiles come together they    \n"
		 << "join to become a new single tile with the value of the sum of the   \n"
		 << "two originals. This value gets added to the score.  On each move    \n"
		 << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		 << "square.  User input of x exits the game.                            \n"
		 << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide*squaresPerSide);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
}//end placeRandomPiece()

// Function to display board 
void displayAsciiBoard(int board[], int squaresPerSide, int score){
    int gameScore = score;
    int index = 0;  
    std::cout << "Score: " << gameScore << std::endl;
    int size = squaresPerSide * squaresPerSide; 
    for(int i=0; i<size; i++){
        if(i%squaresPerSide == 0){
            cout << "        "; 
        }
        if(board[i] == 0){
            cout << setw(6) << ".";
        }
        else{
            cout << setw(6) << board[i];
        }
        if(((i+1)%squaresPerSide == 0) && (i!=0)){ 
            cout << endl << endl; 
        }
    }
}

// Function to get index number
int getIndex(int row, int column, int squaresPerSide){
    int index = (row * squaresPerSide) + column; 
    return index; 
}

// Function to check if the two loops are the same 
bool isSame(int board[], int previousBoard[], int size){
    bool isSame = false; 
    int counter = 0; 
    for(int i=0; i<size; i++){
        if(board[i] == previousBoard[i]){
            counter++;
        }
    }
    if(counter == size){
        isSame = true; 
    }
    return isSame; 
}

// Function for checking if max tile has been reached
int getMaxTile(int squaresPerSide){
    int maxTile; 
    int multiplier = 1; 
    for(int i=squaresPerSide; i>4; i--){
        multiplier = multiplier * 2; 
    }
    maxTile = 1024 * multiplier;
    return maxTile; 
}

// Function for checking if board is full 
bool boardFull(int board[], int boardSize){
    bool truthVal = false; 
    int counter = 0; 
    int size = boardSize * boardSize; 
    for(int i=0; i<size; i++){
        if(board[i] != 0){
            counter++;
        }
    }
    if(counter == size){
        truthVal = true; 
    }
    return truthVal; 
}

// Function for checking if max tile has been reached 
bool maxTileReached(int board[], int maxTile, int boardSize){
    bool truthVal = false;
    int size = boardSize * boardSize; 
    for(int i=0; i<size; i++){
        if(board[i] == maxTile){
            truthVal = true;
        }
    }
    return truthVal; 
}

// Function for shifting left
void shiftLeft(int board[], int squaresPerSide){
    for(int i=0; i<squaresPerSide; i++){    // Iterates through rows
        bool moveMade = false;
        for(int j=0; j<squaresPerSide-1; j++){    // Iterates through columns 
            int currIndex = getIndex( i, j, squaresPerSide); 
            int nextIndex = getIndex( i, j+1, squaresPerSide);
            if((board[currIndex]==0) && (board[nextIndex]!=0)){   // Checks if currentIndex is empty and nextIndex is filled
                board[currIndex] = board[nextIndex]; 
                board[nextIndex] = 0; 
                moveMade = true; 
            }
        }
        if(moveMade){   // If a move is made in a column, then goes to previous row and repeates 
            i--; 
        }
    }
}

// Function for merging left 
void mergeLeft(int board[], int squaresPerSide, int &score){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through rows 
        for(int j=0; j<squaresPerSide-1; j++){   //Iterates through columns 
            int currIndex = getIndex( i, j, squaresPerSide);
            int nextIndex = getIndex( i, j+1, squaresPerSide);
            if((board[currIndex] == board[nextIndex]) && (board[nextIndex] != 0)){   // Checks if two positions are the same
                board[currIndex] = board[nextIndex] + board[currIndex];   // Adds total of the two same squares, and sets the value to currentIndex
                board[nextIndex] = 0; 
                score = score + board[nextIndex] + board[currIndex];   // Updates score
            }
        }
    }
}

// Function for shifting right
void shiftRight(int board[], int squaresPerSide){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through rows
        bool moveMade = false;
        for(int j=squaresPerSide-1; j>0; j--){    // Iterates through columns in reverse order
            int currIndex = getIndex( i, j, squaresPerSide);
            int nextIndex = getIndex( i, j-1, squaresPerSide);   // Gets nextIndex to check from the left side, reverse order of shiftRight
            if((board[currIndex] == 0)&&(board[nextIndex] != 0)){   // Checks if currentIndex is empty and nextIndex is filled
                board[currIndex] = board[nextIndex]; 
                board[nextIndex] = 0; 
                moveMade = true; 
            }
        }
        if(moveMade){   // Iterates through same row if board changed
                i--;
        }
    }
}

// Function for merging right 
void mergeRight(int board[], int squaresPerSide, int &score){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through rows
        for(int j=squaresPerSide-1; j>0; j--){   // Iterates through columns in reverse order
            int currIndex = getIndex( i, j, squaresPerSide);
            int nextIndex = getIndex( i, j-1, squaresPerSide);   // Gets nextIndex to check from the left side, reverse order of shiftRight
            if((board[currIndex] == board[nextIndex]) && (board[nextIndex] != 0)){   
                board[currIndex] = board[nextIndex] + board[currIndex];   // Adds total of the two same squares, and sets the value to currentIndex
                board[nextIndex] = 0;
                score = score + board[nextIndex] + board[currIndex];   // Updates score 
            }
        }
    }
}

// Function for shifting down
void shiftDown(int board[], int squaresPerSide){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through columns
        bool moveMade = false;
        for(int j=squaresPerSide-1; j>0; j--){   // Iterates through rows in reverse order
            int currIndex = getIndex( j, i, squaresPerSide);
            int nextIndex = getIndex( j-1, i, squaresPerSide);   // nextIndex gets the index for the position of the piece in the previous row
            if((board[currIndex]==0)&&(board[nextIndex]!=0)){   // Checks if currentIndex is empty and nextIndex is filled
                board[currIndex] = board[nextIndex]; 
                board[nextIndex] = 0; 
                moveMade = true; 
            } 
        }
        if(moveMade){    // Iterates through same column if board changed
            i--;   
        }
    }
}

// Function for merging down
void mergeDown(int board[], int squaresPerSide, int &score){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through columns
        for(int j=squaresPerSide-1; j>0; j--){   // Iterates through rows in reverse order
            int currIndex = getIndex( j, i, squaresPerSide);
            int nextIndex = getIndex( j-1, i, squaresPerSide);    // nextIndex gets the index for the position of the piece in the previous row
            if((board[currIndex] == board[nextIndex]) && (board[nextIndex] != 0)){
                board[currIndex] = board[nextIndex] + board[currIndex];   // Adds total of the two same squares, and sets the value to currentIndex
                board[nextIndex] = 0; 
                score = score + board[nextIndex] + board[currIndex];   // Updates score 
            }
        }
    }
}
    
// Function for shifting up 
void shiftUp(int board[], int squaresPerSide){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through columns
        bool moveMade = false;
        for(int j=0; j<squaresPerSide-1; j++){    // Iterates through rows
            int currIndex = getIndex( j, i, squaresPerSide);   
            int nextIndex = getIndex( j+1, i, squaresPerSide);   // nextIndex gets index of next row in the same column
            if((board[currIndex] == 0)&&(board[nextIndex] != 0)){   // Checks if currentIndex is empty and nextIndex is filled
                board[currIndex] = board[nextIndex]; 
                board[nextIndex] = 0; 
                moveMade = true; 
            }
        }
        if(moveMade){    // Iterates through same column if board changed
                i--;
        }
    }
}

// Function for merging up 
void mergeUp(int board[], int squaresPerSide, int &score){
    for(int i=0; i<squaresPerSide; i++){   // Iterates through columns
        for(int j=0; j<squaresPerSide-1; j++){   // Iterates through rows
            int currIndex = getIndex( j, i, squaresPerSide);
            int nextIndex = getIndex( j+1, i, squaresPerSide);
            if((board[currIndex] == board[nextIndex]) && (board[nextIndex] != 0)){
                board[currIndex] = board[nextIndex] + board[currIndex];   // Adds total of the two same squares, and sets the value to currentIndex
                board[nextIndex] = 0;  
                score = score + board[nextIndex] + board[currIndex];   // Updates score 
            }
        }
    }
}

//---------------------------------------------------------------------------------------
int main()
{
    // Variable Declarations
    int score = 0;
    int squaresPerSide = 4;        // User will enter this value.  Set default to 4
    int board[ MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
                                                      //    if a move changed the board.
    int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';                  // handles user input
    int move = 1;                          // user move counter
    int placementIndex;                    // For storing user index of choice
    int placementNum;                      // For storing user number to be placed
        
    
    // Display instructions
    displayInstructions();
    cout << " Game ends when you reach " << maxTileValue << "." << endl << endl; 
    
    // Get the board size, create and initialize the board, and set the max tile value depending on board size
    for(int i=0; i<(MaxBoardSize * MaxBoardSize); i++){
    	board[i] = 0; 
	}
    placeRandomPiece(board, squaresPerSide);
    placeRandomPiece(board, squaresPerSide);
    int size = squaresPerSide * squaresPerSide; 
    
    // Infinite loop to run program until user selects exit, board is full, or max tile value is reached
    while( true)
    {

        // Display the text-based board if maxTile Value has not been reached 
        if(!maxTileReached(previousBoard, maxTileValue, squaresPerSide)){
            displayAsciiBoard( board, squaresPerSide, score);
        }
        
        // See if maxTileValue has been reached.  If so, display the final board and break.
        if(maxTileReached(previousBoard, maxTileValue, squaresPerSide)){
            cout << "Congratulations!  You made it to " << maxTileValue << " !!!";
            displayAsciiBoard( board, squaresPerSide, score);
            break; 
        }
        
        // Make a copy of the board  
        for(int i=0; i<size; i++){
            previousBoard[i] = board[i]; 
    
        }
 
        // Prompt for and handle user input
        cout << move << ". Your move: ";
        cin >> userInput;
        
        // See if the board is full.  If so, display the final board and break.
        if(boardFull(board, squaresPerSide)){
            cout << "No more available moves.  Game is over.";
            displayAsciiBoard( board, squaresPerSide, score);
            break; 
        }
        
        switch (userInput) {
            case 'p':
                    cin >> placementIndex; 
                    cin >> placementNum;
                    if(userInput == 'p'){
                        board[placementIndex] = placementNum;   // Places user number of choice on user's index of choice 
                    }
                    break; 
            case 'x':
                    cout << "Thanks for playing. Exiting program... \n\n";
                    exit( 0);
                    break;
			case 'r':
                    std::cin >> squaresPerSide; 
                    if(userInput =='r'){
                        score = 0;   // Resets score
                        move = 0;    // Resets moves
                        size = squaresPerSide * squaresPerSide;   // Resets board size
                        maxTileValue = getMaxTile(squaresPerSide);   // Resets maxTileValue
                        for(int i=0; i<size; i++){   // Reinitializes board
                            board[i] = 0;  
                        }
                        for(int i=0; i<size; i++){   // Reinitializes previous board 
                            previousBoard[i] = board[i];  
                        }
                        placeRandomPiece(board, squaresPerSide);   // Places random piece
                    }
                    cout << "Resetting board" << std::endl << std::endl; 
                    cout << "Enter the size board you want, between 4 and 12: Game ends when you reach " << getMaxTile(squaresPerSide) << "." << std::endl; 
                    break;  
            case 'a':
                    shiftLeft(board, squaresPerSide); 
                    mergeLeft(board, squaresPerSide, score);
                    shiftLeft(board, squaresPerSide); 
                    break; 
            case 's':
                    shiftDown(board, squaresPerSide); 
                    mergeDown(board, squaresPerSide, score);
                    shiftDown(board, squaresPerSide); 
                    break;
            case 'w':
                    shiftUp(board, squaresPerSide); 
                    mergeUp(board, squaresPerSide, score);
                    shiftUp(board, squaresPerSide); 
                    break;
            case 'd':
                    shiftRight(board, squaresPerSide); 
                    mergeRight(board, squaresPerSide, score);
                    shiftRight(board, squaresPerSide);
                    break; 
            default:
                    cout << "Invalid input, please retry.";
                    continue;
                    break;
            
        }//end switch( userInput)
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update the move number.
        int numPieces = 0; 
        for(int i=0; i<size; i++){
            if(previousBoard[i] == board[i]){
                numPieces++; 
            }
        }
        if(numPieces == size){   // Check to see if new board is the same as the previous board
            continue;
        }
        if(userInput!='p'){
            placeRandomPiece(board, squaresPerSide);
            move++; 
        }
    }//end while( true)

    return 0;
}//end main()

