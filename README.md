# Naval-Battleship

## Introduction and Game rules
It is a 2-player game(human vs bot, human vs human) which each player has a field containing 5 ships(which may be 
either vertical or horizontal) on it. There are 4 different types of ships according to their sizes. One 2-block, 
two 3-block, one 4-block and one 5-block ships are what have to be on the field of each player. After placing the 
ships, each player starts to fire the blocks. In case of succesful shot to an enemy ship, it is still the shooter's 
turn to shoot again. Otherwise, it is the other player's turn to play. The game ends when all of the ships of a 
player are fired up and it shows up **YOU WIN!** animation on the screen for 3 seconds before closing by itself.

## How to launch
After downloading or cloning the game in your computer, open up the terminal from the folder containing the game files.
And then type
- to play with a human: **_./bs_**
- to play with a bot: **_./bs -b [difficulty level]_**
- to make 2 bots play **_./bs -b [difficulty level1] [difficulty level2]_**

_Note:_ There are 2 difficulty levels: easy and normal. To play with an easy bot type
0, with a normal bot 1. I am thinking to add a hard bot(2) for the future though.

## How to play
The game has 2 modes: **Human vs Human** and **Human vs Bot**.

It has a GUI, and it is played with mouse. There are 2 fields in the window of each player.
The field on the left side is to shoot or fire enemy ships while the one on the right side is to place and see your ships 
as well as to know what blocks the enemy is shooting.

The first step is placing the ships. Thus, a player should choose its ship from the left side of the window
and place it on the right side appropriately. To place vertical or horizontal ship click the right button of mouse.
After placing, the game starts and you should use the left side of the window to shoot at the enemy field.