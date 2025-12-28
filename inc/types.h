#pragma once

#include <stdint.h>
#include <stddef.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef uint32_t MQcolor_t;
typedef uint8_t MQcolor_channel_t;

typedef enum MQdraw_return_value {
	MQ_DRAWN_FULL,
	MQ_OUT_OF_BOUNDS
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

bool MQVec2Eq(MQvec2 _v1, MQvec2 _v2);
MQvec2 MQVec2(size_t _x, size_t _y);
