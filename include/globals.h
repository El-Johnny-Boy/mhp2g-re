#include "player_data.h"



extern u32 *gMainBlock; //DAT_08A5DD20 - general context block. Passed in numerous functions, often as the first parameter.
extern PlayerData *gPlayerData; //DAT_089C7508 - player block, pointer to PlayerData is at offset 0x4A0 of this block.