#include <mqrender/types.h>

bool MQVec2Eq(const MQvec2 _v1, const MQvec2 _v2) {
	return _v1.x == _v2.x && _v1.y == _v2.y;
}

MQvec2 MQVec2(const size_t _x, const size_t _y) {
	const MQvec2 ret = {_x, _y};
	return ret;
}

MQrgba MQRGBA(const MQcolor_channel_t _r, const MQcolor_channel_t _g, const MQcolor_channel_t _b,
              const MQcolor_channel_t _a) {
	const MQrgba ret = {_r, _g, _b, _a};
	return ret;
}

MQrgba MQColorToRGBA(const MQcolor_t _col) {
	const MQrgba ret = {
		_col >> (sizeof(MQcolor_channel_t) * 24) & 0xFF,
		_col >> (sizeof(MQcolor_channel_t) * 16) & 0xFF,
		_col >> sizeof(MQcolor_channel_t) * 8 & 0xFF,
		_col & 0xFF
	};

	return ret;
}

MQcolor_t MQRGBAtoColor(const MQrgba _rgba) {
//	printf("%x %x %x %x", _rgba.r, _rgba.g, _rgba.b, _rgba.a);
	MQcolor_t col = _rgba.r;
	col <<= sizeof(MQcolor_channel_t) << 3;
	col |= _rgba.g;
	col <<= sizeof(MQcolor_channel_t) << 3;
	col |= _rgba.b;
	col <<= sizeof(MQcolor_channel_t) << 3;
	col |= _rgba.a;
	return col;
}

MQcolor_t MQBlendColors(const MQcolor_t _color_dest, const MQcolor_t _color_src) {
	const MQrgba _coldest = MQColorToRGBA(_color_dest);
	const MQrgba _colsrc = MQColorToRGBA(_color_src);

	const MQcolor_channel_t alpha = (MQcolor_blend_t)_colsrc.a + (MQcolor_blend_t)_coldest.a * (MQcolor_blend_t)(0xFF - _colsrc.a) / 0xFF;
	const MQcolor_blend_t red = ((MQcolor_blend_t)_colsrc.r * (MQcolor_blend_t)_colsrc.a +
		(MQcolor_blend_t)_coldest.r * (MQcolor_blend_t)_coldest.a * (MQcolor_blend_t)(0xFF - _colsrc.a) / 0xFF) / alpha;
	const MQcolor_blend_t green = ((MQcolor_blend_t)_colsrc.g * (MQcolor_blend_t)_colsrc.a +
		(MQcolor_blend_t)_coldest.g * (MQcolor_blend_t)_coldest.a * (MQcolor_blend_t)(0xFF - _colsrc.a) / 0xFF) / alpha;
	const MQcolor_blend_t blue = ((MQcolor_blend_t)_colsrc.b * (MQcolor_blend_t)_colsrc.a +
		(MQcolor_blend_t)_coldest.b * (MQcolor_blend_t)_coldest.a * (MQcolor_blend_t)(0xFF - _colsrc.a) / 0xFF) / alpha;

	return MQRGBAtoColor(MQRGBA(red, green, blue, alpha));
}

MQretval_color MQGetPoint(const MQbuffer *_buffer, const MQvec2 _coords) {
	MQretval_color ret = {0, true};
	if (_coords.x >= _buffer->size.x || _coords.y >= _buffer->size.y) ret.success = false;
	else ret.value = _buffer->data[_coords.y * _buffer->size.x + _coords.x];
	return ret;
}

MQcolor_t MQGetPointUNSAFE(const MQbuffer *_buffer, const MQvec2 _coords) {
	return _buffer->data[_coords.y * _buffer->size.x + _coords.x];
}
