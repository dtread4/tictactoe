// David Treadwell
// 9.3.2023
// C++ 17
// main.cpp
// Tic Tac Toe game in terminal

#include <iostream>
#include <time.h>
using namespace std;

// Function:   initializeBoard
// Purpose:    Fills the board array with empty characters (spaces)
// Parameters: A pointer to the gameBoard array
// Returns:    None
void initializeBoard(char[]);

// Function:   printBoard
// Purpose:    Prints the game in its current state
// Parameters: A pointer to the gameBoard array
// Returns:    None
void printBoard(char[]);

// Function:   printGenericRow
// Purpose:    Prints a basic row without information from the array
// Parameters: Boolean to determine what type of row style to print
// Returns:    None
void printGenericRow(bool);

// Function:   printPlayRow
// Purpose:    Prints a row of the game board using information from the array
// Parameters: Pointer to the game board, integer for which row of the board to print
// Returns:    None
void printPlayRow(char[], int);

// Function:   gameOverCheck
// Purpose:    Checks if one of eight possible win conditions has been reached, and prints a message if so
// Parameters: The gameboard, which character (X or O) was last played, whether the computer or human last played
// Returns:    True if a win condition was met, false if not
bool gameOverCheck(char[], char, bool);

// Function:   getResponse
// Purpose:    Gets a player response (always 1 - 3)
// Parameters: Message to provide context that the player will respond to
// Returns:    The response (1, 2, or 3)
string getResponse(const string&);

// Function:   pieceSelect
// Purpose:    Lets the player pick to be X or O (or chooses randomly for them)
// Parameters: None
// Returns:    The piece the player will play
void pieceSelect(char&, char&);

// Function:   playerMove
// Purpose:    Records the player move based on a column/row pair
// Parameters: The game-board, which character (X or O) the player is
// Returns:    The index of the player move
int playerMove(char[], char);

// Function:   computerMove
// Purpose:    Records the computer move based on either a random selection or an intelligent selection
// Parameters: The game-board, which character (X or O) the computer is, whether to select randomly or intelligently
// Returns:    The index of the computer move
int computerMove(char[], char, bool);

// Function:   playGame
// Purpose:    All game logic and playing occurs within this method
// Parameters: None
// Returns:    None
void playGame();


int main() {

    // Handles starting a new game or ending
    string response;
    while (response != "2") {

        // This method is where all game actions take place
        playGame();

        // Ask user if they want to play again
        response = getResponse("Play Again? (Press 1 or 3 for yes, press 2 for no)\n");

    }

    cout << "Thanks for playing!\n";

    return 0;
}

// Function:   initializeBoard
// Purpose:    Fills the board array with empty characters (spaces)
// Parameters: A pointer to the gameBoard array
// Returns:    None
void initializeBoard(char gameBoard[]) {

    for (int i = 0; i < 9; i++) {

        gameBoard[i] = ' ';

    }

}

// Function:   printBoard
// Purpose:    Prints the game in its current state
// Parameters: A pointer to the gameBoard array
// Returns:    None
void printBoard(char gameBoard[]) {

    cout << "    1     2     3  \n";
    printGenericRow(true);
    printPlayRow(gameBoard, 0);
    printGenericRow(false);
    printGenericRow(true);
    printPlayRow(gameBoard, 1);
    printGenericRow(false);
    printGenericRow(true);
    printPlayRow(gameBoard, 2);
    printGenericRow(true);
    cout << endl;

}

// Function:   printGenericRow
// Purpose:    Prints a basic row without information from the array
// Parameters: Boolean to determine what type of row style to print
// Returns:    None
void printGenericRow(bool type) {

    char printChar;

    // Two types of row: blank ones (type == true) and rows with dashes (type == false)
    if (type) {

        printChar = ' ';

    } else {

        printChar = '_';

    }

    cout << "  ";

    for (int i = 1; i <= 17; i++) {

        // Print vertical line in specific spots
        if (i == 6 || i == 12) {

            cout << "|";

        } else {

            cout << printChar;

        }

    }

    cout << endl;

}

