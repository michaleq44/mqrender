#include <draw.h>

MQdraw_return_value MQSetPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
        const MQcolor_t _color) {
	 if (_coord.x >= _buffer->size.x || _coord.y >= _buffer->size.y)
		return MQ_OUT_OF_BOUNDS;

	_buffer->data[_coord.y * _buffer->size.x +
		_coord.x] = _color; 
	return MQ_DRAWN_FULL;
}

MQdraw_return_value MQBlendPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
		const MQcolor_t _color) {
	const MQretval_color point = MQGetPoint(_buffer, _coord);
	if (!point.success) return MQ_OUT_OF_BOUNDS;
	return MQSetPoint(_buffer, _coord, MQBlendColors(
				point.value,
				_color));
}

MQdraw_return_value MQDrawPoint(const MQbuffer *_buffer,
		const MQvec2 _coord,
		const bool _blend, const MQcolor_t _color) {
	return _blend ? MQBlendPoint(_buffer, _coord, _color) : MQSetPoint(_buffer, _coord, _color);;
}

MQdraw_return_value MQDrawHorizontalLine(const MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _width, const MQdirection _direction,
		const bool _blend, const MQcolor_t _color) {
	MQdraw_return_value ret = MQ_DRAWN_FULL;
	MQvec2 current = _coord;
	if (_direction == MQ_UPLEFT) {
		for (size_t counter = 1; counter <= _width; current.x--, counter++)
			ret |= MQDrawPoint(_buffer,
				current,
				_blend, _color);
	} else {
		for (size_t counter = 1; counter <= _width; current.x++, counter++)
			ret |= MQDrawPoint(_buffer,
				current,
				_blend, _color);
	}		
	return ret;
}

MQdraw_return_value MQDrawVerticalLine(const MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _height, const MQdirection _direction,
		const bool _blend, const MQcolor_t _color) {
	MQvec2 current = _coord;
	MQdraw_return_value ret = MQ_DRAWN_FULL;
	if (_direction == MQ_UPLEFT)
		for (size_t counter = 1; counter <= _height; current.y--, counter++)
			ret |= MQDrawPoint(_buffer,
				current,
				_blend, _color);
	else
		for (size_t counter = 1; counter <= _height; current.y++, counter++)
			ret |= MQDrawPoint(_buffer,
				current,
				_blend, _color);
	return ret;
}

