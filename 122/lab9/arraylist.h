#pragma once
#include "list.h"
#include "exceptions.h"
#include <sstream>
#include "bubble.h"

using std::stringstream;
using std::getline;

const int INITIAL_ARRAY_SIZE = 10;

template <typename TYPE>
class ArrayList : public List<TYPE>
{
public:
	ArrayList();
	~ArrayList();
	void insert(TYPE item, int index);
	void remove(int index);
	TYPE at(int index);
	void sort(int(*cmp)(const TYPE& item1, const TYPE& item2), bool doQuicksort);
	int search(TYPE item, int(*cmp)(const TYPE& item1, const TYPE& item2));
	int getSize();

private:
	TYPE* data;
	int tail; // Tail is actually the index of the item AFTER then last item in the list. Doubles as the number of elements in the list
	int currentArraySize;

	void increaseArraySize();

};

template <typename TYPE>
ArrayList<TYPE>::ArrayList()
{
	currentArraySize = INITIAL_ARRAY_SIZE;
	data = new TYPE[currentArraySize];
	tail = 0;
}

template <typename TYPE>
ArrayList<TYPE>::~ArrayList()
{
	delete[] data;
}

template<typename TYPE>
void ArrayList<TYPE>::insert(TYPE item, int index)
{
	// deal with the case where our array is full already
	if (tail == currentArraySize)
	{
		// Call the increaseArraySize helper function
		increaseArraySize();
	}

	if (index == -1) // Insert at tail
	{
		index = tail;
	}
	for (int i = tail - 1; i >= index; i--)
	{
		// shift element at data[i] to data[i+1]
		data[i + 1] = data[i];
	}
	data[index] = item;
	tail++;
}

template<typename TYPE>
void ArrayList<TYPE>::remove(int index)
{
	if (index < 0 || index >= tail)
	{
		// Throw an index out of bounds exception
		// FYI, stringstream is similar to both cin and cout. When used with <<,
		// information flows to the stringstream. When used with >>, information flows
		// from the stringstream. This allows me to convert an "int" to a string and
		// store it in the message, so I can grab the index number that was invalid
		stringstream sstream;
		sstream << "Index " << index << " is out of bounds";
		string msg;
		getline(sstream, msg);
		throw IndexOutOfBounds(msg);
	}

	for (int i = index; i < tail-1; i++)
	{
		data[i] = data[i + 1];
	}
	tail--;
}

template<typename TYPE>
TYPE ArrayList<TYPE>::at(int index)
{
	if (index < 0 || index >= tail)
	{
		// Throw an index out of bounds exception
		stringstream sstream;
		sstream << "Index " << index << " is out of bounds";
		string msg;
		getline(sstream, msg);
		throw IndexOutOfBounds(msg);
	}

	return data[index];
}

template<typename TYPE>
void ArrayList<TYPE>::sort(int(*cmp)(const TYPE& item1, const TYPE& item2), bool doQuicksort)
{
	bubbleSort<TYPE>(data, tail, cmp);
}

template<typename TYPE>
int ArrayList<TYPE>::search(TYPE item, int(*cmp)(const TYPE& item1, const TYPE& item2))
{
	for (int i = 0; i < tail; i++)
	{
		if (!cmp(item, data[i]))
		{
			return i;
		}
	}
	return -1;
}

template<typename TYPE>
int ArrayList<TYPE>::getSize()
{
	return tail;
}

template<typename TYPE>
void ArrayList<TYPE>::increaseArraySize()
{
	// Create a new array at 2x the original size
	TYPE* tmp = new TYPE[currentArraySize * 2];

	// Copy all the elements from the original array to the new one
	for (int i = 0; i < currentArraySize; i++)
	{
		tmp[i] = data[i];
	}

	// Delete the original array
	delete[] data;

	// Set the new array to be the "data" member
	data = tmp;

	// Set the currentArraySize to the new size
	currentArraySize *= 2;
}
