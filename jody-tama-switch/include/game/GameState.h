#pragma once

#include <string>
#include <vector>
#include <chrono>

enum class GameStatus {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    VICTORY_SCREEN
};

enum class VictoryCondition {
    NONE,
    MASTER_CAPTURE,
    TEMPLE_VICTORY
};

struct GameState {
    GameStatus status;
    int currentPlayer;
    VictoryCondition victoryCondition;
    std::string winner;
    
    // Timing
    std::chrono::steady_clock::time_point gameStartTime;
    std::chrono::steady_clock::time_point lastMoveTime;
    float gameDuration;
    
    // Game progress
    int moveCount;
    int turnCount;
    
    // Selection state
    bool hasSelectedPiece;
    int selectedPieceRow;
    int selectedPieceCol;
    std::string selectedCard;
    
    // Valid moves
    std::vector<std::pair<int, int>> validMoves;
    
    // Constructor
    GameState() 
        : status(GameStatus::MENU)
        , currentPlayer(1)
        , victoryCondition(VictoryCondition::NONE)
        , winner("")
        , gameStartTime(std::chrono::steady_clock::now())
        , lastMoveTime(std::chrono::steady_clock::now())
        , gameDuration(0.0f)
        , moveCount(0)
        , turnCount(0)
        , hasSelectedPiece(false)
        , selectedPieceRow(-1)
        , selectedPieceCol(-1)
        , selectedCard("")
    {}
    
    // Utility methods
    void reset();
    void startNewGame();
    void updateGameDuration();
    float getGameDuration() const;
    bool isGameActive() const;
};