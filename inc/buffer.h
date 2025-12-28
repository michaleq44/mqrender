#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

bool MQInitBuffer(MQbuffer *_buffer,
		const MQvec2 size);

bool MQResizeBuffer(MQbuffer *_buffer,
		const MQvec2 size);

void MQFreeBuffer(MQbuffer *_buffer);
