#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Game.h"
#include "UnixBoard.h"
#include <string.h>
/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
static int loading(int currentRoom);
 
static int startRoom = STARTING_ROOM;
static int checker;

struct {
    uint8_t currentRoom;
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char desc[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t northExit ;
    uint8_t southExit;
    uint8_t eastExit;
    uint8_t westExit;
}Room;

int GameGoNorth(void)
{
	// all of the game go functions are about the same
	// i just use my loading helper function to check if northExit exists. 
    if (Room.northExit != 0) {
        checker = loading(Room.northExit);
        if (checker == SUCCESS) {
            Room.currentRoom = Room.northExit;
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void)
{
	// see GameGoNorth
    if (Room.eastExit != 0) {
        checker = loading(Room.eastExit);
        if (checker == SUCCESS) {
            Room.currentRoom = Room.eastExit;
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void)
{
	// see GameGoNorth
    if (Room.southExit != 0) {
        checker = loading(Room.southExit);
        if (checker == SUCCESS) {
            Room.currentRoom = Room.southExit;
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void)
{
	// see GameGoNorth
    if (Room.westExit != 0) {
        checker = loading(Room.westExit);
        if (checker == SUCCESS) {
            Room.currentRoom = Room.westExit;
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

int GameInit(void)
{
	// very similar to the game go functions except make the loading load the STARTING_ROOM.
	int startChecker = loading(STARTING_ROOM);
    if(startChecker == SUCCESS){
		return SUCCESS;
	}
	return STANDARD_ERROR;
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possibl e titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
	// this is to check if a empty title was passed
    if(Room.title == NULL){
        title = NULL;
    }
	// copy the title into the title
    strcpy(title,Room.title);
    return strlen(Room.title);
}

int GameGetCurrentRoomDescription(char *desc)
{
    if(Room.desc == NULL){
        desc = NULL;
    }
    strcpy(desc,Room.desc);
    return strlen(Room.desc);
}

uint8_t GameGetCurrentRoomExits(void){
    uint8_t holder = 0;
	// this function is very similar to GetButtonEvents from Lab6
    if(Room.northExit != 0){
		// basically or the bits of holder and the enums if the exits exist
        holder = holder | GAME_ROOM_EXIT_NORTH_EXISTS;
    }
        if(Room.eastExit != 0){
        holder = holder | GAME_ROOM_EXIT_EAST_EXISTS;
    }
        if(Room.southExit != 0){
        holder = holder | GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
        if(Room.westExit != 0){
        holder = holder | GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return holder;
}

static int loading(int currentRoom)
{
    FILE *fp;
    uint8_t mover;
    int j;
    char fileString[25];

    // Here I set the fileString to the file.
    sprintf(fileString, "RoomFiles/room%d.txt", currentRoom);
   
   fp = fopen(fileString, "rb");
    if (fp == NULL) {
        return STANDARD_ERROR;
    }
	
	
    // check the first bit
    fread(&mover, 1, 1, fp);
    fread(Room.title, 1, mover, fp);
    Room.title[mover] = '\0';
	//printf("OM1: %d\n", mover);
    // Above I read the title into Room.title @ itemreqs now
    
	
	while (TRUE) {
        int itemChecker = 0;
        int getItem = 0;
        // check how many itemreqs I have
        fread(&mover, 1, 1,fp);
        uint8_t itemReqs [mover];
        // read the itemreqs for the room
        fread(itemReqs, 1, mover, fp);
				//printf("LM1: %d\n", mover);
        // check if i have all the items
       

	   for (j = 0; j < mover; j++) {
            if (FindInInventory(itemReqs[j]) == TRUE) {
                itemChecker++;
            }
        }
        // if the items are all there then read the description of the room
       

	   if (itemChecker == mover) {
		   // check if the item descriptions are met
            fread(&mover, 1, 1, fp);
            fread(Room.desc, 1, mover,fp);
            Room.desc[mover] = '\0';
            fread(&mover, 1, 1, fp);
			//printf("LM2: %d\n", mover);
            uint8_t roomItems[mover];
            fread(roomItems, 1, mover, fp);
            // add whatever items that are in the room into the inventory
            for (j = 0; j < mover; j++) {
                AddToInventory(roomItems[j]);
            }
			//printf("LM3: %d\n", mover);
            // add all of the bits of exits into the respective exits
            fread(&Room.northExit, 1, 1,fp);
			//printf("LM4: %d\n",Room.northExit);
            fread(&Room.eastExit, 1, 1, fp);
			//printf("LM5: %d\n",Room.eastExit);
            fread(&Room.southExit, 1, 1,fp);
			//printf("LM6: %d\n", Room.southExit);
            fread(&Room.westExit, 1, 1, fp);
			//printf("LM7: %d\n",Room.westExit);
			fclose(fp);
            return SUCCESS;
	   } else {
            // if the item reqs were not met go to a version where they are met go to the next item reqs(past the exits)
            fread(&mover, 1, 1, fp);
			//printf("OM2: %d\n", mover);
            fseek(fp,mover, SEEK_CUR);
            fread(&mover, 1, 1,fp);
			//printf("OM3: %d\n", mover);
            fseek(fp, mover, SEEK_CUR);
            fseek(fp, 4, SEEK_CUR);
			//printf("OM4: %d\n", mover);
        }
    }
	fclose(fp);
    return SUCCESS;
}