#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))

#ifndef min3
#define min3(x, y, z) min(min(x, y), z)
#endif
#endif

#ifndef max
#define max(x, y) (((x) > (y)) ? (x) : (y))

#ifndef max3
#define max3(x, y, z) max(max(x, y), z)
#endif

#endif

#define MQDefineReturnValueStruct(type, name) typedef struct {type value; bool success;} name;

typedef uint32_t MQcolor_t;
typedef uint32_t MQcolor_blend_t;
typedef uint8_t MQcolor_channel_t;

typedef enum MQdraw_return_value {
	MQ_DRAWN_FULL = 0,
	MQ_OUT_OF_BOUNDS = 1,
	MQ_INVALID_ARGS = 2,
	MQ_MEMORY_ALLOC_ERROR = 4
} MQdraw_return_value;

typedef enum MQdirection {
	MQ_UPLEFT,
	MQ_DOWNRIGHT
} MQdirection;

typedef struct MQvec2 {
	size_t x, y;
} MQvec2;

typedef struct MQrgba {
	MQcolor_channel_t r, g, b, a;
} MQrgba;

typedef struct MQbuffer {
	// RGBA8888 format: 0xRRGGBBAA
	MQcolor_t *data;
	MQvec2 size;
} MQbuffer;

// retvals
MQDefineReturnValueStruct(MQcolor_t, MQretval_color)


bool MQVec2Eq(MQvec2 _v1, MQvec2 _v2);
MQvec2 MQVec2(size_t _x, size_t _y);
MQrgba MQRGBA(MQcolor_channel_t _r, MQcolor_channel_t _g, MQcolor_channel_t _b,
		MQcolor_channel_t _a);
MQrgba MQColorToRGBA(MQcolor_t _col);
MQcolor_t MQRGBAtoColor(MQrgba _rgba);
MQcolor_t MQBlendColors(MQcolor_t _color_dest, MQcolor_t _color_src);
MQretval_color MQGetPoint(const MQbuffer *_buffer, const MQvec2 _coords);
MQcolor_t MQGetPointUNSAFE(const MQbuffer *_buffer, const MQvec2 _coords);
