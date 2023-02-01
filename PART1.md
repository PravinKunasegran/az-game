# Part 1

## Video Demo

The attached document contains a link to a YouTube video that my team and I have included for submission  convenience and reference  [Video Demo](https://www.youtube.com/watch?v=pcQ52VG0MW4).

## Minimum Requirements

### Completed

The list of  features that have been completed .

1. Overview of Alien vs. Zombie 
- Prior to the game, the player can customize settings including game board dimensions and number of zombies.
2. Game Board 
- The game is played on two-dimensional board that contains game characters and objects. No characters or objects can be placed outside the board. The dimensions of the game board must be odd numbers   so that the Alien can be placed at the centre of the game board. For game board with 10 or more rows or columns, ensure that the row and column numbers are displayed correctly.
3. Game Characters 
- Alien and Zombie are game characters.
4. Game Characters Movement 
- Both Alien and Zombie can move but also limited inside the gameboard   
5. Game Objects 
- Apart from the game characters, the game board also contains game objects such as :
 Arrow {^ (up),v (down), < (left), > (right)} , Health {h} ,Pod {p}, Rock {r}, Empty  {Space} 
 6. Game Control 
 - The player plays the game by typing command , until Alien movements 
 7. Multiple Zombie - Able to customize the number of zombie  
### To Do

List of  all the features on which is incomplete  (ON PROGRESS ). 

1. Game Characters and Object Attributes 
- Objects funtionality and Game Charaters Attack and Life values  
2. Saving and Loading Game File 
- When saving a game,have  that the data is stored correctly so that it can be loaded successfully. After saving, the player will continue to play the ongoing game

## Additional Features

Invisible border for Game charaters to now move outside  of the Game Board 
Added condition for only odd number is allowed in Game Board customization (Row and Collums)

## Contributions

As a leader, I have taken  measures to fairly distribute the contributions made by each member of the team, promoting equality, workload and teamwork.

As specified contribution is  listed down of each group member:

### PRAVIN KUNASEGRAN-(1221303877)

1. Overview of Alien vs. Zombie
2. Alien Movement & Attacks 
3. Documentation & Git-hub Setup
4. Game Controls 

###  MALINY A/P THANARAJ-(1211100910)

1. Game Characters & Game board 
2. Zombie movement and attack behaviour.
3. Implement all game objects.
4. Game Controls 

### MAEVINARSH A/L LOGANATHAN-(1211103476)

1. Game Board 
2. Game Objects
3. Video Demonstration 
4. Game Controls 

## Problems Encountered & Solutions

1. Game Board customization accepting even numbers for rows and collums - Solved inserted an condition for row and collums and debuged  
1. Alien is not centered in gameboard  
- A bug in the code, it may cause the Alien to not be centered will be solve in further submission 
2. Zombie is not spawning 
- Checked the code for the spawn point of the Zombie. Founded that the incorrect coordinates are being used and that the Zombie is being placed on the game board will be solve in further submission 
3. Alien not able follow the command 
-  Logic Error.The logic for moving the Alien may be incorrect will be solve in further submission 