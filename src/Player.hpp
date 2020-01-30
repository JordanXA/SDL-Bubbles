#pragma once

#include "Object.hpp"

enum PlrInputFlag {
    INFLAG_UP = 1,
    INFLAG_DOWN = 2,
	INFLAG_LEFT = 4,
	INFLAG_RIGHT = 8,
	//INFLAG_FOCUS = 16,
	//INFLAG_SHOT = 32,
	//INFLAG_SKIP = 64
};

class Player : public Object {
    public:
        void inputUpdate();
};