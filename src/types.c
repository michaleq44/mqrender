#include <stdlib.h>
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
		_col >> (sizeof(MQcolor_channel_t) * 24) & MQCOLOR_CHANNEL_MAX,
		_col >> (sizeof(MQcolor_channel_t) * 16) & MQCOLOR_CHANNEL_MAX,
		_col >> sizeof(MQcolor_channel_t) * 8 & MQCOLOR_CHANNEL_MAX,
		_col & MQCOLOR_CHANNEL_MAX
	};

	return ret;
}

MQcolor_t MQRGBAToColor(const MQrgba _rgba) {
//	printf("%x %x %x %x", _rgba.r, _rgba.g, _rgba.b, _rgba.a);
	MQcolor_t col = _rgba.r;
	col <<= sizeof(MQcolor_channel_t) * 8;
	col |= _rgba.g;
	col <<= sizeof(MQcolor_channel_t) * 8;
	col |= _rgba.b;
	col <<= sizeof(MQcolor_channel_t) * 8;
	col |= _rgba.a;
	return col;
}

MQcolor_t MQBlendColors(const MQcolor_t _color_dest, const MQcolor_t _color_src) {
	const MQrgba _coldest = MQColorToRGBA(_color_dest);
	const MQrgba _colsrc = MQColorToRGBA(_color_src);

	const MQcolor_channel_t alpha = _colsrc.a + _coldest.a * (MQCOLOR_CHANNEL_MAX - _colsrc.a) / MQCOLOR_CHANNEL_MAX;
	const MQcolor_blend_t red = (_colsrc.r * _colsrc.a +
		_coldest.r * _coldest.a * (MQCOLOR_CHANNEL_MAX - _colsrc.a) / MQCOLOR_CHANNEL_MAX) / alpha;
	const MQcolor_blend_t green = (_colsrc.g * _colsrc.a +
		_coldest.g * _coldest.a * (MQCOLOR_CHANNEL_MAX - _colsrc.a) / MQCOLOR_CHANNEL_MAX) / alpha;
	const MQcolor_blend_t blue = (_colsrc.b * _colsrc.a +
		_coldest.b * _coldest.a * (MQCOLOR_CHANNEL_MAX - _colsrc.a) / MQCOLOR_CHANNEL_MAX) / alpha;

	return MQRGBAToColor(MQRGBA(red, green, blue, alpha));
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

MQcolor_t MQRGBAElementsToColor(const MQcolor_channel_t _r, const MQcolor_channel_t _g, const MQcolor_channel_t _b,
		const MQcolor_channel_t _a) {
	return MQRGBAToColor(MQRGBA(_r, _g, _b, _a));
}

MQcolor_t MQRGBElementsToColor(const MQcolor_channel_t _r, const MQcolor_channel_t _g, const MQcolor_channel_t _b) {
	return MQRGBAToColor(MQRGBA(_r, _g, _b, MQCOLOR_CHANNEL_MAX));
}