class JodyTamaGame {
    constructor() {
        this.board = this.createBoard();
        this.currentPlayer = 1;
        this.gameState = 'playing'; // 'playing', 'gameOver'
        this.selectedPiece = null;
        this.selectedCard = null;
        this.validMoves = [];
        this.cards = this.createCards();
        this.playerCards = { 1: [], 2: [] };
        this.centerCard = null;
        this.gameHistory = [];
        
        this.initializeGame();
    }

    createBoard() {
        const board = [];
        for (let row = 0; row < 5; row++) {
            board[row] = [];
            for (let col = 0; col < 5; col++) {
                board[row][col] = null;
            }
        }
        return board;
    }

    createCards() {
        // All 17 Onitama cards with their movement patterns
        return {
            'Boar': {
                name: 'Boar',
                pattern: [
                    [0, 0, 0],
                    [1, 0, 0],
                    [0, 0, 0]
                ]
            },
            'Cobra': {
                name: 'Cobra',
                pattern: [
                    [0, 0, 0],
                    [0, 0, 1],
                    [0, 1, 0]
                ]
            },
            'Crab': {
                name: 'Crab',
                pattern: [
                    [0, 0, 0],
                    [1, 0, 1],
                    [0, 0, 0]
                ]
            },
            'Crane': {
                name: 'Crane',
                pattern: [
                    [0, 1, 0],
                    [0, 0, 0],
                    [0, 1, 0]
                ]
            },
            'Dragon': {
                name: 'Dragon',
                pattern: [
                    [0, 0, 1],
                    [1, 0, 0],
                    [0, 0, 1]
                ]
            },
            'Eel': {
                name: 'Eel',
                pattern: [
                    [0, 1, 0],
                    [0, 0, 0],
                    [0, 0, 1]
                ]
            },
            'Elephant': {
                name: 'Elephant',
                pattern: [
                    [0, 1, 0],
                    [0, 1, 0],
                    [0, 0, 0]
                ]
            },
            'Frog': {
                name: 'Frog',
                pattern: [
                    [0, 0, 0],
                    [0, 0, 1],
                    [0, 1, 0]
                ]
            },
            'Goose': {
                name: 'Goose',
                pattern: [
                    [0, 1, 0],
                    [0, 0, 0],
                    [0, 0, 1]
                ]
            },
            'Horse': {
                name: 'Horse',
                pattern: [
                    [0, 0, 0],
                    [0, 1, 0],
                    [0, 0, 1]
                ]
            },
            'Mantis': {
                name: 'Mantis',
                pattern: [
                    [0, 0, 0],
                    [0, 0, 1],
                    [0, 1, 0]
                ]
            },
            'Monkey': {
                name: 'Monkey',
                pattern: [
                    [0, 1, 0],
                    [0, 0, 0],
                    [0, 1, 0]
                ]
            },
            'Ox': {
                name: 'Ox',
                pattern: [
                    [0, 0, 0],
                    [0, 1, 0],
                    [0, 0, 1]
                ]
            },
            'Rabbit': {
                name: 'Rabbit',
                pattern: [
                    [0, 0, 0],
                    [0, 0, 1],
                    [0, 1, 0]
                ]
            },
            'Rooster': {
                name: 'Rooster',
                pattern: [
                    [0, 1, 0],
                    [0, 0, 0],
                    [0, 0, 1]
                ]
            },
            'Tiger': {
                name: 'Tiger',
                pattern: [
                    [0, 0, 0],
                    [0, 0, 0],
                    [0, 2, 0]
                ]
            },
            'Turtle': {
                name: 'Turtle',
                pattern: [
                    [0, 0, 0],
                    [0, 1, 0],
                    [0, 0, 0]
                ]
            }
        };
    }

    initializeGame() {
        // Set up initial board positions
        this.setupInitialBoard();
        
        // Deal cards
        this.dealCards();
    }

