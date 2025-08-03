#pragma once

#include <vector>
#include <string>

// Piece types
enum class PieceType {
    MASTER,
    MONK
};

// Player numbers
enum class Player {
    PLAYER_1 = 1,
    PLAYER_2 = 2
};

// Piece structure
struct Piece {
    PieceType type;
    Player player;
    int row;
    int col;
    
    Piece(PieceType t, Player p, int r, int c) 
        : type(t), player(p), row(r), col(c) {}
};

// Board square
struct BoardSquare {
    Piece* piece;
    bool isTemple;
    
    BoardSquare() : piece(nullptr), isTemple(false) {}
};

class Board {
public:
    static const int BOARD_SIZE = 5;
    
    Board();
    ~Board();
    
    // Initialization
    void initialize();
    void reset();
    
    // Piece management
    bool placePiece(PieceType type, Player player, int row, int col);
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool removePiece(int row, int col);
    Piece* getPiece(int row, int col) const;
    
    // Board queries
    bool isEmpty(int row, int col) const;
    bool isValidPosition(int row, int col) const;
    bool isTemple(int row, int col) const;
    std::vector<Piece*> getPlayerPieces(Player player) const;
    std::pair<int, int> findMaster(Player player) const;
    
    // Board state
    const std::vector<std::vector<BoardSquare>>& getSquares() const;
    std::vector<std::vector<BoardSquare>> getSquaresCopy() const;
    
    // Utility
    void clear();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
    
private:
    std::vector<std::vector<BoardSquare>> squares;
    std::vector<std::unique_ptr<Piece>> pieces; // Owns all pieces
    
    void setupInitialBoard();
    void markTempleSquares();
};