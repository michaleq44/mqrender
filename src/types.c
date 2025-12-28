#include "types.h"

bool MQVec2Eq(MQvec2 _v1, MQvec2 _v2) {
	return _v1.x == _v2.x && _v1.y == _v2.y;
}

MQvec2 MQVec2(size_t _x, size_t _y) {
	MQvec2 ret = {_x, _y};
	return ret;
}
