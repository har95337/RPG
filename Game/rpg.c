// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CMPE13 Support Library
#include <stdio.h>
#include <stdlib.h>




// User libraries
#include "Player.h"
#include "Game.h"
#include "UnixBoard.h"
// **** Set any macros or preprocessor directives here ****
#define ASCII_ESC 27
// **** Declare any data types here ****
static char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
static char desc[GAME_MAX_ROOM_DESC_LENGTH + 1];
// **** Define any global or external variables here ****
static int i = 0; 
static char direction = '\n';
static char checkEnter = '\n'; 
static char afterEnter = '\n';
// **** Declare any function prototypes here ****

int main()
{
    /******************************** Your custom code goes below here ********************************/

    if (GameInit() != SUCCESS) {
        return STANDARD_ERROR;
    }
	
    while (1) {
		// Here i load the title and desc properly
        GameGetCurrentRoomTitle(title);
        GameGetCurrentRoomDescription(desc);
		// a ton of vt100 commands
		printf("%c[2J", ASCII_ESC );
        printf("%c[H", ASCII_ESC);
        printf("%c[35m ", ASCII_ESC);
        printf("%c[43m", ASCII_ESC);
		// print the title with pretty colors
        printf("%s", title);
		printf("%c[1B", ASCII_ESC);
        printf("%c[49m", ASCII_ESC);
        printf("%c[39m", ASCII_ESC);
		// reset the colors and print the description
		printf("%s", desc);
		printf("%c[E", ASCII_ESC);
        printf("%c[1000B", ASCII_ESC);
		
		// here is where i make the compass
		if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS){
			printf("%c[32m", ASCII_ESC);
		}else{
			printf("%c[31m", ASCII_ESC);
		}
		printf("%c[1C", ASCII_ESC);
		printf("%c[3A", ASCII_ESC);
		printf("n");
		printf("%c[39m", ASCII_ESC);

		
		if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS){
			printf("%c[32m", ASCII_ESC);
		}else{
			printf("%c[31m", ASCII_ESC);
		}		
		printf("%c[2D", ASCII_ESC);
		printf("%c[1B", ASCII_ESC);
		printf("w");
		printf("%c[39m", ASCII_ESC); 
		
		if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS){
			printf("%c[32m", ASCII_ESC);
		}else{
			printf("%c[31m", ASCII_ESC);
		}
		printf("%c[1C", ASCII_ESC);
		printf("e");
		printf("%c[39m", ASCII_ESC); 
		
		
		if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS){
			printf("%c[32m", ASCII_ESC);
		}else{
			printf("%c[31m", ASCII_ESC);
		}
		printf("%c[1B", ASCII_ESC);
		printf("%c[2D", ASCII_ESC);
		printf("s");
		printf("%c[39m", ASCII_ESC); 
		
		
		
		
		printf("%c[2B", ASCII_ESC);
		printf("What direction: ");
		checkEnter = getchar();
		// i use 3 variables to check 3 iterations of this loop to check if \n CHARACTER \n was entered
        if ((direction == 'n' || direction == 'N') && checkEnter == '\n' && afterEnter == '\n') {
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
                GameGoNorth();
            }
        }
        if (((direction == 'e' || direction == 'E')) && checkEnter == '\n' && afterEnter == '\n') {
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
                GameGoEast();
            }
        }
        if (((direction == 's' || direction == 'S')) && checkEnter== '\n' && afterEnter == '\n') {
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
                GameGoSouth();
            }
        }
        if (((direction== 'w' || direction == 'W')) && checkEnter == '\n' && afterEnter == '\n') {
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
                GameGoWest();
            }
        }
		afterEnter = direction; 
		direction = checkEnter;
	}

	


    /**************************************************************************************************/
}
