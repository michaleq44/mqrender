#include <buffer.h>

MQbuffer *MQCreateBuffer() {
	auto const buf = (MQbuffer*)malloc(sizeof(MQbuffer));
	return buf;
}

bool MQInitBuffer(MQbuffer *_buffer,
		const MQvec2 _size) {
	_buffer->data = (MQcolor_t*)malloc(sizeof(MQcolor_t) * _size.x * _size.y);
	if (!_buffer->data) return false;

	_buffer->size = _size;

	return true;
}

bool MQResizeBuffer(MQbuffer *_buffer,
		const MQvec2 _size) {
	_buffer->data = (MQcolor_t*)realloc(_buffer->data, sizeof(MQcolor_t) * _size.x * _size.y);
	if (!_buffer->data) return false;

	_buffer->size = _size;

	return true;
}

void MQClearBuffer(const MQbuffer *_buffer) {
	memset(_buffer->data, 0, _buffer->size.x * _buffer->size.y * sizeof(MQcolor_t));
}

void MQFillBuffer(const MQbuffer *_buffer,
		const MQcolor_t _color) {
	for (size_t i = 0; i < _buffer->size.x * _buffer->size.y; i++) _buffer->data[i] = _color;
}

void MQFreeBuffer(MQbuffer *_buffer) {
	free(_buffer->data);
	free(_buffer);
}
