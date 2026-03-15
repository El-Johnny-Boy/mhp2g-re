#include <stdbool.h>
#include "player_data.h"
#include "types.h"
#include "globals.h"
#include "game_constants.h"


//08857bb8
//not completely sure about this since it's also called by FUN_0885df98
bool playerHasItem(PlayerData* playerData, u32 itemID) {
    u32 itemID16 = itemID & 0xffff;
    
    if (itemID16 == 0xffff || itemID16 > ITEM_COUNT) {
        return false;
    }
    else {
        u32 word = playerData->itemOwnedFlags[itemID16 / ITEM_FLAG_BITS];
        u32 mask = 1u << (itemID % ITEM_FLAG_BITS);

        return (word & mask) != 0;
    }
    
}

//0885c5c4
/*Certainly a tailcall or a wrapper for playerHasItem, in Ghidra this function has 
two parameters but the first one is ignored. First parameters is a u32 that contains the pointer of GameData.*/
bool playerHasItem_TailCall(u32 itemID) {
    return playerHasItem(getPlayerData(), itemID);
}

PlayerData *getPlayerData(void) {
    return (PlayerData *)(gMainBlock + 0x4A0); 
}

//08850d9c
int getChestPageCount() {
    bool hasItem;
    u32 boxExpansionItemID;
    u32 pageCount; 

    pageCount = 8;
    boxExpansionItemID = 0x33d;

    while (boxExpansionItemID < 0x33f) {
        hasItem = playerHasItem_TailCall(boxExpansionItemID);
        pageCount ++;
        boxExpansionItemID ++;
    }

    return pageCount;
}

//08850e08
int getChestSlotCount() {
    return getChestPageCount() * 100; //100 slots per page, hardcoded.
}

//0885c334
//Again called with DAT_08A5DD20 as first parameter, but it's not used.

int getTotalItemCount(u32 itemID) {
    u16 slotCount = getChestSlotCount();
    int total = 0;
    int slotIndex = 0;

    ItemSlotData *slot = gPlayerData->itemChest;

    for (int i = 0; i < slotCount; i++, slot++) {
         if (slot->itemID == itemID) {
            total += slot->quantity;
            //here there is a check to against the byte at &DAT_0899a23b[itemID * 0x18]
            //at tis adress there is a pointer 0885aae4
            //then 8 bytes later there is another pointer 0885ac84
        }
    }

    while (slotIndex < slotCount) {
        if (slot->itemID == itemID) {
            total += slot->quantity;
        }
        slot++;
        slotIndex++;
    }

    return total;
}