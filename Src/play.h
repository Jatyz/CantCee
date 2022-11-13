#pragma once

// Level Slection First Row Height
#define firstRowHeight (windowHeight / 2) - 200
#define secondRowHeight (windowHeight / 2) - 50
#define thirdRowHeight (windowHeight / 2) + 100


// First Column
#define firstColumn (windowWidth / 2) - 330
// Second Column
#define secondColumn (windowWidth / 2) - 210 // difference of 120
// Third Column
#define thirdColumn (windowWidth / 2) - 90
// Fourth Column
#define fourthColumn (windowWidth / 2) + 30
// Fifth Column
#define fifthColumn (windowWidth / 2) + 150

// backToMainMenu Button
#define exitHeight thirdRowHeight + 150
// playButton Height
#define playHeight thirdRowHeight + 150

#define titleX (windowWidth / 2) - 90
#define titleY (windowHeight / 2) - 320




void play_Init(void);

void play_Update(void);

void play_Exit(void);