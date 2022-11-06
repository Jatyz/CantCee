If your project cant work make sure to check
 in extern

you have c processing, all the required files, as it might not be transferred over github.

Files in resources might not be transffered as well, need to check

project settings
make sure debugging > working directory
$(SolutionDir)bin\$(Configuration)-$(Platform)\

everything else shld be fine, if not js check wif ur own project and compare

(How to add enemies)

Call "enemies[width][height].type" to add enemies. ".type" tells the game which enemy to generate. Currently there are 2 enemies, "TWO_WAY_LOOK" and "AOE_VIEW". Then , call "enemies[width][height].isActive' to activate the enemy. Setting it to 0 will disable the enemy, anything other than 0 will activate the enemy.

TWO_WAY_LOOK: Enemy looks at x and y axis.

AOE_VIEW: Enemy looks at either 8 or 24 grids. Setting .isActive to 1 will give it 8 grids to check and setting .isActive to 2 will give it 24 grids to check.