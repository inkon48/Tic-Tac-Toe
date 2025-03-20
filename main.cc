#include <iostream>
#include <vector>
#include <algorithm>

#define RED "\e[0;31m"
class TicTacTae {
private:    
    std::vector<char> board;
    char currentPlayer;
public:
    TicTacTae() : board(9, ' ') {};
    void displayBoard() const {
        for (int i = 0; i < 9; ++i) {
            std::cout << board[i];
            if ((i + 1) % 3 != 0) {
                std::cout << "    |  ";  
            } else {
                std::cout << '\n';
                if (i < 8) std::cout << "-------------------" << '\n';
            }
        }
        std::cout << '\n';
    } 

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    void playerSelection(const char player) {
        if (player == 'X')
            currentPlayer = 'X';
        else 
            currentPlayer = 'O';
    }

    bool makeMove(const int position) {
        if (position < 1 || position > 9 || board[position - 1] != ' ')
            return false; // invalid position
        board[position - 1] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        return true;
    }

    char checkWinner() const {
        // check rows
        for (int i = 0; i < 9; i += 3) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i] != ' ')
                return board[i];
        }

        // check cols
        for (int i = 0; i < 3; ++i) {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != ' ')
                return board[i];
        }

        // check diagonal
        if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ')
            return board[0];
        if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ')
            return board[2];

        for (const char& cell : board) {
            if (cell == ' ')
                return ' '; // game not over 
        }
            
        return 'T';
    }

    bool isGameOver() const {
        if (checkWinner() != ' ' || std::find(board.begin(), board.end(), ' ') == board.end())
            return true;
        return false;
    }
};

int main() {
    std::cout << "hello";
    TicTacTae game;
    std::cout << "Who will take first (X, O)? ";
    char player;
    std::cin >> player;
    game.playerSelection(player);
    int position;
    char winner = ' ';
    while (!game.isGameOver()) {
        game.displayBoard();
        std::cout << "Player " << game.getCurrentPlayer() << ", enter your move (1-9): ";
        std::cin >> position;
        if (!game.makeMove(position)) {
            std::cerr << "Invalid move. Try again!" << '\n';
        }
    }

    game.displayBoard();
    winner = game.checkWinner();
    if (winner == 'T') {
        std::cout << "It's a tie." << '\n';
    } else {
        std::cout << RED << '\n';
        std::cout << "Player " << winner << " wins!" << '\n';
    }

    return 0;
}