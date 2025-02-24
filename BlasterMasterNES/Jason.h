#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define JASON_WALKING_SPEED		0.1f
#define JASON_RUNNING_SPEED		0.2f

#define JASON_ACCEL_WALK_X	0.0005f
#define JASON_ACCEL_RUN_X	0.0007f

#define JASON_JUMP_SPEED_Y		0.5f
#define JASON_JUMP_RUN_SPEED_Y	0.6f

#define JASON_GRAVITY			0.002f

#define JASON_JUMP_DEFLECT_SPEED  0.4f

#define JASON_STATE_DIE				-10
#define JASON_STATE_IDLE			0
#define JASON_STATE_WALKING_RIGHT	100
#define JASON_STATE_WALKING_LEFT	200

#define JASON_STATE_JUMP			300
#define JASON_STATE_RELEASE_JUMP    301

#define JASON_STATE_RUNNING_RIGHT	400
#define JASON_STATE_RUNNING_LEFT	500

#define JASON_STATE_SIT				600
#define JASON_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_JASON_IDLE_RIGHT 400
#define ID_ANI_JASON_IDLE_LEFT 401

#define ID_ANI_JASON_WALKING_RIGHT 500
#define ID_ANI_JASON_WALKING_LEFT 501

#define ID_ANI_JASON_RUNNING_RIGHT 600
#define ID_ANI_JASON_RUNNING_LEFT 601

#define ID_ANI_JASON_JUMP_WALK_RIGHT 700
#define ID_ANI_JASON_JUMP_WALK_LEFT 701

#define ID_ANI_JASON_JUMP_RUN_RIGHT 800
#define ID_ANI_JASON_JUMP_RUN_LEFT 801

#define ID_ANI_JASON_SIT_RIGHT 900
#define ID_ANI_JASON_SIT_LEFT 901

#define ID_ANI_JASON_BRACE_RIGHT 1000
#define ID_ANI_JASON_BRACE_LEFT 1001

#define ID_ANI_JASON_DIE 999

// SMALL JASON
#define ID_ANI_JASON_SMALL_IDLE_RIGHT 1100
#define ID_ANI_JASON_SMALL_IDLE_LEFT 1102

#define ID_ANI_JASON_SMALL_WALKING_RIGHT 1200
#define ID_ANI_JASON_SMALL_WALKING_LEFT 1201

#define ID_ANI_JASON_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_JASON_SMALL_RUNNING_LEFT 1301

#define ID_ANI_JASON_SMALL_BRACE_RIGHT 1400
#define ID_ANI_JASON_SMALL_BRACE_LEFT 1401

#define ID_ANI_JASON_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_JASON_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_JASON_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_JASON_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#define GROUND_Y 160.0f




#define	JASON_LEVEL_SMALL	1
#define	JASON_LEVEL_BIG		2

#define JASON_BIG_BBOX_WIDTH  14
#define JASON_BIG_BBOX_HEIGHT 24
#define JASON_BIG_SITTING_BBOX_WIDTH  14
#define JASON_BIG_SITTING_BBOX_HEIGHT 16

#define JASON_SIT_HEIGHT_ADJUST ((JASON_BIG_BBOX_HEIGHT-JASON_BIG_SITTING_BBOX_HEIGHT)/2)

#define JASON_SMALL_BBOX_WIDTH  13
#define JASON_SMALL_BBOX_HEIGHT 12


#define JASON_UNTOUCHABLE_TIME 2500

class CJason : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;

	void OnCollisionWithBlackfoot(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CJason(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = JASON_GRAVITY;

		level = JASON_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != JASON_STATE_DIE);
	}

	int IsBlocking() { return (state != JASON_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};