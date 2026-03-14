#include <stdint.h>
#include <types.h>

typedef struct
{
    u16 itemID;
    u16 quantity;
} ItemSlotData; //0x4 bytes, used in inventory and item chest, but not equipment chest.