//#include <stdio.h>
MQdraw_return_value MQDrawLine(const MQbuffer *_buffer,
		const MQvec2 _coord1, const MQvec2 _coord2,
		const bool _blend, const MQcolor_t _color) {
	if (MQVec2Eq(_coord1, _coord2)) return MQDrawPoint(_buffer,
			_coord1,
			_blend, _color);

	const size_t right = max(_coord1.x, _coord2.x);
	const size_t left = min(_coord1.x, _coord2.x);

	const size_t bottom = max(_coord1.y, _coord2.y);
	const size_t top = min(_coord1.y, _coord2.y);

	const size_t width = right - left + 1;
	const size_t height = bottom - top + 1;

	if (width == 1) return MQDrawVerticalLine(_buffer,
			MQVec2(left, top), height, MQ_DOWNRIGHT,
			_blend, _color);
	if (height == 1) return MQDrawHorizontalLine(_buffer,
			MQVec2(left, top), width, MQ_DOWNRIGHT,
			_blend, _color);
	MQdraw_return_value ret = MQ_DRAWN_FULL;
	if (width == 2) {
		ret |= MQDrawVerticalLine(_buffer,
				MQVec2(left, top), height >> 1, MQ_DOWNRIGHT,
				_blend, _color);
		ret |= MQDrawVerticalLine(_buffer,
				MQVec2(left + 1, top + (height >> 1)), (height >> 1) + (height & 1), MQ_DOWNRIGHT,
				_blend, _color);
		return ret;
	}
	if (height == 2) {
		ret |= MQDrawHorizontalLine(_buffer,
				MQVec2(left, top), width >> 1, MQ_DOWNRIGHT,
				_blend, _color);
		ret |= MQDrawHorizontalLine(_buffer,
				MQVec2(left + (width >> 1), top + 1), (width >> 1) + (width & 1), MQ_DOWNRIGHT,
				_blend, _color);
		return ret;
	}
	
	//printf("w: %lu, h: %lu\n", width, height);
	MQvec2 current = {left, top};
	if (width > height) {
		const size_t dx = width / height + (width % height > height / 2);
		const size_t dxstart = (width - (height-2) * (dx)) / 2;
		const size_t dxend = (width - (height-2) * (dx)) - dxstart;
		//printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dxstart); 
		ret |= MQDrawHorizontalLine(_buffer,
				current, dxstart, MQ_DOWNRIGHT,
				_blend, _color);
		current.x += dxstart;
		current.y++;
		for ( ; current.x < right; current.x+=dx, current.y++) {
			//printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dx); 
			ret |= MQDrawHorizontalLine(_buffer,
					current, dx, MQ_DOWNRIGHT,
					_blend, _color);
		}
		//printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dx - dxend); 
		ret |= MQDrawHorizontalLine(_buffer,
				current, dxend, MQ_DOWNRIGHT,
				_blend, _color);
	} else {
		const size_t dy = height / width + (height % width > width / 2);
		const size_t dystart = (height - (width-2) * dy) / 2;
		const size_t dyend = height - (width-2) * dy - dystart;
		//printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dystart); 
		ret |= MQDrawVerticalLine(_buffer,
				current, dystart, MQ_DOWNRIGHT,
				_blend, _color);
		current.x++;
		current.y += dystart;
		for ( ; current.y < bottom; current.y+=dy, current.x++) {
			//printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dy); 
			ret |= MQDrawVerticalLine(_buffer,
					current, dy, MQ_DOWNRIGHT,
					_blend, _color);
		}
		//printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dyend); 
		ret |= MQDrawHorizontalLine(_buffer,
				current, dyend, MQ_DOWNRIGHT,
				_blend, _color);
	}

	return ret;
}

MQdraw_return_value MQDrawRect(const MQbuffer *_buffer,
		const MQvec2 _topleft, const MQvec2 _bottomright,
		const bool _blend, const bool _fill, const MQcolor_t _color) {
	MQdraw_return_value ret = MQ_DRAWN_FULL;
	const size_t width = _bottomright.x - _topleft.x + 1;
	const size_t height = _bottomright.y - _topleft.y + 1;
	if (!_fill) {
		ret |= MQDrawHorizontalLine(_buffer,
				MQVec2(_topleft.x, _topleft.y), width, MQ_DOWNRIGHT,
				_blend, _color);
		ret |= MQDrawVerticalLine(_buffer,
				MQVec2(_bottomright.x, _topleft.y), height, MQ_DOWNRIGHT,
				_blend, _color);
		ret |= MQDrawHorizontalLine(_buffer,
				MQVec2(_bottomright.x, _bottomright.y), width, MQ_UPLEFT,
				_blend, _color);
		ret |= MQDrawVerticalLine(_buffer,
				MQVec2(_topleft.x, _bottomright.y), height, MQ_UPLEFT,
				_blend, _color);
		return ret;
	}
	
	if (width > height) {
		for (size_t y = _topleft.y; y <= _bottomright.y; y++) {
			ret |= MQDrawHorizontalLine(_buffer,
					MQVec2(_topleft.x, y), width, MQ_DOWNRIGHT,
					_blend, _color);
		}
	} else {
		for (size_t x = _topleft.x; x <= _bottomright.x; x++) {
			ret |= MQDrawVerticalLine(_buffer,
					MQVec2(x, _topleft.y), height, MQ_DOWNRIGHT,
					_blend, _color);
		}
	}

	return ret;
}

