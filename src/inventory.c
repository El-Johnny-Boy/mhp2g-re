#include "game_constants.h"
#include "globals.h"
#include "types.h"
#include "player_data.h"

//0885aec8
int getInventoryItemQuantity(short itemID)
{
    ItemSlotData *slot = gPlayerData->inventory;

    for (u32 i = 0; i < INVENTORY_SIZE; i++, slot++) {
        if (gPlayerData->inventory[i].itemID == itemID) {
            return gPlayerData->inventory[i].quantity;
        }
    }

    return 0;
}