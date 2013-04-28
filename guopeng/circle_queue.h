/*
 * circle_queue.h
 *
 *  Created on: 2011-11-11
 *      Author: kevinguo
 */

#ifndef CIRCLE_QUEUE_H_
#define CIRCLE_QUEUE_H_
#include <stdlib.h>

template <typename T>
class CircleQueue {
public:
	CircleQueue()
	: m_data_array(NULL)
	, size(0)
	, capactity(0)
	, head(0)
	, tail(-1) {}

	virtual ~CircleQueue() {}

	bool Init(int _size) {
		assert(_size > 0);
		capactity = _size;
		m_data_array = new T[_size];
		assert(m_data_array != NULL);
		memset(m_data_array, 0, sizeof(T)*size);

		size = 0;
		head = 0;
		tail = -1;
		return false;
	}
    bool UnInit() {
    	if (NULL == m_data_array) {
    		return false;
    	}
    	delete [] m_data_array;
    }
    bool Push(const T &data) {
    	if (size >= capactity) {
    		return false;
    	}
    	tail = (tail + 1)%capactity;
    	m_data_array[tail] = data;
    	size += 1;
    	return true;
    }
    bool Pop(T &data) {
    	if (size == 0) {
    		return false;
    	}
    	data = m_data_array[head];
    	head = (head + 1)%capactity;
    	size--;
    	return true;
    }

    int GetSize() const{
    	return size;
    }

private:
	T *m_data_array;
	int size;
	int capactity;
	int head;
	int tail;

};

#endif /* CIRCLE_QUEUE_H_ */
