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

    //Checks each chest items against an item table at address 0x0899a23b
    for (u16 i = 0; i < slotCount; i++, slot++) {
        //If the item isn't stackable, return 999.
        if (gItemTable[itemID & 0xFFFF].maxInventoryStack == 0xFF) {
            return 999;
        }
        if (slot->itemID == itemID) {
            total += slot->quantity;
        }
    }
    
    return total;
}

//08850668
//No references, called by pointer ?
u16 writeDataOnFirstEmptyEquipmentChestSlot(PlayerData* playerData, u8 equipmentTypeID, u16 equipmentID, u16 unknown) {
    //Proof against wrong data ?
    if (equipmentTypeID >= 7) {
        return 0xFFFF;
    }

    u16 slotCount = getChestSlotCount();
    EquipmentSlotData *slot = playerData->equipmentChest;

    for (u16 i = 0; i < slotCount; i++, slot++) {
        if (slot->occupied == 0) {
            slot->occupied = 1;
            slot->equipmentTypeID = equipmentTypeID;
            slot->equipmentID = equipmentID;
            slot->unknown1 = unknown;
            slot->unknown2 = 0;
            slot->unknown3 = 0;
            slot->unknown4 = 0;
            return i;
        }
    }

    return 0xFFFF;
}