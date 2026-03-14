#include <stdint.h>
#include "types.h"


enum EquipmentTypeID {
  Leggings = 0x00,
  Helmet = 0x01,
  Plate = 0x02,
  Gauntlets = 0x03,
  Waist = 0x04,
  BlademasterWeapon = 0x05,
  GunnerWeapon = 0x06,
};

typedef struct
{
    u8 rarity; //? Maybe, need to crosscheck with other stuff
    u8 equipmentTypeID; //stocked as u8, cast as EquipmentTypeID in usage. Maybe not an enum, but it seems to be one.
    u32 equipmentID; 
    u16 unknown1; //

} EquipmentSlotData; //0xC bytes

typedef struct
{
    EquipmentSlotData weapon; // 0xC bytes
    EquipmentSlotData armor[5]; //0x3C bytes
} PlayerEquippedGear;