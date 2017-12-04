// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

namespace SCENE_STATES
{
	enum E
	{
		Invalid = 0,
		Game,
		NumScenes
	};
}

namespace BOIDSTATE {
	enum e {
		Undefined,
		Idle,
		Attack,
		DefendLeader,
		DefendBase,
		ToBase,
		ToField,
		AttackEnemy,
		Dead,
		Count
	};
}

namespace TEAM {
	enum t {
		Undefined,
		Green,
		Red,
		Count
	};
}

// TODO: reference additional headers your program requires here
