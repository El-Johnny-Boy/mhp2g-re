# References
getChestPageCount :
    - getChestSlotCount [Done]
    - ???_clampBoxSlotIndex [ToVerify]
    - FUN_089042ec 

getChestSlotCount :
    - getFirstEmptySlotIndex [Done]
    - writeDataOnFirstEmptyEquipmentChestSlot [Done]
    - FUN_088539e4
    - removeItemQuantityFromChest [Done]
    - FUN_0885baf8
    - findSlotIndexbyID [Done]
    - getFirstItemSlotQuantity [Done]
    - getTotalItemCount [Done]
    - getItemChestRemainingCapacity [Done]
    - getMaximumQuantityThatCanBeAdded [Done]