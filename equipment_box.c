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
int getBoxPageCount() {
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

int getBoxSlotCount() {
    return getBoxPageCount() * 100; //100 slots per page, hardcoded.
}