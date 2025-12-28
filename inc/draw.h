#pragma once

#include "types.h"

MQdraw_return_value MQDrawPoint(MQbuffer *_buffer,
		const MQvec2 _coord,
		const MQcolor_t _color);

MQdraw_return_value MQDrawHorizontalLine(MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _width, const MQdirection _direction,
		const MQcolor_t _color);

MQdraw_return_value MQDrawVerticalLine(MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _height, const MQdirection _direction,
		const MQcolor_t _color);

MQdraw_return_value MQDrawLine(MQbuffer *_buffer,
		const MQvec2 _coord1, const MQvec2 _coord2,
		const MQcolor_t _color);
