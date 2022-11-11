// ---------------------------------------------------------------mainMenu Headers---------------------------------------------------------------
// 
// 
// ---------------------------------------------------------------Global Variables---------------------------------------------------------------
// Window Size
#define windowWidth 1000.f
#define windowHeight 800.f

// Button Size
#define buttonWidth 300.f
#define buttonHeight 76.f // for all 4 buttons on main menu

// levelSelection buttons
#define levelButtonWidth 100.f
#define levelButtonHeight 100.f

// level Selection Pop-up screen
#define popUpWidth 400.f
#define popUpHeight 400.f



// mainMenu Button Size
#define mainMenuButtonWidth 300.f		// for all 5 buttons on main menu
#define mainMenuButtonHeight 76.f 

// startWord
#define startWordWidth (windowWidth / 2)
#define startWordHeight (windowHeight / 2) - 70

// howToPlayWord
#define howToPlayWordWidth (windowWidth / 2)
#define howToPlayWordHeight (windowHeight / 2) + 30

// Credits
#define creditsWordWidth (windowWidth / 2)
#define creditsWordHeight (windowHeight / 2) + 130

// Settings
#define settingsWordWidth (windowWidth / 2)
#define settingsWordHeight (windowHeight / 2) + 230

// Exit
#define exitWordWidth (windowWidth / 2)
#define exitWordHeight (windowHeight / 2) + 330

void mainMenu_Init(void);

void mainMenu_Update(void);

void mainMenu_Exit(void);