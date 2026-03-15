#include <stdint.h>
#include "types.h"


typedef struct {
    u8 category; //0x00 for items, 0x01 for certains jewels ?, 0x02 for ammunition, 0x03 for coatings.
    //jewel list:
    /*
    jewels list:
    874    |   0x36A    | Bind Jewel
    875    |   0x36B    | Observer Jewel
    876    |   0x36C    | Quick Charge Jewel
    877    |   0x36D    | Speed Fire Jewel 
    878    |   0x36E    | Anti Paralyze Jewel
    879    |   0x36F    | Anti Faint Jewel
    880    |   0x370    | Anti Venom Jewel
    881    |   0x371    | Snowplow Jewel
    */
    u8 usable; //0x00 not usable, 0x01 usable by the player, 0x02 usable by guns, 0x03 usable by bows.
    u8 rarity; //0x00 for rarity 1, up to 0x04 for rarity 5
    u8 maxInventoryStack;
    u8 unknown3;
    u8 unknown4;
    u8 unknown5;
    u8 unknown6[2];
    u8 unknown7[4];
    u32 price;
    u32 sellPrice;
    u32 unknown8;
} ItemData;
