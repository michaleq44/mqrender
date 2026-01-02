#include <buffer.h>

MQbuffer *MQCreateBuffer() {
	const auto buf = (MQbuffer*)malloc(sizeof(MQbuffer));
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
	MQcolor_t *bufdata = malloc(_size.x * _size.y * sizeof(MQcolor_t));
	if (bufdata == NULL) return false;
	for (size_t y = 0; y < min(_buffer->size.y, _size.y); y++)
		memcpy(bufdata + y * _size.x * sizeof(MQcolor_t),
				_buffer->data + y * _buffer->size.x * sizeof(MQcolor_t),
				min(_buffer->size.x, _size.x));
	free(_buffer->data);
	_buffer->data = bufdata;
	_buffer->size = _size;

	return true;
}

void MQFreeBuffer(MQbuffer *_buffer) {
	free(_buffer->data);
	free(_buffer);
}
