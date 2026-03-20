# Memory addresses

## Global pointers - Static addresses in the binary
| Address      | Name          | Points towards | Notes                                          |
|--------------|---------------|----------------|------------------------------------------------|
| 0x089C7508   | gPlayerBlock  | 0x099959A0     | player block, player data starts at +0x4A0 (0x9995E40)     |
| 0x08A5DD20   | gGameContext  | 0x09A024D8     | general context ? passed in numerous functions |

## Player block layout (base = *gPlayerBlock)
| Offset | Size   | Name             | Notes                        |
|--------|--------|------------------|------------------------------|
| +0x4A0 | ???    | PlayerData       | start of Player Data         |

## PlayerData layer (base = *gPlayerBlock + 0x4A0)
| Offset   | Size    | Name                 | Notes                                   |
|----------|---------|----------------------|-----------------------------------------|
| +0x000   | 0x10    | name                 | UTF-16, 8 chars max                     |
| +0x010   | 0x0C    | unknown1             | empty, padding ?                        |
| +0x01C   | 0x04    | unknown2             | FF 67 9A E4 — checksum ?                |
| +0x020   | 0x0C    | weapon               | EquipmentSlotData                       |
| +0x02C   | 0x3C    | armor[5]             | EquipmentSlotData * 5                   |
| +0x068   | 0x40    | unknown3             |                                         |
| +0xa8    | 0x2ee0  | equipmentChest[1000] | EquipmentSlotData, 12 bytes/slot        |
| +0x2f88  | 0xfa0   | itemChest[1000]      | ItemSlotData, 4 bytes/slot              |
| +0x3f28  | 0x60    | inventory[24]        | ItemSlotData, 4 bytes/slot              |
| +0x3f88  | 0x40    | unknown4             |                                         |
| +0x3fc8  | 0x8     | timePlayed           | in seconds, stored as 64 bits integer   |
| +0x3fd0  | 0x667e4 | unknwown5            | a lot of things, need to look into it   |
| +0x6a7b4 | 0xa0    | itemOwnedFlags[]     | bitset owned items                      |