# Marrakech Game 🕌🎲

This is a terminal-based C++ implementation of the classic board game **Marrakech**, created as an academic project for the *"Introducción a la programación"* course, under the Department of Systems Engineering.

In Marrakech, players compete to dominate the carpet market by placing rugs, collecting coins, and strategically maneuvering the merchant Hassam across a 7x7 plaza.

---

## 📋 Game Overview

- 👥 2 players  
- 🎨 Each player has:  
  - 10 rugs (in a selected color)  
  - 20 coins  
- 🧍 Hassam starts at the center of the board (3,3) and moves each turn  
- 🎯 The goal is to outlast your opponent or have the highest score by the end  

---

## 🧠 Main Mechanics

Each turn consists of:

1. **Orienting Hassam**: Choose a direction (left, right, or keep current).
2. **Rolling the die**: Move Hassam in a straight line.
3. **Paying the opponent**: If landing on opponent rugs, pay 1 coin per connected tile.
4. **Placing a rug**: Place a 2-tile rug adjacent to Hassam based on placement rules.

---

## 🔍 Notable Algorithm

To compute the payment when a player lands on an opponent's rug, a **flood fill-style search algorithm** is used. It explores all contiguous rug segments of the same color to calculate how many coins should be paid. This is done using a stack to traverse the 2D board — a typical connected-component search.

---

## 🧪 Features

- ANSI-colored console interface for rug visualization
- Interactive turn-based gameplay for 2 players
- Dynamic orientation and movement of Hassam
- Real-time rug placement and validation
- Player elimination and final score calculation
- Automatic save of results to a file (`partida.txt`)

---

## ⚙️ How to Compile & Run

### Requirements:
- C++17 compiler or higher

### Compile:
```bash
g++ -std=c++17 -o marrakech main.cpp
```

### Run:
```bash
./marrakech
```

> You can also use any C++ IDE that supports console input/output.

---

## 📤 Program Output

### Terminal Output
During gameplay, the terminal shows:
- A 7x7 board with rugs and Hassam's current position
- Player status (coins, rugs)
- Valid rug placement options
- Payment calculation if stepping on opponent rugs
- Final score and winner announcement

### partida.txt (Saved Output)
After the game ends, the program generates a summary in a file named `partida.txt`. Example:

```
Nombre: Alice
Color: R
Cantidad de alfombras: 14
Cantidad de monedas: 5

Nombre: Bob
Color: A
Cantidad de alfombras: 13
Cantidad de monedas: 4

El ganador es Alice
```

---

## 📁 Project Structure

```
marrakech-game/
├── main.cpp         # Full source code of the game
├── partida.txt      # Auto-generated result file
├── README.md        # This documentation
```

---

## 🚀 Future Improvements

- AI opponent (e.g. with decision trees or Monte Carlo simulations)
- Graphical interface using SFML, SDL, or Qt
- Multiplayer mode over local network
- Save/load support during gameplay
- Game replays and performance stats

---

## 👤 Author

**Juan Enrique Rozo Tarache**  
Student – Pontificia Universidad Javeriana
GitHub: [@JuanR771](https://github.com/JuanR771)

> Developed as part of the final project for the course *Introducción a la programación* – Departamento de Ingeniería de Sistemas.

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
