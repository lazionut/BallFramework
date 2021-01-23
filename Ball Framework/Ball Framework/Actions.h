#pragma once
#include <stdint.h>

namespace BallFramework
{

	enum class Actions : uint8_t
	{
		NONE,

		SPEEDCHANGE,

		PADDLESIZECHANGE,
		PADDLESPEEDCHANGE,

		BALLSIZECHANGE,
		BALLSPEEDCHANGE,

		BONUSPOINTS,
		REMOVEPOINTS,

		//numarul de actiuni
		ACTIONSNUMBER
	};

}