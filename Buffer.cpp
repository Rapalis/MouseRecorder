#include "Buffer.h"

Buffer::Buffer(): m_marker(0)
{
	m_buffer.reserve(60000);
}


Buffer::~Buffer()
{
}

void Buffer::push(const char * data, const int & size)
{
	for (int i = 0; i < size; i++)
	{
		m_buffer.push_back(data[i]);
	}
}

void Buffer::read(char * data, const int & size)
{
	for (int i = 0; i < size; i++)
	{
		data[i] = m_buffer.data()[m_marker];
		m_marker++;
	}
}

bool Buffer::endOfBuffer() const
{
	return (m_buffer.size() - 1 > m_marker) ? false : true;
}

const char * Buffer::getBuffer() const
{
	return m_buffer.data();
}


void Buffer::clear()
{
	m_marker = 0;
	m_buffer.clear();
}

unsigned int Buffer::getSize() const
{
	return m_buffer.size();
}

void Buffer::markerReset()
{
	m_marker = 0;
}
