#pragma once
#include <ostream>

using std::ostream;

template <typename TYPE>
class ADTStack {
public:
    /**
     * Pushes the item on to the top of the stack.
     * @param item The item to insert into the stack.
     */
    virtual void push(TYPE item) = 0;

    /**
     * Removes the top item from the stack.
     */
    virtual void pop() = 0;

    /**
     * Returns the top item stored on the stack.
     * @return item currently at the top of the stack.
     */
    virtual TYPE peek() = 0;

    /**
     * Returns the number of items currently stored in the stack.
     * @return int total number of items in the stack.
     */
    virtual int size() = 0;

    /**
     * Function to print the contents of the stack. The stack should be printed with
     * a | at the bottom, and a comma separated list of each element (all on one line).
     * For example, if my stack had the values 5, 4, 3, 2, 1 (with 1 at the top), then
     * the output would be:
     * | 5, 4, 3, 2, 1
     *
     * @param stream The stream to write to (This will be used similar to cout)
     */
    virtual void printStack(ostream& stream) = 0;
};