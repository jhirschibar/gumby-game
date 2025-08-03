// Main application entry point
document.addEventListener('DOMContentLoaded', function() {
    console.log('Initializing Jody-Tama game...');
    
    // Create game instance
    const game = new JodyTamaGame();
    
    // Create UI controller
    const ui = new JodyTamaUI(game);
    
    // Store references globally for debugging
    window.jodyTamaGame = game;
    window.jodyTamaUI = ui;
    
    console.log('Jody-Tama game initialized successfully!');
    
    // Add some helpful console commands for debugging
    console.log('Available debug commands:');
    console.log('- window.jodyTamaGame: Access the game engine');
    console.log('- window.jodyTamaUI: Access the UI controller');
    console.log('- window.jodyTamaGame.getGameState(): Get current game state');
    console.log('- window.jodyTamaGame.resetGame(): Reset the game');
});

// Add some utility functions for development
window.JodyTamaUtils = {
    // Log current game state
    logGameState: function() {
        if (window.jodyTamaGame) {
            console.log('Current Game State:', window.jodyTamaGame.getGameState());
        }
    },
    
    // Test a specific move
    testMove: function(fromRow, fromCol, toRow, toCol, cardName) {
        if (window.jodyTamaGame) {
            const result = window.jodyTamaGame.makeMove(fromRow, fromCol, toRow, toCol, cardName);
            console.log('Move result:', result);
            return result;
        }
    },
    
    // Get all valid moves for a piece
    getValidMoves: function(row, col) {
        if (window.jodyTamaGame) {
            return window.jodyTamaGame.getValidMoves(row, col);
        }
    },
    
    // Get all valid moves for a card
    getValidMovesForCard: function(cardName) {
        if (window.jodyTamaGame) {
            return window.jodyTamaGame.getValidMovesForCard(cardName);
        }
    }
};