// Function:   printPlayRow
// Purpose:    Prints a row of the game board using information from the array
// Parameters: Pointer to the game board, integer for which row of the board to print
// Returns:    None
void printPlayRow(char gameBoard[], int row) {

    // Index of the array to access will be 3 times row number (row 0-indexed)
    int gamePos = row * 3;

    cout << (row + 1);

    for (int i = 1; i <= 18; i++) {

        // Print different characters depending on the iterator/location in the board
        if (i == 7 || i == 13) {

            cout << "|";

        } else if (i == 4 || i == 10 || i == 16){

            cout << gameBoard[gamePos];

            gamePos++;

        } else {

            cout << " ";

        }

    }

    cout << endl;

}

// Function:   gameOverCheck
// Purpose:    Checks if one of eight possible win conditions has been reached, and prints a message if so
// Parameters: The gameboard, which character (X or O) was last played, whether the computer or human last played
// Returns:    True if a win condition was met, false if not
bool gameOverCheck(char gameBoard[], char lastMoved, bool player) {

    bool over = false;
    bool victory = false;

    // Check if the game was a draw
    int freeSpaces = 0;
    for (int i = 0; i < 9; i++) {

        if(gameBoard[i] == ' ') {

            freeSpaces++;

        }

    }

    // If there were no free spaces, then the game must be over
    if (freeSpaces == 0) {

        over = true;

    }

    // 1. Complete top row
    if (gameBoard[0] == lastMoved && gameBoard[1] == lastMoved && gameBoard[2] == lastMoved) {

        victory = true;
        over = true;

    }
    // 2. Complete second row
    if (gameBoard[3] == lastMoved && gameBoard[4] == lastMoved && gameBoard[5] == lastMoved) {

        victory = true;
        over = true;

    }
    // 3. Complete third row
    if (gameBoard[6] == lastMoved && gameBoard[7] == lastMoved && gameBoard[8] == lastMoved) {

        victory = true;
        over = true;

    }
    // 4. Complete first column
    if (gameBoard[0] == lastMoved && gameBoard[3] == lastMoved && gameBoard[6] == lastMoved) {

        victory = true;
        over = true;

    }
    // 5. Complete second column
    if (gameBoard[1] == lastMoved && gameBoard[4] == lastMoved && gameBoard[7] == lastMoved) {

        victory = true;
        over = true;

    }
    // 6. Complete third column
    if (gameBoard[2] == lastMoved && gameBoard[5] == lastMoved && gameBoard[8] == lastMoved) {

        victory = true;
        over = true;

    }
    // 7. Diagonal top left to bottom right
    if (gameBoard[0] == lastMoved && gameBoard[4] == lastMoved && gameBoard[8] == lastMoved) {

        victory = true;
        over = true;

    }
    // 8. Diagonal bottom left to top right
    if (gameBoard[6] == lastMoved && gameBoard[4] == lastMoved && gameBoard[2] == lastMoved) {

        victory = true;
        over = true;

    }

    // Game over and player won
    if(over && player && victory) {

        cout << "Congrats, you won!\n\n";

    }

    // Game over and computer won
    if (over && !player && victory) {

        cout << "Sorry, you lost. Better luck next time.\n\n";

    }

    // Game over and nobody won
    if (over && !victory) {

        cout << "It's a draw! Well played.\n\n";

    }

    return over;

}

// Function:   getResponse
// Purpose:    Gets a player response (always 1 - 3)
// Parameters: Message to provide context that the player will respond to
// Returns:    The response (1, 2, or 3)
string getResponse(const string& message) {

    string response;

    // Keep asking for an input until the user enters a valid one
    while (response != "1" && response != "2" && response != "3") {

        cout << message;
        getline(cin, response);

        if (response != "1" && response != "2" && response != "3") {

            cout << "Sorry, invalid response; please try again:\n";

        }

    }

    return response;

}

