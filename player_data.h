#include <stdint.h>
#include "types.h"

#define ITEM_COUNT 1260
#define ITEM_FLAG_WORDS ((ITEM_COUNT + 31) / 32)

/*
Notable memory addresses :
0x09995E60 : equipped weapon
0x09995E6C : equipped legs, head, torso, bracers, waist. 12 bytes each.

0x09995EE8 : equipment chest
0x09998DC8 : item chest
0x09999D68 : inventory
*/


enum EquipTypeID: u8 {
  Leggings = 0x00,
  Helmlet = 0x01,
  Plate = 0x02,
  Gauntlets = 0x03,
  Waist = 0x04,
  BlademasterWeapon = 0x05,
  GunnerWeapon = 0x06,
};

typedef struct {
    u16 chars[8]; // 0x10 bytes
} HunterName;

typedef struct
{
    u8 rarity; //? Maybe, need to crosscheck with other stuff
    EquipTypeID equipTypeID;
    u32 equipementID; 
    u16 unknown3; //

} EquipmentSlotData; //0xC bytes

typedef struct
{
    EquipmentSlotData weapon; // 0xC bytes
    EquipmentSlotData armor[5]; //0x3C bytes
} PlayerEquippedGear;


typedef struct 
{
    //0x00
    HunterName name;
    //0x10
    u8 unkown1[0xC]; //empty in new save. Maybe HR, padding ?
    //0x1C
    u8 unknown2[0x4]; //FF 67 9A E4 in two different saves.
    //0x20
    PlayerEquippedGear equippedGear;
    //0x68
    u8 unkown3[0x48];
    //B0
    u8 unknown4[0x6A690];
    //0x6A7B4
    // item owned bitset
    u32 itemOwnedFlags[ITEM_FLAG_WORDS];

} PlayerData; //likely but might be something else