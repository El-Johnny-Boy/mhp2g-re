#include <stdint.h>
#include "types.h"

typedef enum {
    ITEM_FLAG_NONE          = 0x00,
    ITEM_FLAG_EDIBLE        = 0x01,  // items that can be eaten (like potions, herbs, etc.)
    ITEM_FLAG_POKKE_POINTS  = 0x02,  // items that give pokke points
    ITEM_FLAG_SUPPLY        = 0x04,  // supply items (like knives, traps, etc.)
    ITEM_FLAG_TREASURE      = 0x10,  // treasure quest items
    ITEM_FLAG_INFO          = 0x20,  // info item (doesn't take a slot)
} ItemFlags; //can't find the 0x08 flag, maybe it's not used or maybe it's used for something else.

typedef enum {
    COLOR_WHITE = 0x00,
    COLOR_RED = 0x01,
    COLOR_GREEN = 0x02,
    COLOR_BLUE = 0x03,
    COLOR_YELLOW = 0x04,
    COLOR_PURPLE = 0x05,
    COLOR_LIGHT_BLUE = 0x06,
    COLOR_ORANGE = 0x07,
    COLOR_PINK = 0x08,
    COLOR_BROWN = 0x09, //I guess, I don't see it used anywhere but it seems to fit the pattern of the other colors, and there are 10 colors in total.
    COLOR_GREY = 0x0A,
} Colors; //0x4 bytes, used in inventory and item chest, but not equipment chest.

typedef struct {
    u8 category; //0x00 for items, 0x01 for carryable items (like eggs), 0x02 for ammunition, 0x03 for coatings.
    u8 usable; //0x00 not usable, 0x01 usable by the player, 0x02 usable by guns, 0x03 usable by bows.
    u8 rarity; //0x00 for rarity 1, up to 0x04 for rarity 5
    u8 maxInventoryStack;
    u8 flags; //bitfield, see ItemFlags
    u8 icon; //seems like a base icon ID that is recolored for different items (ex. Rathalos Tail and Shell have the same icon, but different colors as Cephalos Fin)
    u8 color; //color of the icon 
    u8 unknown1; //all 0x00, maybe padding.
    u16 ammoID;
    u16 unknown2; //0x03 for treasures and ruststones, 0x02 for carryables, rest is 0x00. Bitfield ?
    u32 buyPrice;
    u32 sellPrice;
    u16 unknown8; //all 0x00, maybe padding.
    u16 decorationSkillID;
} ItemData;
