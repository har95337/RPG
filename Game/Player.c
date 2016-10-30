/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
 #include "Player.h"
 #include "UnixBoard.h"
 #include <stdio.h>
 #include <stdlib.h>
 static uint8_t inventory[INVENTORY_SIZE]; 
 static int i = 0; 
 static int j; 
 
 
int AddToInventory(uint8_t item){
	if(i > 4){
		return STANDARD_ERROR; 
	}else{
		inventory[i] = item;
		i++; 
	}
	return SUCCESS; 
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item){
	for(j = 0; j <= INVENTORY_SIZE; j++){
		if(inventory[j]== item){
			return SUCCESS;
		}
	}
	return STANDARD_ERROR; 
}