MQdraw_return_value MQBlitBuffer(const MQbuffer *_dest, const MQbuffer *_src,
		const MQvec2 _topleft,
		const bool _blend) {
	MQdraw_return_value ret = MQ_DRAWN_FULL;

	for (size_t y = 0; y < _src->size.y; y++) {
		for (size_t x = 0; x < _src->size.x; x++) {
			ret |= MQDrawPoint(_dest,
					MQVec2(_topleft.x + x, _topleft.y + y),
					_blend, MQGetPointUNSAFE(_src, MQVec2(x, y)));
		}
	}

	return ret;
}

MQdraw_return_value MQDrawTriangle(const MQbuffer *_buffer,
		const MQvec2 _v1, const MQvec2 _v2, const MQvec2 _v3,
		const bool _blend, const bool _fill, const MQcolor_t _color) {
	const size_t left = min3(_v1.x, _v2.x, _v3.x);
	const size_t top = min3(_v1.y, _v2.y, _v3.y);
	const size_t right = max3(_v1.x, _v2.x, _v3.x);
	const size_t bottom = max3(_v1.y, _v2.y, _v3.y);

	const size_t width = right + 1 - left;
	const size_t height = bottom + 1 - top;

	MQdraw_return_value ret = MQ_DRAWN_FULL;
	if (!_fill) {
		ret |= MQDrawLine(_buffer,
			_v1, _v2,
			_blend, _color);
		ret |= MQDrawLine(_buffer,
			_v2, _v3,
			_blend, _color);
		ret |= MQDrawLine(_buffer,
			_v3, _v1,
			_blend, _color);
		return ret;
	}

	MQbuffer *tmpbuf = MQCreateBuffer();
	if (tmpbuf == NULL) return MQ_MEMORY_ALLOC_ERROR;
	if (!MQInitBuffer(tmpbuf, MQVec2(width, height))) return MQ_MEMORY_ALLOC_ERROR;
	ret |= MQDrawLine(tmpbuf,
		_v1, _v2,
		false, 1);
	ret |= MQDrawLine(tmpbuf,
		_v2, _v3,
		false, 1);
	ret |= MQDrawLine(tmpbuf,
		_v3, _v1,
		false, 1);
	size_t x1, x2;
	size_t k;
	for (MQvec2 current = {0, 0}; current.y < height; current.y++) {
		x1 = 0, x2 = 0, k = 0;
		for (current.x = 0; current.x < width; current.x++) {
			if (MQGetPointUNSAFE(tmpbuf, current)) {
				if (k == 0) {
					x1 = current.x;
					k = 1;
				}
				else if (k == 1) {
					x2 = current.x;
					k = 2;
				} else break;
			}
		}
		if (k == 2) ret |= MQDrawHorizontalLine(tmpbuf,
			MQVec2(x1, current.y), x2 + 1 - x1, MQ_DOWNRIGHT,
			false, _color);
	}

	ret |= MQBlitBuffer(_buffer, tmpbuf,
		MQVec2(left, top),
		_blend);
	MQFreeBuffer(tmpbuf);

	return ret;
}

MQdraw_return_value MQDrawPolygon(const MQbuffer *_buffer,
		const MQvec2 *_vertices, const size_t _n_vertices,
		const bool _blend, const bool _fill, const MQcolor_t _color) {
	size_t right = 0, bottom = 0;
	size_t left = SIZE_MAX, top = SIZE_MAX;
	MQbuffer *tmpbuf = MQCreateBuffer();
	if (tmpbuf == NULL) return MQ_MEMORY_ALLOC_ERROR;
	for (size_t i = 0; i < _n_vertices; i++) {
		left = min(left, _vertices[i].x);
		top = min(top, _vertices[i].y);
		right = max(right, _vertices[i].x);
		bottom = max(bottom, _vertices[i].y);
	}
	const size_t width = right + 1 - left;
	const size_t height = bottom + 1 - top;

	MQInitBuffer(tmpbuf, MQVec2(width, height));
	for (size_t i = 0; i < _n_vertices; i++) {

	}
}
