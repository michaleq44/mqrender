#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <mqrender/types.h>

// creates the buffer object pointer
MQbuffer *MQCreateBuffer();

// allocates the buffer's data and sets the size
bool MQInitBuffer(MQbuffer *_buffer,
		const MQvec2 _size);

// resizes the buffer, does not preserve contents
bool MQResizeBuffer(MQbuffer *_buffer,
		const MQvec2 _size);

// fills the buffer with zeroes (faster than MQFillBuffer() because it uses memset, but it can't set color)
void MQClearBuffer(const MQbuffer *_buffer);

// fills the buffer with giben color
void MQFillBuffer(const MQbuffer *_buffer,
		MQcolor_t _color);

// frees the buffer's data memory and the buffer object
void MQFreeBuffer(MQbuffer *_buffer);