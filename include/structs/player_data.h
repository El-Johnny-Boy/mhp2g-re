#include <stdint.h>
#include "types.h"
#include "game_constants.h"
#include "structs/equipment.h"
#include "structs/item_slot.h"

/*
Notable memory addresses :
0x09995E60 : equipped weapon
0x09995E6C : equipped legs, head, torso, bracers, waist. 12 bytes each.

0x09995EE8 : equipment chest
0x09998DC8 : item chest
0x09999D68 : inventory
*/


typedef struct {
    u16 chars[8]; // 0x10 bytes
} HunterName;



typedef struct 
{
    //0x00
    HunterName name;
    //0x10
    u8 unkown1[0xC]; //empty in new save. Maybe HR, padding ?
    //0x1C
    u32 unknown2; //FF 67 9A E4 in two different saves.
    //0x20
    PlayerEquippedGear equippedGear; //0x6 * 0xC = 0x48 bytes
    //0x68
    u8 unkown3[0x40];
    //0xA8
    EquipmentSlotData equipmentChest[1000]; //0xC bytes each, 1000 slots, 0x2ee0 bytes total
    //0x2f88
    ItemSlotData itemChest[1000]; //0x4 bytes each, 1000 slots, 0xfa0 bytes total
    //0x3f28
    ItemSlotData inventory[24]; //0x4 bytes each, 24 slots, 0x60 bytes total
    //0x3f88
    u8 unknown3[0x40];
    //0x3fc8
    u8 timePlayed[0x8]; //in seconds, stored as a 64 bit integer.
    //0x3fd0
    u8 unknown4[0x667E4];
    //0x6A7B4
    // item owned bitset
    u32 itemOwnedFlags[ITEM_FLAG_WORDS];

} PlayerData; //likely but might be something else