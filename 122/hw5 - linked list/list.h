#pragma once

template <typename TYPE>
class List
{
public:
	/**
	* Method to insert item at the given index
	*/
	virtual void insert(TYPE item, int index=0)=0;

	/**
	* Method to remove an item at the given index
	*/
	virtual void remove(int index) = 0;

	/**
	* Method to retrieve an item at the given index
	*/
	virtual TYPE at(int index) = 0;

	/**
	* Method to sort the data in the List. Takes a pointer to a comparison function
	* 
	* The comparison function takes 2 TYPEs as parameters. It returns a -1 if the first item is "less than" the second, a 0 if they are 
	* "equal", and a 1 if the second item is "less than" the first.
	*/
	virtual void sort(int(*cmp)(const TYPE& item1,const TYPE& item2), bool doQuicksort) = 0;

	/**
	* Method to search for a given item. Takes an ITEM as a parameter and a comparison function. Returns the index of the item if found
	*
	* Utilizes a compare function similar to the sort method.
	*/
	virtual int search(TYPE item, int(*cmp)(const TYPE& item1, const TYPE& item2)) = 0;

	/**
	* Method to get the size of the List
	*/
	virtual int getSize() = 0;
};

