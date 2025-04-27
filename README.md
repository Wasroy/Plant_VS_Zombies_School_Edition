# Dauphine Defender - Tower Defense Game in C

## Overview

This project is a Tower Defense game developed in C, inspired by "Plants vs Zombies." The player must defend Dauphine University against waves of invading students by strategically placing defense turrets.

Developed as part of the **C Programming** course at Université Paris Dauphine.

## Key Features

- **Tower Defense Game Mechanics**  
- **Different Types of Turrets and Students**  
- **Dynamic ASCII Art-based Grid Display**  
- **Wave System and Save/Load Functionality**  
- **Use of Dynamic Memory and Doubly Linked Lists**

## Project Structure

```
Dauphine_Defender/
├── Source/
│   ├── main.c
│   ├── affichage.c
│   ├── etudiant.c
│   ├── jeu.c
│   ├── tourelles.c
│   ├── *.h (headers)
├── save/            # Save files
├── README.md
```

- `main.c`: Main game loop and general control.
- `affichage.c`: Display the grid and manage colors.
- `etudiant.c`: Handle student enemy behaviors.
- `jeu.c`: Manage game logic, saving, and loading.
- `tourelles.c`: Handle turret behaviors and interactions.

## Installation

1. **Clone the repository:**

```bash
git clone https://github.com/your-username/dauphine-defender.git
cd dauphine-defender
```

2. **Compile:**

```bash
gcc Source/*.c -o dauphine_defender
```

3. **Run:**

```bash
./dauphine_defender
```

## Gameplay

- Start with a few turrets and limited budget.
- Place turrets strategically to prevent students from reaching the university.
- Face increasingly difficult waves including "Basic Students," "Fast Students," and "The Majorant."
- Win by surviving all the waves; lose if students reach the first column.

## Game Entities

**Turrets:**
- Basic Turret (T)
- Long Range Turret (L)
- Powerful Turret (P)
- Explosive Turret (X)
- Auto-repairing Turret (R)

**Students:**
- Sleepy Student (Z)
- Weak Student (A)
- Strong Student (S)
- Fast Student (V)
- The Majorant (M)

## Known Bugs and Optimizations

- **Victory Bug:** Early victory fixed by adding minimum turn count.
- **Display of Health:** Solved by dynamic color changes instead of displaying numerical health.
- **Optimization in `attaquer_tourelles()`:** Improved attack handling to prevent attacks on deleted turrets.

## Tools and Resources Used

- **Programming:** Visual Studio Code
- **Documentation:** Overleaf (LaTeX)
- **Communication:** Discord, Trello
- **Resources:** Wikipedia, YouTube tutorials, GitHub

## Developers

- **Rayan Bourgou**
- **William Miserolle**

---

*Project completed in April 2025.*

---

"In C programming, everything works... until a segmentation fault appears."