    setupInitialBoard() {
        // Player 1 pieces (bottom)
        this.board[4][0] = { type: 'monk', player: 1 };
        this.board[4][1] = { type: 'monk', player: 1 };
        this.board[4][2] = { type: 'master', player: 1 };
        this.board[4][3] = { type: 'monk', player: 1 };
        this.board[4][4] = { type: 'monk', player: 1 };

        // Player 2 pieces (top)
        this.board[0][0] = { type: 'monk', player: 2 };
        this.board[0][1] = { type: 'monk', player: 2 };
        this.board[0][2] = { type: 'master', player: 2 };
        this.board[0][3] = { type: 'monk', player: 2 };
        this.board[0][4] = { type: 'monk', player: 2 };
    }

    dealCards() {
        const cardNames = Object.keys(this.cards);
        const shuffledCards = this.shuffleArray([...cardNames]);
        
        // Deal 2 cards to each player
        this.playerCards[1] = shuffledCards.slice(0, 2);
        this.playerCards[2] = shuffledCards.slice(2, 4);
        
        // Set center card
        this.centerCard = shuffledCards[4];
    }

    shuffleArray(array) {
        const shuffled = [...array];
        for (let i = shuffled.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
        }
        return shuffled;
    }

    selectPiece(row, col) {
        const piece = this.board[row][col];
        
        if (!piece || piece.player !== this.currentPlayer) {
            return false;
        }

        this.selectedPiece = { row, col };
        this.selectedCard = null;
        this.validMoves = this.getValidMoves(row, col);
        return true;
    }

    selectCard(cardName) {
        if (!this.playerCards[this.currentPlayer].includes(cardName)) {
            return false;
        }

        this.selectedCard = cardName;
        this.selectedPiece = null;
        this.validMoves = this.getValidMovesForCard(cardName);
        return true;
    }

    getValidMoves(row, col) {
        const piece = this.board[row][col];
        if (!piece || piece.player !== this.currentPlayer) {
            return [];
        }

        const validMoves = [];
        const availableCards = this.playerCards[this.currentPlayer];

        for (const cardName of availableCards) {
            const cardMoves = this.getValidMovesForCard(cardName, row, col);
            validMoves.push(...cardMoves);
        }

        return validMoves;
    }

    getValidMovesForCard(cardName, fromRow = null, fromCol = null) {
        const card = this.cards[cardName];
        const validMoves = [];

        // If no specific piece is selected, check all pieces
        const piecesToCheck = fromRow !== null && fromCol !== null 
            ? [{ row: fromRow, col: fromCol }]
            : this.getPlayerPieces(this.currentPlayer);

        for (const piece of piecesToCheck) {
            const moves = this.getMovesForPieceWithCard(piece.row, piece.col, card);
            validMoves.push(...moves);
        }

        return validMoves;
    }

    getPlayerPieces(player) {
        const pieces = [];
        for (let row = 0; row < 5; row++) {
            for (let col = 0; col < 5; col++) {
                const piece = this.board[row][col];
                if (piece && piece.player === player) {
                    pieces.push({ row, col });
                }
            }
        }
        return pieces;
    }

    getMovesForPieceWithCard(row, col, card) {
        const moves = [];
        const piece = this.board[row][col];
        
        if (!piece || piece.player !== this.currentPlayer) {
            return moves;
        }

        // Check each possible move based on the card pattern
        for (let dr = -1; dr <= 1; dr++) {
            for (let dc = -1; dc <= 1; dc++) {
                const newRow = row + dr;
                const newCol = col + dc;
                
                if (this.isValidPosition(newRow, newCol)) {
                    const targetPiece = this.board[newRow][newCol];
                    
                    // Check if this move follows the card pattern
                    if (this.isValidMoveByPattern(row, col, newRow, newCol, card.pattern)) {
                        // Check if target is empty or contains opponent piece
                        if (!targetPiece || targetPiece.player !== this.currentPlayer) {
                            moves.push({
                                fromRow: row,
                                fromCol: col,
                                toRow: newRow,
                                toCol: newCol,
                                cardName: card.name
                            });
                        }
                    }
                }
            }
        }

        return moves;
    }

    isValidPosition(row, col) {
        return row >= 0 && row < 5 && col >= 0 && col < 5;
    }

