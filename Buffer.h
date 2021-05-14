#pragma once
#include <vector>
class Buffer
{
private:
	std::vector<char> m_buffer;
	unsigned int m_marker;
public:
	void push(const char* data, const int& size);
	void read(char* data, const int& size);
	bool endOfBuffer() const;
	const char* getBuffer() const;
	void clear();
	unsigned int getSize() const;
	void markerReset();
	Buffer();
	~Buffer();
};

