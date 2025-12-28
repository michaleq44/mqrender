#include "buffer.h"

bool MQInitBuffer(MQbuffer *_buffer,
		const MQvec2 _size) {
	_buffer->data = malloc(_size.x * _size.y * sizeof(MQcolor_t));
	if (_buffer->data == NULL) return false;
	_buffer->size = _size;

	return true;
}

bool MQResizeBuffer(MQbuffer *_buffer,
		const MQvec2 _size) {
	_buffer->data = realloc(_buffer->data, _size.x * _size.y * sizeof(MQcolor_t));
	if (_buffer->data == NULL) return false;
	_buffer->size = _size;

	return true;
}

void MQFreeBuffer(MQbuffer *_buffer) {
	free(_buffer->data);
	_buffer->size.x = 0, _buffer->size.y = 0;
}
