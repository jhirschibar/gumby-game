class JodyTamaUI {
    constructor(game) {
        this.game = game;
        this.boardElement = document.getElementById('game-board');
        this.player1CardsElement = document.querySelector('#player1-cards .cards-container');
        this.player2CardsElement = document.querySelector('#player2-cards .cards-container');
        this.centerCardElement = document.querySelector('#center-card .card-display');
        this.turnIndicator = document.getElementById('turn-indicator');
        this.gameStatus = document.getElementById('game-status');
        
        this.selectedPiece = null;
        this.selectedCard = null;
        this.validMoves = [];
        
        this.initializeUI();
        this.bindEvents();
    }

    initializeUI() {
        this.createBoard();
        this.updateDisplay();
    }

    createBoard() {
        const boardGrid = document.createElement('div');
        boardGrid.className = 'board-grid';
        
        for (let row = 0; row < 5; row++) {
            for (let col = 0; col < 5; col++) {
                const square = document.createElement('div');
                square.className = 'board-square';
                square.dataset.row = row;
                square.dataset.col = col;
                
                // Mark temple squares
                if ((row === 0 && col === 2) || (row === 4 && col === 2)) {
                    square.classList.add('temple');
                }
                
                boardGrid.appendChild(square);
            }
        }
        
        this.boardElement.appendChild(boardGrid);
    }

    updateDisplay() {
        this.updateBoard();
        this.updateCards();
        this.updateTurnIndicator();
        this.updateGameStatus();
    }

    updateBoard() {
        const board = this.game.getBoardState();
        const squares = document.querySelectorAll('.board-square');
        
        squares.forEach(square => {
            const row = parseInt(square.dataset.row);
            const col = parseInt(square.dataset.col);
            const piece = board[row][col];
            
            // Clear previous content
            square.innerHTML = '';
            square.className = 'board-square';
            
            // Add temple class if needed
            if ((row === 0 && col === 2) || (row === 4 && col === 2)) {
                square.classList.add('temple');
            }
            
            // Add piece if present
            if (piece) {
                const pieceElement = document.createElement('div');
                pieceElement.className = `piece ${piece.type} ${piece.player === 2 ? 'player2' : ''}`;
                pieceElement.textContent = piece.type === 'master' ? 'M' : 'm';
                square.appendChild(pieceElement);
            }
            
            // Highlight selected piece
            if (this.selectedPiece && this.selectedPiece.row === row && this.selectedPiece.col === col) {
                square.classList.add('selected');
            }
            
            // Highlight valid moves
            if (this.isValidMove(row, col)) {
                square.classList.add('valid-move');
            }
        });
    }

    updateCards() {
        this.updatePlayerCards(1);
        this.updatePlayerCards(2);
        this.updateCenterCard();
    }

    updatePlayerCards(player) {
        const cards = this.game.getPlayerCards(player);
        const container = player === 1 ? this.player1CardsElement : this.player2CardsElement;
        
        container.innerHTML = '';
        
        cards.forEach(cardName => {
            const cardElement = this.createCardElement(cardName, player);
            container.appendChild(cardElement);
        });
    }

    updateCenterCard() {
        const centerCardName = this.game.getCenterCard();
        if (centerCardName) {
            this.centerCardElement.innerHTML = '';
            const cardElement = this.createCardElement(centerCardName, 'center');
            this.centerCardElement.appendChild(cardElement);
        }
    }

    createCardElement(cardName, player) {
        const card = this.game.cards[cardName];
        const cardElement = document.createElement('div');
        cardElement.className = 'card';
        cardElement.dataset.cardName = cardName;
        
        if (player !== 'center') {
            cardElement.dataset.player = player;
        }
        
        // Highlight selected card
        if (this.selectedCard === cardName) {
            cardElement.classList.add('selected');
        }
        
        const cardContent = document.createElement('div');
        cardContent.innerHTML = `
            <div class="card-name">${cardName}</div>
            <div class="move-pattern">
                ${this.createPatternHTML(card.pattern)}
            </div>
        `;
        
        cardElement.appendChild(cardContent);
        return cardElement;
    }

    createPatternHTML(pattern) {
        let html = '';
        for (let row = 0; row < 3; row++) {
            for (let col = 0; col < 3; col++) {
                const cellClass = pattern[row][col] > 0 ? 'active' : 'inactive';
                const cellText = pattern[row][col] === 2 ? '2' : pattern[row][col] === 1 ? '1' : '';
                html += `<div class="pattern-cell ${cellClass}">${cellText}</div>`;
            }
        }
        return html;
    }

    updateTurnIndicator() {
        const currentPlayer = this.game.getCurrentPlayer();
        this.turnIndicator.textContent = `Player ${currentPlayer}'s Turn`;
    }

    updateGameStatus() {
        if (this.game.isGameOver()) {
            const winCondition = this.game.checkWinCondition();
            if (winCondition) {
                this.gameStatus.textContent = `Player ${winCondition.winner} wins!`;
                this.showGameOverModal(winCondition);
            }
        } else {
            this.gameStatus.textContent = 'Game in Progress';
        }
    }

    bindEvents() {
        // Board click events
        this.boardElement.addEventListener('click', (e) => {
            if (e.target.classList.contains('board-square')) {
                this.handleBoardClick(e.target);
            }
        });

        // Card click events
        this.player1CardsElement.addEventListener('click', (e) => {
            if (e.target.closest('.card')) {
                this.handleCardClick(e.target.closest('.card'));
            }
        });

        this.player2CardsElement.addEventListener('click', (e) => {
            if (e.target.closest('.card')) {
                this.handleCardClick(e.target.closest('.card'));
            }
        });

        // Control buttons
        document.getElementById('new-game-btn').addEventListener('click', () => {
            this.resetGame();
        });

        document.getElementById('rules-btn').addEventListener('click', () => {
            this.showRulesModal();
        });

        // Modal events
        document.getElementById('play-again-btn').addEventListener('click', () => {
            this.resetGame();
            this.hideGameOverModal();
        });

        document.getElementById('close-modal-btn').addEventListener('click', () => {
            this.hideGameOverModal();
        });

        document.getElementById('close-rules-btn').addEventListener('click', () => {
            this.hideRulesModal();
        });

        // Close modals when clicking outside
        window.addEventListener('click', (e) => {
            if (e.target.classList.contains('modal')) {
                this.hideGameOverModal();
                this.hideRulesModal();
            }
        });
    }

    handleBoardClick(squareElement) {
        const row = parseInt(squareElement.dataset.row);
        const col = parseInt(squareElement.dataset.col);
        
        // If a piece is selected and this is a valid move
        if (this.selectedPiece && this.isValidMove(row, col)) {
            this.makeMove(row, col);
            return;
        }
        
        // If a card is selected, try to select a piece
        if (this.selectedCard) {
            const piece = this.game.getBoardState()[row][col];
            if (piece && piece.player === this.game.getCurrentPlayer()) {
                this.selectPiece(row, col);
                this.updateDisplay();
            }
            return;
        }
        
        // Try to select a piece
        this.selectPiece(row, col);
        this.updateDisplay();
    }

    handleCardClick(cardElement) {
        const cardName = cardElement.dataset.cardName;
        const player = cardElement.dataset.player;
        
        // Only allow selecting cards for current player
        if (parseInt(player) === this.game.getCurrentPlayer()) {
            this.selectCard(cardName);
            this.updateDisplay();
        }
    }

    selectPiece(row, col) {
        if (this.game.selectPiece(row, col)) {
            this.selectedPiece = { row, col };
            this.selectedCard = null;
            this.validMoves = this.game.getValidMovesForDisplay();
        }
    }

    selectCard(cardName) {
        if (this.game.selectCard(cardName)) {
            this.selectedCard = cardName;
            this.selectedPiece = null;
            this.validMoves = this.game.getValidMovesForDisplay();
        }
    }

    makeMove(toRow, toCol) {
        if (!this.selectedPiece || !this.selectedCard) {
            return;
        }
        
        const success = this.game.makeMove(
            this.selectedPiece.row,
            this.selectedPiece.col,
            toRow,
            toCol,
            this.selectedCard
        );
        
        if (success) {
            this.selectedPiece = null;
            this.selectedCard = null;
            this.validMoves = [];
            this.updateDisplay();
        }
    }

    isValidMove(row, col) {
        return this.validMoves.some(move => 
            move.toRow === row && move.toCol === col
        );
    }

    resetGame() {
        this.game.resetGame();
        this.selectedPiece = null;
        this.selectedCard = null;
        this.validMoves = [];
        this.updateDisplay();
    }

    showGameOverModal(winCondition) {
        const modal = document.getElementById('game-over-modal');
        const title = document.getElementById('game-over-title');
        const message = document.getElementById('game-over-message');
        
        title.textContent = 'Game Over!';
        message.textContent = `Player ${winCondition.winner} wins by ${winCondition.reason.toLowerCase()}!`;
        
        modal.classList.remove('hidden');
    }

    hideGameOverModal() {
        const modal = document.getElementById('game-over-modal');
        modal.classList.add('hidden');
    }

    showRulesModal() {
        const modal = document.getElementById('rules-modal');
        modal.classList.remove('hidden');
    }

    hideRulesModal() {
        const modal = document.getElementById('rules-modal');
        modal.classList.add('hidden');
    }
}