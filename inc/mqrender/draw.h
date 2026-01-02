#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <mqrender/types.h>
#include <mqrender/buffer.h>

MQdraw_return_value MQSetPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
        const MQcolor_t _color);

MQdraw_return_value MQBlendPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
		const MQcolor_t _color);

MQdraw_return_value MQDrawPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
		const bool _blend, const MQcolor_t _color);

MQdraw_return_value MQDrawHorizontalLine(const MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _width, const MQdirection _direction,
		const bool _blend, const MQcolor_t _color);

MQdraw_return_value MQDrawVerticalLine(const MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _height, const MQdirection _direction,
		const bool _blend, const MQcolor_t _color);

MQdraw_return_value MQDrawLine(const MQbuffer *_buffer,
		const MQvec2 _coord1, const MQvec2 _coord2,
		const bool _blend, const MQcolor_t _color);

MQdraw_return_value MQDrawRect(const MQbuffer *_buffer,
		const MQvec2 _topleft, const MQvec2 _bottomright,
		const bool _blend, const bool _fill, const MQcolor_t _color);

MQdraw_return_value MQBlitBuffer(const MQbuffer *_dest, const MQbuffer *_src,
		const MQvec2 _topleft,
		const bool _blend);

MQdraw_return_value MQDrawTriangle(const MQbuffer *_buffer,
		const MQvec2 _v1, const MQvec2 _v2, const MQvec2 _v3,
		const bool _blend, const bool _fill, const MQcolor_t _color);

MQdraw_return_value MQDrawPolygon(const MQbuffer *_buffer,
		const MQvec2 *_vertices, const size_t _n_vertices,
		const bool _blend, const bool _fill, const MQcolor_t _color);
