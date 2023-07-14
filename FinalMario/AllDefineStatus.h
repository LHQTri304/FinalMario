#pragma once
#include "AniIDs.h"


//	### Goomba ###
#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 12
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_FLIGHT_TIME	33.0f
#define GOOMBA_FLYING_SPEED	0.1f

#define GOOMBA_STATE_FLYING 300
#define GOOMBA_STATE_DROPING 301



//	### Koopa ###
#define KOOPA_GRAVITY 0.0005f
#define KOOPA_GRAVITY_KICKED 0.005f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_KICKED_SPEED 0.35f
#define KOOPA_FLYING_SPEED	0.25f
#define KOOPA_AVOID_FALL_BUG_VY 0.06f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_STUNNED 17

#define	KOOPA_LEVEL_SHELL 1
#define	KOOPA_LEVEL_WALK 2
#define	KOOPA_LEVEL_FLY 3

#define KOOPA_STUNNED_TIMEOUT 9000
#define KOOPA_REVIVING_TIMEOUT 2000

#define KOOPA_STATE_MOVING 100
#define KOOPA_STATE_STUNNED 200
#define KOOPA_STATE_REVIVE 201
#define KOOPA_STATE_KICKED 202



//	### FakeHead ###
#define FAKEHEAD_GRAVITY 0.2f

#define FAKEHEAD_BBOX_WIDTH 16
#define FAKEHEAD_BBOX_HEIGHT 24



//	### FirePlant ###
#define FIREPLANT_MOVING_SPEED 0.05f

#define FIREPLANT_BBOX_WIDTH 16
#define FIREPLANT_BBOX_HEIGHT 24

#define FIREPLANT_SAFE_WIDTH 50
#define FIREPLANT_LOWEST_HEIGHT 380
#define FIREPLANT_FIRE_TIME 50

#define FIREPLANT_STATE_MOVING_UP 100
#define FIREPLANT_STATE_MOVING_DOWN 101
#define FIREPLANT_STATE_FIRING 200
#define FIREPLANT_STATE_PAUSE 300



//	### BulletFire ###
#define BULLETFIRE_MOVING_SPEED_X 0.05f
#define BULLETFIRE_MOVING_SPEED_Y 0.02f

#define BULLETFIRE_WRONG_COLLISION_TIMEOUT 5

#define BULLETFIRE_BBOX_WIDTH 7
#define BULLETFIRE_BBOX_HEIGHT 7

#define BULLETFIRE_STATE_INSIDE_PLANT 100
#define BULLETFIRE_STATE_FIRING_UPLEFT 200
#define BULLETFIRE_STATE_FIRING_DOWNLEFT 201
#define BULLETFIRE_STATE_FIRING_UPRIGHT 202
#define BULLETFIRE_STATE_FIRING_DOWNRIGHT 203



//	### BitePlant ###
#define BITEPLANT_MOVING_SPEED 0.05f

#define BITEPLANT_BBOX_WIDTH 16
#define BITEPLANT_BBOX_HEIGHT 24

#define BITEPLANT_LOWEST_HEIGHT 380
#define BITEPLANT_BITE_TIME 75	//Pause time

#define BITEPLANT_STATE_MOVING_UP 100
#define BITEPLANT_STATE_MOVING_DOWN 101
#define BITEPLANT_STATE_BITING 150



//	### Brick ###
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16



//	### QuestBrick ###
#define QUESTBRICK_STATE_WAIT 100
#define QUESTBRICK_STATE_ACTIVATED 200

#define BRICK_ACTIVATED_TIME 5000



//	### Coin ###
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_ACTIVATED_SPEED 0.001f

#define COIN_PIXEL_MOVING_Y 64

#define COIN_STATE_WAIT 100
#define COIN_STATE_ACTIVATED 200



//	### ItemsLevelUp ###
#define ITEMS_LEVELUP_BBOX_WIDTH 14
#define ITEMS_LEVELUP_BBOX_HEIGHT 14

#define ITEMS_LEVELUP_WRONG_COLLISION_TIMEOUT 5

#define ITEMS_LEVELUP_STATE_WAIT 100
#define ITEMS_LEVELUP_STATE_ACTIVATED 200
#define ITEMS_LEVELUP_STATE_MOVING 300
#define ITEMS_LEVELUP_STATE_DELETED 400

#define ITEMS_LEVELUP_KIND_MUSHROOM 0
#define ITEMS_LEVELUP_KIND_LEAF 1



//	### Mushroom ###
#define MUSHROOM_GRAVITY 0.002f	//Count as "ay" because mushroom drop normally
#define MUSHROOM_SPEED 0.07f
#define MUSHROOM_ACTIVATED_SPEED 0.2f

#define MUSHROOM_ACTIVATED_PIXEL_MOVE_Y 16



//	### Leaf ###
#define LEAF_GRAVITY 0.02f	//Count as vy instead of ay because leaf falls slowly and steadily
#define LEAF_SPEED 0.05f
#define LEAF_ACTIVATED_SPEED 3.5f

#define LEAF_ACTIVATED_PIXEL_MOVE_X 32
#define LEAF_ACTIVATED_PIXEL_MOVE_Y 48



//	### Star ###
#define STAR_GRAVITY 0.0018f	//Count as "ay" because star drop normally
#define STAR_SPEED_X 0.0005f
#define STAR_SPEED_Y 0.0025f
#define STAR_ACTIVATED_SPEED 0.5f

#define STAR_BBOX_WIDTH 16
#define STAR_BBOX_HEIGHT 16

#define STAR_PIXEL_MOVING_Y 80

#define STAR_STATE_WAIT 100
#define STAR_STATE_ACTIVATED 200
#define STAR_STATE_MOVING_DOWN 300