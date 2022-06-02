

// *******************************************************************END SEMESTER PROJECT*****************************************************************

//                                                                       ~~~~~~BY~~~~~~

/*
                                                                1. Syed Umer Tariq
                                                                2. Hasan Iqtedar
                                                                3. Zaid bin Tariq
                                                                4. Tayyab Ahmed

~~~~~~  BSCS 9 A ~~~~~~
*/


/*NOTE:
We did not use anything that is beyond the scope of our course.

We did use ANSI color codes for making it colorful, but they are simple and work like escape sequences,
so we think that is not BEYOND THE SCOPE of our course. The project works fine without them as well.

"ANSI CODE"        "COLOR"

\x1b[36m           cyan
\x1b[33m           yellow
\x1b[0m            white
*/


#include <stdio.h>
#include <windows.h>//for Sleep();
#include <time.h>//for rand(); & srand();

char rules[8] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };  // Array that stores the rules,both default and custom.
char rowNew[200];       // Array to store current generation
char rowOld[200];       // Array to store the Next generation
char alive = 'O';         // using 'O' Character to represent alive

void drawLogo(); // Call This function whenever you need to draw the logo
char keyboardIn(); // function for input from keyboard( Arrow keys + Enter)
void mainMenu(); // The main menu logic
void tutorial(); // This function contains the whole tutorial
void credits(); // the credits function
void startingCombination(); // Function to setup starting combo( Random or singular)
void nextGen(); // Generating the next generation
void drawRow(); // Draws each row( 1 generation)
char checkRules(char, char, char); // Checks the rules for every generation
void customRules(); // To set rules by user
void selectRules(int selected); //User choice to make his own rules or to select a preset
void play(); // the function in which the simulation runs
void simulationRules(); // function deals with setting up the rules



//********************************************************************************************************************
//********************************************  MAIN FUNCTION ********************************************************
//********************************************************************************************************************
int main()
{
	srand(time(NULL));
	mainMenu();
}
//********************************************************************************************************************
//********************************************************************************************************************

//***********************************************    DRAW LOGO FUNCTION    *******************************************
void drawLogo()
{

	system("cls"); //Logo will always on the top, so the screen will be cleared first

	// Drawing the Logo using printf and escape sequences
	printf("\t\t\t\t\t\t\t\t\t\x1b[33m~~~~~\x1b[0m  W O L F A R M ' S     E L E M E N T A R Y  \x1b[33m~~~~~\x1b[0m\n");
	printf("\t\t\t\t\t\t\t\x1b[36m _____       _  _       _              _____       _                     _              \n");
	printf("\t\t\t\t\t\t\t|    _| ___ | || | _ _ | | ___  ___   |  _  | _ _ | |_  ___  _____  ___ | |_  ___  ___  \n");
	printf("\t\t\t\t\t\t\t|   |_ | -_|| || || | || || . ||  _|  |     || | ||  _|| . ||     || . ||  _|| . ||   | \n");
	printf("\t\t\t\t\t\t\t|_____||___||_||_||___||_||__;||_|    |__|__||___||_|  |___||_|_|_||__;||_|  |___||_|_| \x1b[0m \n");
	printf("\t\t\t\t\t\t\t\t __            _  _     _  _     _         _      ___      __       __ \n");
	printf("\t\t\t\t\t\t\t\t(__      |     |\\/|     |  |     |        /_\\      |      /  \\     |__)\n");
	printf("\t\t\t\t\t\t\t\t __)     |     |  |     |__|     |__     /   \\     |      \\__/     |  \\ \n\n");
}

//**********************************************     INPUT FUNCTION      *********************************************
char keyboardIn()
{

	if (getch() == 13)     // 13 is the code for enter key
		return 'e';     // If enter is pressed, returns 'e'

	// note: turns out that arrow keys give us two values, first one for all arrows is same, so that gets wasted in the above getch();
	// so we use getch(); again to get the second value

	char kp = getch();    // saving the user input in a variable
	switch (kp)
	{
	case 72:        // 72 is the code for Up arrow key
		return 'u';

	case 80:        // 80 is the code for Down arrow key
		return 'd';

	case 75:        // 75 is the code for Left arrow key
		return 'l';

	case 77:        // 77 is the code for Right arrow key
		return 'r';
	default:
		getch();    // we need to keep the values entered to be even because we are using two getch, so if user presses any key, this getch() balances it
	}
}

//*********************************************    MAIN_MENU FUNCTION    *********************************************
void mainMenu()
{

	int selection = 0;   // Variable to store the currently selected option, "Start Tutorial" selected by default(at selection = 0)
	int quit = 0;        // Used to run the while loop unless exit is selected
	char keyPressed;     // Variable to store user input

	while (!quit)         // the loop will run unless we select exit
	{

		drawLogo();      //Logo on the top
		printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m\n\n\n");

		/*There are two state of the button, Active and Not Active, when it is selected i.e the "selection" variable has  its corresponding value,
		it will be active, else it will be Not active.
		*/
		//The "Start Tutorial" button(Active at selection = 0)
		if (selection == 0)
			printf("\t\t\t\t\t\t\t\t\t\t\x1b[33m     %c%c >>>> Start Tutorial <<<< %c%c\x1b[0m\n\n\n", 219, 219, 219, 219); // Active
		else
			printf("\t\t\t\t\t\t\t\t\t\t\t~~~~ Start Tutorial ~~~~ \n\n\n"); // Not Active


		//The "Start Simulation" button(Active at selection = 1)
		if (selection == 1)
			printf("\t\t\t\t\t\t\t\t\t\t\x1b[33m     %c%c >>> Start Simulation <<< %c%c \x1b[0m\n\n\n", 219, 219, 219, 219); // Active
		else
			printf("\t\t\t\t\t\t\t\t\t\t\t~~~ Start Simulation ~~~ \n\n\n"); // Not Active


		//The "Credits" button(Active at selection = 2)
		if (selection == 2)
			printf("\t\t\t\t\t\t\t\t\t\t\x1b[33m     %c%c >>>>>>>> Credits <<<<<<< %c%c\x1b[0m\n\n\n", 219, 219, 219, 219); // Active
		else
			printf("\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~ Credits ~~~~~~~ \n\n\n"); // Not Active


		//The "Exit" button(Active at selection = 3)
		if (selection == 3)
			printf("\t\t\t\t\t\t\t\t\t\t\x1b[33m     %c%c >>>>>>>>> Exit <<<<<<<<< %c%c \x1b[0m\n\n", 219, 219, 219, 219);
		else
			printf("\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ Exit ~~~~~~~~~ \n\n");

		printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
		printf("\n\n\nNOTE: Use UP ARROW and DOWN ARROW Keys to cycle, ENTER to select.");

		keyPressed = keyboardIn(); //After drawing the Main menu, we call the user input function and save the user input in the variable keyPressed

		if (keyPressed == 'e')       // the keyboardIn() function returns 'e' if enter is pressed
		{
			switch (selection)       // when enter is pressed, we check which option is selected.
			{
			case 0:             // if selection variable is 0, then "start tutorial" is selected
				tutorial();
				break;

			case 1:             // if selection variable is 1, then "start simulation" is selected
				play();         // call the play function
				break;


			case 2:             // if selection variable is 2, then "Credits" is selected
				credits();      // call the credits function
				break;

			case 3:             // if selection variable is 0, then "Exit" is selected
				quit = 1;       //break out of the loop and end the program
				drawLogo();
				printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");

				printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t       B   Y   E   !\n\n\n\n\n\n\n\n");
				printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");

				break;

			}
		}
		else                       // if Enter is not pressed
		{
			switch (keyPressed)     // We only check for UP and DOWN arrows
			{
			case 'u':          // the keyboardIn() function returns 'u' if UP arrow is pressed
				if (selection == 0)// if first option is selected
					selection = 3;// go to last
				else
					selection--;//otherwise go up one option
				break;
			case 'd':           // the keyboardIn() function returns 'e' if enter is pressed
				if (selection == 3)
				selection = 0; // if first button is selected then select the last one
			else
				selection++; // else select the button below the currently selected
				break;

			}
		}

	}


}

