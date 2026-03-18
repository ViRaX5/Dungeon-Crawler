# Dungeon Crawler Game Engine (C++)

A command-driven dungeon crawler game engine developed in C++, featuring modular object-oriented design and multiple interacting gameplay systems including combat, inventory, map navigation, and dynamic entity management.

---

## 🎮 Overview

This project implements a fully functional dungeon crawler where the game world is constructed and controlled באמצעות (via) structured input commands.  

Players can create characters, explore rooms, fight monsters, collect items, and progress through a dynamically built dungeon.

---

✨ Features

🧍 Character System
- Multiple playable classes: **Warrior, Thief, Mage**
- Each class has unique base stats (Health, Strength, Defense)
- Equipment restrictions per class

🗺️ Dungeon & Map System
- Dynamic room creation
- Rooms stored using a **linked list data structure**
- Directional connections (North, South, East, West)
- Validation rules (no duplicate or invalid connections)

⚔️ Combat System
- Turn-based combat
- Player attacks first
- Damage formula: damage = max(1, attacker STR − defender DEF)
- Persistent health across battles

👾 Monsters
- Monsters placed dynamically in rooms
- Customizable stats (health, strength, defense)
- One monster per interaction context

🎒 Inventory & Items
- Equipment system (weapons & shields)
- Potions (health, strength, defense) applied instantly
- Smart equipment replacement:
- Keeps strongest item automatically
- Item stat bonuses and upgrades

🚶 Movement System
- Player movement between connected rooms
- Validation of valid directions and paths
- Error handling for invalid moves

🧾 Command-Based Engine
The game is controlled באמצעות text commands such as:

- `create room`
- `connect`
- `place`
- `enter dungeon`
- `move`
- `fight`
- `pickup`

---

🧠 Technical Highlights

- Object-Oriented Design with multiple interacting classes (Game, Character, Room, Item, Monster)
- Custom **linked list implementation** for managing entities :contentReference[oaicite:0]{index=0}  
- Command parsing engine using `stringstream` for dynamic execution :contentReference[oaicite:1]{index=1}  
- Separation of concerns between:
- Game logic
- Data structures
- Input processing
- Robust error handling for invalid actions and inputs

---

🏗️ Architecture

The system is structured into several core components:

- **Game Engine**
- Handles command execution and game flow  
- Manages players, dungeon, and interactions  

- **Dungeon / Room System**
- Stores rooms and connections  
- Handles navigation and entity placement  

- **Character System**
- Player classes with stats and inventory  
- Combat and item interaction logic  

- **Item & Inventory System**
- Equipment and potions with stat effects  
- Dynamic item comparison and replacement  

- **Combat System**
- Turn-based battle loop implementation :contentReference[oaicite:2]{index=2}  

---

⚙️ Technologies Used

- C++  
- Standard Template Library (STL)  
- Object-Oriented Programming (OOP)  
- File I/O and command parsing  

---

🚀 How to Run

1. Clone the repository:
 git clone https://github.com/your-repo/dungeon-crawler.git
2. Navigate to the project directory:
 cd dungeon-crawler
3. Compile the project:
   g++ *.cpp -o dungeon
4. Prepare an input file (e.g., input.txt) with game commands
5. Run the game:
   ./dungeon

📂 Input / Output
 - The game reads commands from an input file
 - Executes them sequentially
 - Outputs final game state to a file

📌 Future Improvements
 - Smarter AI behavior for enemies
 - Graphical interface (GUI)
 - Save/load game state
 - Multiple players interacting simultaneously
 - Enhanced combat mechanics

👤 Authors
  Amit Lachmann
  Noam Eilat
