#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <mqrender/types.h>

MQbuffer *MQCreateBuffer();

bool MQInitBuffer(MQbuffer *_buffer,
		const MQvec2 _size);

bool MQResizeBuffer(MQbuffer *_buffer,
		const MQvec2 _size);

void MQFreeBuffer(MQbuffer *_buffer);
