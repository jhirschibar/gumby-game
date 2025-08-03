#pragma once

#include <string>
#include <vector>

class Card {
public:
    Card();
    Card(const std::string& name, const std::vector<std::vector<int>>& pattern);
    ~Card();
    
    // Card properties
    std::string getName() const;
    std::vector<std::vector<int>> getPattern() const;
    
    // Pattern validation
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
    std::vector<std::pair<int, int>> getValidMoves(int fromRow, int fromCol, int boardSize) const;
    
    // Utility
    void setName(const std::string& name);
    void setPattern(const std::vector<std::vector<int>>& pattern);
    bool isEmpty() const;
    
    // Serialization
    std::string serialize() const;
    bool deserialize(const std::string& data);
    
private:
    std::string name;
    std::vector<std::vector<int>> pattern; // 3x3 pattern grid
    
    // Pattern validation helpers
    bool isPatternValid(const std::vector<std::vector<int>>& pattern) const;
    bool isPositionInBounds(int row, int col, int boardSize) const;
};

// Card factory for creating all Onitama cards
class CardFactory {
public:
    static std::vector<Card> createAllCards();
    static Card createCard(const std::string& name);
    
private:
    static std::vector<std::pair<std::string, std::vector<std::vector<int>>>> getCardDefinitions();
};