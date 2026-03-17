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


//088505e8
int getFirstEmptyEquipmentSlotIndex(PlayerData* playerData) {
    u16 slotCount = getChestSlotCount();
    EquipmentSlotData *slot = playerData->equipmentChest;

    for (u16 i = 0; i < slotCount; i++, slot++) {
        if (slot->occupied == 0) {
            return i;
        }
    }

    return 0xFFFF;
}

//0885c288
// Returns 999 if non stackable
int getFirstItemSlotQuantity(u16 itemID) {
    short slotCount = getBoxSlotCount();
    ItemSlotData *slot = gPlayerData->itemChest;

    for (int i = 0; i < slotCount; i++, slot++) {
        if (slot->itemID == itemID) {
            if (gItemTable[itemID].maxInventoryStack == 0xFF) {
                return 999;
            }
            return slot->quantity;
        }
    }
    return 0;
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


//0885c3d4
//Returns the remaining capacity for an item in the item chest. Returns 0 for non stackable items.
int getItemChestRemainingCapacity(u16 itemID) {
    itemID = itemID & 0xFFFF;

    if (itemID == 0 || gItemTable[itemID].maxInventoryStack == 0xFF) {
        return 0;
    }

    short SlotCount = getBoxSlotCount();
    ItemSlotData *slot = gPlayerData->itemChest;
    int total = 0;

    for (int i = 0; i < SlotCount; i++, slot++) {
        if (slot->itemID == itemID) {
            total += 99 - slot->quantity;
        }
        else if (slot->itemID == 0) {
            total += 99;
        }
    }

    return total;
}

//0885c490
//Returns the maximum quantity of a specific item that can be added to the item chest, taking into account the current quantity.
int getMaximumQuantityThatCanBeAdded(u16 itemID) {
    itemID = itemID & 0xFFFF;

    if (itemID == 0) {
        return 0;
    }

    short slotCount = getBoxSlotCount();
    u32 maxStack = gItemTable[itemID].maxInventoryStack;

    if (maxStack == 0xFF) {
        return 99;
    }

    ItemSlotData *slot = gPlayerData->itemChest;
    u32 remaining = maxStack;

    for (int i = 0; i < slotCount; i++, slot++) {
        if (slot->itemID == 0) {
            return maxStack;
        }
        if (slot->itemID == itemID && maxStack != 0xFF) {
            remaining -= maxStack - slot->quantity; 
            if ((int)remaining < 1) {               
                return maxStack;
            }
        }
    }

    return maxStack - remaining;
}

//0885b9d8
int removeItemQuantityFromChest(u16 itemID, short quantityToRemove) {
    ItemSlotData *slot = gPlayerData->itemChest;
    u32 remainingQuantity = quantityToRemove;

    if (quantityToRemove < 0) {
        return 0;
    }
    else {
        itemID = itemID & 0xFFFF;
        
        if (itemID == 0) {
            return 0;
        }
        else if (gItemTable[itemID].maxInventoryStack == 0xFF) {
            return 0;
        }
        else {
            u32 slotCount = getBoxSlotCount();
            
            for (u32 i = 0; i < slotCount; i++, slot++) {
                if (slot->itemID == itemID) {
                    if (slot->quantity < remainingQuantity) {
                        remainingQuantity = remainingQuantity - slot->quantity;
                        slot->quantity = 0;
                    }
                    else {
                        slot->quantity -= remainingQuantity;
                        remainingQuantity = 0;
                    }
                    if (slot->quantity == 0) {
                        slot->itemID = 0x0000;
                    }
                    if (remainingQuantity == 0) {
                        return 0;
                    }
                }
            }
        }
    }

    return remainingQuantity;
}