    isValidMoveByPattern(fromRow, fromCol, toRow, toCol, pattern) {
        const dr = toRow - fromRow;
        const dc = toCol - fromCol;
        
        // Check if the move matches the pattern
        const patternRow = dr + 1; // Convert to pattern coordinates
        const patternCol = dc + 1;
        
        if (patternRow < 0 || patternRow >= 3 || patternCol < 0 || patternCol >= 3) {
            return false;
        }
        
        return pattern[patternRow][patternCol] === 1 || pattern[patternRow][patternCol] === 2;
    }

    makeMove(fromRow, fromCol, toRow, toCol, cardName) {
        // Validate the move
        const validMoves = this.getValidMovesForCard(cardName, fromRow, fromCol);
        const isValidMove = validMoves.some(move => 
            move.fromRow === fromRow && 
            move.fromCol === fromCol && 
            move.toRow === toRow && 
            move.toCol === toCol
        );

        if (!isValidMove) {
            return false;
        }

        // Record the move
        const moveRecord = {
            fromRow,
            fromCol,
            toRow,
            toCol,
            cardName,
            player: this.currentPlayer,
            capturedPiece: this.board[toRow][toCol]
        };

        // Execute the move
        this.board[toRow][toCol] = this.board[fromRow][fromCol];
        this.board[fromRow][fromCol] = null;

        // Handle card exchange
        this.exchangeCard(cardName);

        // Record the move
        this.gameHistory.push(moveRecord);

        // Check for win conditions
        if (this.checkWinCondition()) {
            this.gameState = 'gameOver';
            return true;
        }

        // Switch players
        this.currentPlayer = this.currentPlayer === 1 ? 2 : 1;
        
        // Clear selections
        this.selectedPiece = null;
        this.selectedCard = null;
        this.validMoves = [];

        return true;
    }

    exchangeCard(usedCardName) {
        // Remove the used card from current player
        const playerCardIndex = this.playerCards[this.currentPlayer].indexOf(usedCardName);
        if (playerCardIndex !== -1) {
            this.playerCards[this.currentPlayer].splice(playerCardIndex, 1);
        }

        // Add the center card to current player
        if (this.centerCard) {
            this.playerCards[this.currentPlayer].push(this.centerCard);
        }

        // Set the used card as the new center card
        this.centerCard = usedCardName;
    }

    checkWinCondition() {
        // Check if a master has been captured
        const player1Master = this.findMaster(1);
        const player2Master = this.findMaster(2);

        if (!player1Master) {
            return { winner: 2, reason: 'Master captured' };
        }
        if (!player2Master) {
            return { winner: 1, reason: 'Master captured' };
        }

        // Check if a master has reached the opponent's temple
        if (player1Master.row === 0 && player1Master.col === 2) {
            return { winner: 1, reason: 'Master reached temple' };
        }
        if (player2Master.row === 4 && player2Master.col === 2) {
            return { winner: 2, reason: 'Master reached temple' };
        }

        return null;
    }

    findMaster(player) {
        for (let row = 0; row < 5; row++) {
            for (let col = 0; col < 5; col++) {
                const piece = this.board[row][col];
                if (piece && piece.player === player && piece.type === 'master') {
                    return { row, col };
                }
            }
        }
        return null;
    }

    getGameState() {
        return {
            board: this.board,
            currentPlayer: this.currentPlayer,
            gameState: this.gameState,
            selectedPiece: this.selectedPiece,
            selectedCard: this.selectedCard,
            validMoves: this.validMoves,
            playerCards: this.playerCards,
            centerCard: this.centerCard,
            gameHistory: this.gameHistory
        };
    }

    resetGame() {
        this.board = this.createBoard();
        this.currentPlayer = 1;
        this.gameState = 'playing';
        this.selectedPiece = null;
        this.selectedCard = null;
        this.validMoves = [];
        this.gameHistory = [];
        
        this.setupInitialBoard();
        this.dealCards();
    }

    // Utility methods for UI
    getBoardState() {
        return this.board;
    }

    getCurrentPlayer() {
        return this.currentPlayer;
    }

    getPlayerCards(player) {
        return this.playerCards[player] || [];
    }

    getCenterCard() {
        return this.centerCard;
    }

    getValidMovesForDisplay() {
        return this.validMoves;
    }

    isGameOver() {
        return this.gameState === 'gameOver';
    }
}