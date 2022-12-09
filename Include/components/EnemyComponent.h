#ifndef ENEMYCOMPONENT_H_
#define ENEMYCOMPONENT_H_

#include <h3.h>

#define ENEMYCOMPONENT_TYPEID 0x10000005

H3_CAPI_BEGIN_BLOCK
void EnemyComponent_Terminate(void* properties);
void EnemyComponentUpdate(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void EnemyCollision(H3Handle object, SH3Collision obj_id);

void* EnemyComponent_CreateProperties(H3Handle* player,int* raycast_index,H3Handle* GameScene);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EnemyComponent, bool, IsAggro);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EnemyComponent, float, AggroTimer);

H3_CAPI_END_BLOCK

#define ENEMYCOMPONENT_CREATE(PLAYER,RAYCASTINDEX,GAMESCENE)                                          \
	(SH3Component) {                                                            \
		.Terminate          = EnemyComponent_Terminate,                                 \
		.Update             = EnemyComponentUpdate,                  \
		.OnCollisionEnter   = EnemyCollision,   \
		.isInitialized      = false,             \
		.componentType      = ENEMYCOMPONENT_TYPEID,                                    \
		.properties         = EnemyComponent_CreateProperties(PLAYER,RAYCASTINDEX,GAMESCENE) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */
