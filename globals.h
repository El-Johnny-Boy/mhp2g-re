#include "player_data.h"


// DAT_089C7508 containts 0x99959A0 : pointer to the main block ?
// PlayerData = *0x089C7508 + 0x4A0
extern u32 gMainBlock;
extern PlayerData *gPlayerData;