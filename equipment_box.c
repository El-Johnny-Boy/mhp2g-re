#include <stdbool.h>
#include "player_data.h"
#include "types.h"

#define ITEM_COUNT 1260

//08857bb8
//not completely sure about this since it's also called by FUN_0885df98
bool playerHasItem(PlayerData* playerData, u32 itemID) {
    bool hasItem;

    u32 itemID16 = itemID & 0xffff;
    
    if (itemID16 == 0xffff) {
        return false;
    }
    if (itemID16 > ITEM_COUNT) {
        return false;
    }
    else {
        u32 word = playerData->itemOwnedFlags[itemID16 / 32];
        u32 mask = 1 << (itemID % 32);
        return (word & mask) != 0;
    }
    
}

//0885c5c4
//Certainly a tailcall for playerHasItem
void playerHasItem_TailCall(u32 itemID) {
    
}


//08850d9c
int getBoxPageCount() {
    bool hasItem;
    u32 boxExpansionItemID;
    u32 pageCount; 

    pageCount = 8;
    boxExpansionItemID = 0x33d;

    while (boxExpansionItemID < 0x33f) {
        hasItem;
    }
}