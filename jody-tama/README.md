# Jody-Tama

A browser-based implementation of the Onitama board game, featuring a 5x5 grid with strategic piece movement and card-based gameplay.

## 🎮 How to Play

### Objective
Win by either:
- Capturing the opponent's Master piece
- Moving your Master to the opponent's Temple square (center of their back row)

### Setup
- Each player starts with 4 Monks and 1 Master on their side of the 5x5 board
- 5 move cards are dealt from a deck of 17 unique cards
- Each player receives 2 cards, with 1 card in the center

### Gameplay
1. **On your turn**, choose one of your cards and move a piece according to that card's pattern
2. **After moving**, that card goes to the center and you receive the center card
3. **Cards show movement patterns** relative to the piece's current position
4. **You can only move to empty squares** or capture opponent pieces
5. **The game continues** until one player achieves a win condition

### Card Movement Patterns
Each card displays a 3x3 grid showing valid movement patterns:
- **Active cells** (blue) show where the piece can move
- **Numbers** indicate special movement (e.g., "2" for Tiger card's long jump)
- **Empty cells** (gray) are invalid moves

## 🚀 Getting Started

### Prerequisites
- A modern web browser (Chrome, Firefox, Safari, Edge)
- No additional software required

### Installation
1. Clone or download this repository
2. Navigate to the `jody-tama` directory
3. Open `index.html` in your web browser

### Running the Game
```bash
# If you have a local server (optional)
python -m http.server 8000
# Then open http://localhost:8000/jody-tama/
```

## 🎯 Game Features

### Core Gameplay
- ✅ Complete Onitama rules implementation
- ✅ All 17 original movement cards
- ✅ Real-time move validation
- ✅ Win condition detection
- ✅ Turn-based gameplay

### User Interface
- 🎨 Modern, responsive design
- 🖱️ Intuitive click-based controls
- 🎯 Visual move highlighting
- 📱 Mobile-friendly layout
- 🎮 Interactive card selection

### Game Controls
- **Click a piece** to select it and see valid moves
- **Click a card** to select it and see valid moves for all pieces
- **Click a highlighted square** to make a move
- **New Game** button to start a fresh game
- **Rules** button to view game instructions

## 🏗️ Technical Architecture

### File Structure
```
jody-tama/
├── index.html          # Main HTML file
├── styles.css          # CSS styling
├── game-engine.js      # Core game logic
├── ui-controller.js    # User interface handling
├── main.js            # Application initialization
└── README.md          # This file
```

### Components

#### Game Engine (`game-engine.js`)
- **Board Management**: 5x5 grid with piece tracking
- **Move Validation**: Ensures moves follow card patterns
- **Card System**: All 17 Onitama cards with movement patterns
- **Win Detection**: Master capture and temple victory conditions
- **State Management**: Game state, player turns, history

#### UI Controller (`ui-controller.js`)
- **Board Rendering**: Visual representation of the game board
- **Card Display**: Interactive card selection and pattern visualization
- **User Interaction**: Click handling and move execution
- **Visual Feedback**: Highlighting selected pieces and valid moves
- **Modal Management**: Game over and rules dialogs

#### Styling (`styles.css`)
- **Responsive Design**: Works on desktop and mobile
- **Modern UI**: Clean, professional appearance
- **Visual Hierarchy**: Clear distinction between elements
- **Interactive States**: Hover effects and selections

## 🎲 Game Rules in Detail

### Piece Types
- **Master**: The most important piece. Losing it means losing the game
- **Monks**: Regular pieces that can capture and be captured

### Movement Rules
1. **Card-Based**: Each move must follow a card's pattern
2. **Relative Movement**: Patterns are relative to the piece's position
3. **Capture**: Moving to a square with an opponent's piece captures it
4. **No Friendly Fire**: Cannot move to squares occupied by your own pieces

### Card Exchange
1. **Use a Card**: When you make a move, you use one of your cards
2. **Receive Center Card**: You receive the card that was in the center
3. **Update Center**: Your used card becomes the new center card

### Victory Conditions
1. **Master Capture**: Capture the opponent's Master piece
2. **Temple Victory**: Move your Master to the opponent's Temple square

## 🛠️ Development

### Debugging
The game includes debugging utilities accessible via the browser console:
```javascript
// Access game engine
window.jodyTamaGame

// Access UI controller
window.jodyTamaUI

// Log current game state
JodyTamaUtils.logGameState()

// Test a specific move
JodyTamaUtils.testMove(fromRow, fromCol, toRow, toCol, cardName)
```

### Extending the Game
- **New Cards**: Add to the `createCards()` method in `game-engine.js`
- **UI Enhancements**: Modify `ui-controller.js` for new features
- **Styling**: Update `styles.css` for visual changes

## 📱 Browser Compatibility

- ✅ Chrome 60+
- ✅ Firefox 55+
- ✅ Safari 12+
- ✅ Edge 79+

## 🎨 Design Philosophy

The game emphasizes:
- **Accessibility**: Clear visual feedback and intuitive controls
- **Responsiveness**: Works seamlessly across different screen sizes
- **Performance**: Smooth animations and responsive interactions
- **User Experience**: Minimal learning curve with comprehensive rules

## 🤝 Contributing

Feel free to contribute improvements:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is open source and available under the MIT License.

---

**Enjoy playing Jody-Tama!** 🎮