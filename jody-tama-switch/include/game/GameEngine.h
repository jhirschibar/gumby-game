#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "graphics/Renderer.h"
#include "Board.h"
#include "Card.h"
#include "GameState.h"

// Forward declarations
class Renderer;

class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    
    // Initialization
    bool initialize();
    void shutdown();
    
    // Game loop
    void update(float deltaTime);
    void render(Renderer* renderer);
    
    // Game state management
    void resetGame();
    void startNewGame();
    void pauseGame();
    void resumeGame();
    
    // Game actions
    bool selectPiece(int row, int col);
    bool selectCard(const std::string& cardName);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol, const std::string& cardName);
    
    // Game state queries
    GameState getGameState() const;
    int getCurrentPlayer() const;
    bool isGameOver() const;
    std::string getWinner() const;
    std::vector<std::pair<int, int>> getValidMoves(int row, int col) const;
    std::vector<std::pair<int, int>> getValidMovesForCard(const std::string& cardName) const;
    
    // Board access
    const Board& getBoard() const;
    std::vector<Card> getPlayerCards(int player) const;
    Card getCenterCard() const;
    
    // Save/Load
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
    
    // AI (for single player mode)
    void setAIOpponent(bool enabled);
    bool isAIOpponent() const;
    void setAIDifficulty(int difficulty); // 1-3 (Easy, Medium, Hard)
    
    // Statistics
    struct GameStats {
        int gamesPlayed;
        int player1Wins;
        int player2Wins;
        int averageGameLength;
        std::unordered_map<std::string, int> cardUsageStats;
    };
    
    GameStats getGameStats() const;
    void resetStats();
    
private:
    // Core game components
    std::unique_ptr<Board> board;
    std::vector<Card> allCards;
    std::unordered_map<int, std::vector<Card>> playerCards; // player -> cards
    Card centerCard;
    
    // Game state
    GameState currentState;
    int currentPlayer;
    std::string winner;
    
    // Selection state
    std::pair<int, int> selectedPiece; // row, col
    std::string selectedCard;
    std::vector<std::pair<int, int>> validMoves;
    
    // AI
    bool aiOpponent;
    int aiDifficulty;
    
    // Statistics
    GameStats stats;
    
    // Private methods
    void initializeCards();
    void dealCards();
    void shuffleCards(std::vector<Card>& cards);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Card& card) const;
    void exchangeCard(const std::string& usedCardName);
    bool checkWinCondition();
    std::pair<int, int> findMaster(int player) const;
    void updateValidMoves();
    void makeAIMove();
    
    // Card patterns (converted from JavaScript)
    struct CardPattern {
        std::string name;
        std::vector<std::vector<int>> pattern;
    };
    
    std::vector<CardPattern> cardPatterns;
    void initializeCardPatterns();
};