//************************************************    TUTORIAL  FUNCTION    ******************************************
void tutorial()
{
	//                              USING PRINTF, LOOPS And Escape sequences to show some infographics
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t NOTE: \n\n  ");
	printf("\t\t\t\t\t\t\t\t Press ENTER key to continue when you see\x1b[33m \' %c \' \x1b[0m in this tutorial \n\n  ", 175);
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t       \x1b[33m  %c  \x1b[0m  ", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");

	while (getch() != 13); // To make sure only enter key is pressed

	drawLogo();// Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t  First, Lets Learn how Cellular Automaton works.\n\n  ");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m",175);
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\t\t\t\t\t\t\t\t      Consider a row of cells:  \n\n\t\t\t\t\t\t\t\t     ");

	for (int x = 0; x <= 15; x++) // for loop to print the row
	{
		printf(" O  ", 219);
	}

	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	while (getch() != 13); // To make sure only enter key is pressed
	printf("\b \n");
	printf("\n\n\t\t\t\t\t\t\t\t      The state of the cells can be ON(Alive) or OFF(Dead):  \n\n\t\t\t\t\t\t\t\t     ");

	for (int x = 0; x <= 15; x++)// for loop to print the second row with dead cells as well
	{
		if (rand() % 3 == 0)   //one out of 3 chance that it will be a dead cell
			printf("    ");
		else
			printf(" O  ", 219);
	}

	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t      See that each cell has two neighboring cells\n\n  ");
	printf("\t\t\t\t\t\t\t\t\t\t\t     o   O   o");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	getch();
	printf("\b \n");
	printf("\n\n\t\t\t\t\t\t\t a cell, and it 2 neighbors can have 8 different combinations( . represents dead here): \n  ");
	printf("\n\t\t\t\t\t\t\t     O  O  O \t\tO  O  . \t\tO  .  O \t\tO  .  .\n  ");
	printf("\n\n\t\t\t\t\t\t\t     .  O  O \t\t.  O  . \t\t.  .  O \t\t.  .  .\n  ");
	printf("\n\t\t\t\t\t\t\t  And we can set rules for each combination to determine the state \n\n\t\t\t\t\t\t\t  of the selected cell in next generation  \n  ");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\t\t\t\t\t\t\t  For Example, we can set the rules like this: \n  ");
	printf("\n\t\t\t\t\t\t\t  O  O  O -> Dead\tO  O  . -> Alive     \tO  .  O -> Dead\t     O  .  . -> Dead\n  ");
	printf("\n\n\t\t\t\t\t\t\t  .  O  O -> Alive\t.  O  . -> Dead   \t.  .  O -> Alive     .  .  . -> Alive\n  ");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	while (getch() != 13); // To make sure only enter key is pressed
	printf("\b \n");
	printf("\n\t\t\t\t\t\t\t the next step is to implement these rules \n  ");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\t\t\t\t\t\t\t  Now consider this row: ");
	printf("\n\n\t\t\t\t\t\t\t\t  O   .   O   O   O   .\x1b[33m [ O ] \x1b[0mO   .   O   O  ");
	printf("\n\n\t\t\t\t\t\t\t  We have selected one cell ( selection represented by\x1b[33m [ ]\x1b[0m)");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	while (getch() != 13);
	printf("\b \n");
	printf("\n\n\t\t\t\t\t\t\t  This cell has two neighbors, select them as well and we get 3 cells:");
	printf("\n\n\t\t\t\t\t\t\t\t  O   .   O   O   O \x1b[33m[ .  O  O ] \x1b[0m.   O   O  ");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	while (getch() != 13);
	printf("\b \n");
	printf("\n\n\t\t\t\t\t\t\t  Now we look up the rules for this combination that we set earlier.\n\n\t\t\t\t\t\t\t\t\t\t.  O  O -> Alive");
	printf("\n\n\t\t\t\t\t\t\t  so this cell will be Alive in the next generation");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	while (getch() != 13);
	printf("\b \n");
	printf("\n\n\t\t\t\t\t\t\t  Similarly we can select the next cell and repeat the same process");
	printf("\n\n\t\t\t\t\t\t\t\t  O   .   O   O   O   . \x1b[33m[ O   O   . ]\x1b[0m O   O  ");
	printf("\n\n\t\t\t\t\t\t\t  In this way we can run through the whole row, and create a new generation i.e the second generation.");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\t\t\t\t\t\t\t  By Stacking these generations on each other,To our surprise,\n\n\t\t\t\t\t\t\t  many complex patterns are observed, which we will be generating in this simulator");
	printf("\n\n\n\n\t\t\t\t\t\t\t \x1b[33m       Wolfram's idea was that every complex system starts from something simple \n\n\t\t\t\t\t\t\t\t\t     and grows complex following some universal rules \n\n\n\n\t\t\t\t\t\t\t\tHe designed this system( And Many others) to show the key concept that\n\n\t\t\t\t\t\t\t\t      we can generate complex systems by implementing simple rules.\x1b[0m ");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\t\t\t\t\t\t\t If you don't have a big Brain, and don't understand any of this, don't worry \n\n\t\t\t\t\t\t\t The Simulation will still work ");
	printf("\n\n\t\t\t\t\t\t\t We have already taken care of this stuff so you don't have to worry about it");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");

	while (getch() != 13); // To make sure only enter key is pressed
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\t\t\t\t\t\t\t We have also provided some of our favorite set of rules for you to try,\n\n\t\t\t\t\t\t\t or you can create your own rules");
	printf("\n\n\t\t\t\t\t\t\t All you have to do is select Alive or Dead for 8 different combinations\n\n\t\t\t\t\t\t\t We hope thats simple enough. ");
	printf("\n\n\n\t\t\t\t\t\t\t Now select Start simulation in the main menu to give it a go ");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t \x1b[33m  %c\x1b[0m", 175); // continue character
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	while (getch() != 13); // To make sure only enter key is pressed
}

//*********************************************   Credits FUNCTION   **************************************************
void credits()
{
	drawLogo(); // Clears Screen, draws the logo

	// USING PRINTF AND ESCAPE SEQUENCES TO PRINT THE CREDITS
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t    ~~~~~> \x1b[36mEND SEMESTER PROJECT\x1b[0m <~~~~~\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t * BY * \n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t* \t    1. Tayyab Ahmed           \t  * \n\n");
	printf("\t\t\t\t\t\t\t\t\t\t* \t    2. Zaid bin Tariq         \t  *  \n\n");
	printf("\t\t\t\t\t\t\t\t\t\t* \t    3. Hasan Iqtedar          \t  * \n\n");
	printf("\t\t\t\t\t\t\t\t\t\t* \t    4. Syed Umer Tariq        \t  *\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t*******************************************\n");
	printf("\t\t\t\t\t\t\t\t\t\t* \x1b[33m    Students of BSCS 9A, SEECS NUST     \x1b[0m*\n");
	printf("\t\t\t\t\t\t\t\t\t\t*******************************************\n");


	printf("PRESS ENTER KEY TO GO BACK");
	while (getch() != 13); // Enter key to go back to main menu
}

// ************************************************  SET RULES  *******************************************************
void customRules()
{
	//                                          This function is called when the user selects "Set Your Own Rules"
	drawLogo(); // Clears screen and draws logo
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\t\t\t\t\t\t\t\tLets set up the rules for the simulation\n");
	printf("\n\n\n\t\t\t\t\t\t\t\tWe will show you Eight combinations one by one\n\n\t\t\t\t\t\t\t\t You will have to choose alive or dead for each one to \n\n\t\t\t\t\t\t\t\tsetup the rules for the simulation");
	printf("\n\n\n\t\t\t\t\t\t\t\tPress any key to continue...\n");
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	getch();
	for (int x = 0; x<8; x++) // 8 iterations for 8 rules
	{
		int select = 1; // 1 if alive is selected , 0 if dead is selected
		while (1) //while loop to redraw when the selection changes
		{
			drawLogo(); // Clears screen and draws logo
			printf("\n\n\n\t\t\t\t\t\t\tWhat State do you want to be for this combination?");
			printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
			printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t");


			switch (x)   // Shows different combination depending on the iteration of the for loop
			{
			case 0:
				printf(".    .    .  ");
				break;
			case 1:
				printf(".    .    O ");
				break;
			case 2:
				printf(".    O    . ");
				break;
			case 3:
				printf(".    O    O ");
				break;
			case 4:
				printf("O    .    . ");
				break;
			case 5:
				printf("O    .    O ");
				break;
			case 6:
				printf("O    O    . ");
				break;
			case 7:
				printf("O    O    O ");
				break;
			}
			printf("\n\n\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
			if (select == 1)       // if select is 1, alive is active
				printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\x1b[33m~> ALIVE <~\x1b[0m\t\t\t\t    DEAD ");
			else if (select == 0)  // if select is 0, dead is active
				printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t   ALIVE   \t\t\t\t \x1b[33m~> DEAD <~\x1b[0m");
			printf("\n\n\n\n\n\nNOTE: Use LEFT ARROW and RIGHT ARROW Keys to cycle, ENTER to select.");
			char keyhit = keyboardIn(); // getting user input using keyboardIn() function
			if (keyhit == 'l' || keyhit == 'r')   // if either right or left arrow key is pressed,
			{
				select = (select + 1) % 2; // we change the selected
			}
			else if (keyhit == 'e')  // if enter is pressed
			{
				rules[x] = (select == 1) ? alive : ' ';    // we set the current rule depending on the state of select
				break;
			}
		}
	}

}

// ************************************************* CHECK RULES ******************************************************
char checkRules(char l, char m, char r)
{
	// This function one by one checks for the 8 Rules and returns the corresponding rule array element(Alive or dead state)

	if (l == ' ' && m == ' ' && r == ' ')
		return rules[0];
	else if (l == ' ' && m == ' ' && r == alive)
		return rules[1];
	else if (l == ' ' && m == alive && r == ' ')
		return rules[2];
	else if (l == ' ' && m == alive && r == alive)
		return rules[3];
	else if (l == alive && m == ' ' && r == ' ')
		return rules[4];
	else if (l == alive && m == ' ' && r == alive)
		return rules[5];
	else if (l == alive && m == alive && r == ' ')
		return rules[6];
	else if (l == alive && m == alive && r == alive)
		return rules[7];
}

// ********************************************** PLAY FUNCTION *******************************************************
void play()
{
	int maxGen;  // variable for the total number of generations
	simulationRules(); // This function deals with the setup of the rules
	do{     // we need to take input atleast once
		drawLogo();
		printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
		printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t     How many generations do you want to run the simulation for?\n\t\t\t\t\t\t\t\t     (Please Enter a positive number,Recommended:100-500)\n\t\t\t\t\t\t\t\t     ");
		scanf("%d", &maxGen);    // taking input for number of generations
	} while (maxGen<0); // But the user is asked again until he enters a valid positive number
	drawLogo();
	printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t    Press ENTER to run simulation...\n");
	printf("\n\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
	startingCombination();  // initializes the cell rows
	while (getch() != 13);  // waits for Enter key
	drawLogo();     // Clears the screen, draws the logo
	printf("\n ");
	Sleep(200);

	for (int currentGen = 0; currentGen < maxGen; currentGen++)      // loops runs for the number of generations entered by the user
	{
		drawRow();                                                  // Draws the current generations
		printf("\x1b[0m  Gen %d\n\x1b[%dm ", currentGen + 1, 31 + rand() % 7);    // prints the current gen
		Sleep(100);                 // adds delay
		nextGen();                  // generates the next generation and passes it to the current gen
	}
	printf("\x1b[0m  \n\nPress ENTER to return to main menu\n");
	while (getch() != 13);
}

// ********************************************** SIMULATION RULES FUNCTION *******************************************
void simulationRules()
{
	int selection = 0;          // holds the number for currently selected rule
	char keyPressed;            // variable to hold user input

	while (1)                    // loop runs until one of the rules is selected
	{
		drawLogo();         // clears the screen and draws the logo

		/* There are 7 Buttons on the screen, only one can be selected at a time. the selection variable stores which button is selected
		if that button is selected it is drawn as Active, else it will be drawn as Not Actice
		*/
		printf("\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
		printf("\n\n\t\t\t\t\t\t\tWe have collected some of our favorite set of rules, give them a try, or create your own!\n\n");
		if (selection == 0)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 90 <<<~~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 90 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 90 ~~~~~~~~~~ ");                                      // Rule 90 Button, NOT ACTIVE

		if (selection == 1)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 57 <<<~~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 57 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 57 ~~~~~~~~~~ ");                                      // Rule 57 Button, NOT ACTIVE

		if (selection == 2)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 161 <<<~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 161 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 161 ~~~~~~~~~  ");                                     // Rule 161 Button, NOT ACTIVE

		if (selection == 3)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 105 <<<~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 105 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 105 ~~~~~~~~~");                                       // Rule 105 Button, NOT ACTIVE

		if (selection == 4)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 153 <<<~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 153 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 153 ~~~~~~~~~ ");                                      // Rule 153 Button, NOT ACTIVE

		if (selection == 5)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~~~~~~>>> RULE 182 <<<~~~~~~ %c\x1b[0m ", 219, 219);    // Rule 182 Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t~~~~~~~~~ RULE 182 ~~~~~~~~~ ");                                      // Rule 182 Button, NOT ACTIVE

		if (selection == 6)
			printf("\n\n\t\t\t\t\t\t\t\t\t\t      \x1b[33m%c ~>>> Set Your Own Rules <<<~ %c\x1b[0m", 219, 219);     // Set your own rules Button, ACTIVE
		else
			printf("\n\n\t\t\t\t\t\t\t\t\t\t        ~~~~ Set Your Own Rules ~~~~  ");                               // set your own rules Button, NOT ACTIVE



		printf("\n\n\n\t\t\t\t\t\t\t\x1b[36m_________________________________________________________________________________________\x1b[0m");
		printf("\n\n\nNOTE: Use UP ARROW and DOWN ARROW Keys to cycle, ENTER to select.");
		keyPressed = keyboardIn();      // get input from keyboard
		if (keyPressed == 'e')           // if enter is pressed,
		{
			selectRules(selection);     // set the selected rules
			break;
		}


		switch (keyPressed)
		{
		case 'u':   // if Up arrow is pressed,
			if (selection == 0)
				selection = 6; // if last button is selected then select the first one
			else
				selection--; // else select the button above the currently selected
			break;

		case 'd':   // if Down arrow is pressed
			if (selection == 6)
				selection = 0; // if first button is selected then select the last one
			else
				selection++; // else select the button below the currently selected
				break;

		}

	}

}

//********************************************* SELECT RULES **********************************************************
void selectRules(int selected)
{
	if (selected != 6)
	{
		switch (selected)    // the rule selected by the user gets saved in temp array and then passed to the rules array
		{
		case 0: // RULE 90
		{
					char temprules[] = { ' ', 'O', ' ', 'O', 'O', ' ', 'O', ' ' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}

		case 1: // RULE 57
		{
					char temprules[] = { 'O', ' ', ' ', 'O', 'O', 'O', ' ', ' ' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}

		case 2: //RULES 161
		{
					char temprules[] = { 'O', ' ', ' ', ' ', ' ', 'O', ' ', 'O' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}

		case 3: //RULES 105
		{
					char temprules[] = { 'O', ' ', ' ', 'O', ' ', 'O', 'O', ' ' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}

		case 4: // RULE 153
		{
					char temprules[] = { 'O', ' ', ' ', 'O', 'O', ' ', ' ', 'O' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}

		case 5: // RULE 182
		{
					char temprules[] = { ' ', 'O', 'O', ' ', 'O', 'O', ' ', 'O' };
					for (int n = 0; n<8; n++)
					{
						rules[n] = temprules[n];
					}
					break;
		}


		}
	}
	else
		customRules();


}

// ********************************************* DRAW ROW *************************************************************
void drawRow()
{
	for (int x = 0; x<200; x++)     // runs loop till 200, draws each cell of the row
	{
		printf("%c", rowOld[x]);
	}
}

// ************************************************** NEXT GENERATION *************************************************
void nextGen()
{
	for (int x = 1; x < 199; x++)
	{
		rowNew[x] = checkRules(rowOld[x - 1], rowOld[x], rowOld[x + 1]);       // calls the check rules function by passing a cell and its 2 neighbors, and sets the returned values to the next gen
	}
	for (int x = 0; x < 200; x++)
	{
		rowOld[x] = rowNew[x];                                            // passes the next generation to current generation
	}
}

// ******************************************* STARTING COMBINATION ***************************************************
void startingCombination()
{
	for (int i = 0; i<200; i++)               // initializes both rows, current gen and next gen to dead
	{
		rowNew[i] = ' ';
		rowOld[i] = ' ';
	}
	rowOld[100] = 'O';                        // sets the middle cell of the first gen to alive

}