// Function:   pieceSelect
// Purpose:    Lets the player pick to be X or O (or chooses randomly for them)
// Parameters: None
// Returns:    The piece the player will play
void pieceSelect(char& playerPiece, char& computerPiece) {

    string response;
    playerPiece = 'n';

    response = getResponse(
            "What piece do you want to play as?\n[1] - X (and go first)\n[2] - O (and go second)\n[3] - Random\n"
            );

    // Set the piece if player selected explicitly
    if (response == "1") {

        playerPiece = 'X';
        computerPiece = 'O';

    }

    if (response == "2") {

        playerPiece = 'O';
        computerPiece = 'X';

    }

    // Randomly select a piece
    if (response == "3") {

        srand(time(0));

        if(rand() % 2 == 0) {

            playerPiece = 'X';
            computerPiece = 'O';

        } else {

            playerPiece = 'O';
            computerPiece = 'X';

        }

    }

}

// Function:   playerMove
// Purpose:    Records the player move based on a column/row pair
// Parameters: The gameboard, which character (X or O) the player is
// Returns:    The index of the player move
int playerMove(char gameBoard[], char playerPiece) {

    string response;
    int playIndex = -1;

    // Get column number
    response = getResponse("Please select a column to play your move:\n");

    // Convert to integer, then subtract one (board is not 0-indexed but array is)
    playIndex = stoi(response) - 1;

    // Get row number
    response = getResponse("Please select a row to play your move:\n");

    // Add the row (value minus one times three) to the column to get the index of the desired move
    playIndex = playIndex + 3 *(stoi(response) - 1);

    // Adjust the array/board to account for the move
    gameBoard[playIndex] = playerPiece;

    return playIndex;

}

// Function:   computerMove
// Purpose:    Records the computer move based on either a random selection or an intelligent selection
// Parameters: The game-board, which character (X or O) the computer is, whether to select randomly or intelligently
// Returns:    The index of the computer move
int computerMove(char gameBoard[], char computerPiece, bool intelligent) {

    int playIndex;

    // TODO add if back
    //if (!intelligent) {

        srand(time(nullptr));

        // Assign play index to computer to play randomly. If that space is occupied, keep running until empty found
        do {

            // Select random number between max (8) and minimum (0) index
            playIndex = (rand() % (8 - 0 + 1));

        } while (gameBoard[playIndex] != ' ');

    //}

    gameBoard[playIndex] = computerPiece;

    return playIndex;

}

// Function:   playGame
// Purpose:    All game logic and playing occurs within this method
// Parameters: None
// Returns:    None
void playGame() {

    bool gameOver = false;

    char playerPiece;
    char computerPiece;
    pieceSelect(playerPiece, computerPiece);

    // Note that a 1D array is being used to represent a 2D game-board for simplicity.
    // Indexes 0-2 are row 1, 3-5 are row 2, 6-8 are row 3
    char gameBoard[9];
    initializeBoard(gameBoard);

    while(!gameOver) {

        // If player is X, they will go first each time. Otherwise, they will go second
        if (playerPiece == 'X') {

            printBoard(gameBoard);
            playerMove(gameBoard, playerPiece);
            printBoard(gameBoard);
            gameOver = gameOverCheck(gameBoard, playerPiece, true);

            if (!gameOver) {

                computerMove(gameBoard, computerPiece, false);
                printBoard(gameBoard);
                gameOver = gameOverCheck(gameBoard, computerPiece, false);

            }


        } else {

            computerMove(gameBoard, computerPiece, false);
            printBoard(gameBoard);
            gameOver = gameOverCheck(gameBoard, computerPiece, false);

            if (!gameOver) {

                playerMove(gameBoard, playerPiece);
                printBoard(gameBoard);
                gameOver = gameOverCheck(gameBoard, playerPiece, true);

            }

        }

    }

}