#include "draw.h"

MQdraw_return_value MQDrawPoint(MQbuffer *_buffer,
		const MQvec2 _coord,
		const MQcolor_t _color) {
	if (_coord.x >= _buffer->size.x || _coord.y >= _buffer->size.y)
		return MQ_OUT_OF_BOUNDS;

	_buffer->data[_coord.y * _buffer->size.x +
		_coord.x] = _color;
	return MQ_DRAWN_FULL;
}

MQdraw_return_value MQDrawHorizontalLine(MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _width, const MQdirection _direction,
		const MQcolor_t _color) {
	MQvec2 current = _coord;
	MQdraw_return_value ret;
	if (_direction == MQ_UPLEFT)
		while (current.x > _coord.x - _width) {
			ret = MQDrawPoint(_buffer,
					current,
					_color);
			current.x--;
		}
	else
		while (current.x < _coord.x + _width) {
			ret = MQDrawPoint(_buffer,
					current,
					_color);
			current.x++;
		}
	return ret;
}

MQdraw_return_value MQDrawVerticalLine(MQbuffer *_buffer,
		const MQvec2 _coord, const size_t _height, const MQdirection _direction,
		const MQcolor_t _color) {
	MQvec2 current = _coord;
	MQdraw_return_value ret;
	if (_direction == MQ_UPLEFT)
		while (current.y > _coord.y - _height) {
			ret = MQDrawPoint(_buffer,
					current,
					_color);
			current.y--;
		}
	else
		while (current.y < _coord.y + _height) {
			ret = MQDrawPoint(_buffer,
					current,
					_color);
			current.y++;
		}
	return ret;
}

#include <stdio.h>
MQdraw_return_value MQDrawLine(MQbuffer *_buffer,
		const MQvec2 _coord1, const MQvec2 _coord2,
		const MQcolor_t _color) {
	if (MQVec2Eq(_coord1, _coord2)) return MQDrawPoint(_buffer,
			_coord1,
			_color);

	const size_t right = max(_coord1.x, _coord2.x);
	const size_t left = min(_coord1.x, _coord2.x);

	const size_t bottom = max(_coord1.y, _coord2.y);
	const size_t top = min(_coord1.y, _coord2.y);

	const size_t width = right - left + 1;
	const size_t height = bottom - top + 1;

	if (width == 0) return MQDrawVerticalLine(_buffer,
			MQVec2(left, top), height, MQ_DOWNRIGHT,
			_color);
	if (height == 0) return MQDrawHorizontalLine(_buffer,
			MQVec2(left, top), width, MQ_DOWNRIGHT,
			_color);
	
	printf("w: %lu, h: %lu\n", width, height);
	MQvec2 current = {left, top};
	MQdraw_return_value ret;
	if (width > height) {
		const size_t dx = width / height + (width % height > height / 2);
		const size_t dxstart = (width - (height-2) * (dx)) / 2;
		const size_t dxend = (width - (height-2) * (dx)) - dxstart;
		printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dxstart); 
		ret = MQDrawHorizontalLine(_buffer,
				current, dxstart, MQ_DOWNRIGHT,
				_color);
		current.x += dxstart;
		current.y++;
		for ( ; current.x < right; current.x+=dx, current.y++) {
			printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dx); 
			ret = MQDrawHorizontalLine(_buffer,
					current, dx, MQ_DOWNRIGHT,
					_color);
		}
		printf("Drawing %lu %lu w: %lu\n", current.x, current.y, dx - dxend); 
		ret = MQDrawHorizontalLine(_buffer,
				current, dxend, MQ_DOWNRIGHT,
				_color);
	} else {
		const size_t dy = height / width + (height % width > width / 2);
		const size_t dystart = (height - (width-2) * (dy)) / 2;
		const size_t dyend = (height - (width-2) * (dy)) - dystart;
		printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dystart); 
		ret = MQDrawVerticalLine(_buffer,
				current, dystart, MQ_DOWNRIGHT,
				_color);
		current.x++;
		current.y += dystart;
		for ( ; current.y < bottom; current.y+=dy, current.x++) {
			printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dy); 
			ret = MQDrawVerticalLine(_buffer,
					current, dy, MQ_DOWNRIGHT,
					_color);
		}
		printf("Drawing %lu %lu h: %lu\n", current.x, current.y, dyend); 
		ret = MQDrawHorizontalLine(_buffer,
				current, dyend, MQ_DOWNRIGHT,
				_color);
	}

	return ret;
}
