#include <components/monsterecomponent.h>

#include <components/collectablecomponent.h>
#include <components/inventorycomponent.h>
#include "components/inventorygirlcomponent.h"
#include <components/tirednesscomponent.h>

#include <components/spritecomponent.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	H3Handle player;
	H3Handle energyBar;
	H3Handle drinkSFX;

	bool isReadyToUse;
	bool IsMan;

} MonstereComponent_Properties;

void MonstereComponent_Terminate(void* properties)
{
	free(properties);
}

void MonstereComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MonstereComponent_Properties* props = (MonstereComponent_Properties*)properties;
	
	//use object in hand
	if (H3_Input_IsMouseBtnPressed(MB_Left) && CollectableComponent_GetisInHandEx(object))
	{
		//not to use at the same time as it is caught
		if (props->isReadyToUse)
		{
			H3_Sound_Play(props->drinkSFX, 0.4, false);
			//drink monstere helps to recover energy

			if (TirednessComponent_GetrecovEnergyEx(props->energyBar) == 0) {  //first drink
				TirednessComponent_SetrecovEnergyEx(props->energyBar, 1);
			}
			else if (TirednessComponent_GetrecovEnergyEx(props->energyBar) == 1) { //second drink
				TirednessComponent_SetrecovEnergyEx(props->energyBar, 2);
			}

			//remove from inventory
			if (props->IsMan)
				InventoryComponent_SetObjSlot2Ex(props->player, NULL);
			else
				InventoryGirlComponent_SetObjSlot3Ex(props->player, NULL);
			CollectableComponent_SetdurabilityEx(object, CollectableComponent_GetdurabilityEx(object) - 1);
		}
		props->isReadyToUse = true;
	}
}

void* MonstereComponent_CreateProperties(H3Handle playerRef, H3Handle energyBarRef, bool IsMan)
{
	MonstereComponent_Properties* properties = malloc(sizeof(MonstereComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->player		= playerRef;
	properties->energyBar	= energyBarRef;
	properties->IsMan		= IsMan;

	properties->isReadyToUse = true;
	properties->drinkSFX = H3_Sound_Load("assets/SFX/DrinkSFX.wav");

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MonstereComponent, MONSTERECOMPONENT_TYPEID, bool, isReadyToUse);