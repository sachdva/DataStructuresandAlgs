#ifndef BINARY_H
#define BINARY_H

#include "Eecs281PQ.h"

//#include <algorithm>    // std::sort
//A specialized version of the priority queue ADT implemented as a binary heap.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
    //Description: Construct a priority queue out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
        BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Construct an empty priority queue with an optional comparison functor.
    //Runtime: O(1)
    BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());

    //Description: Add a new element to the priority queue.
    //Runtime: O(log n)
    virtual void push(const TYPE& val);

    //Description: Remove the most extreme (defined by 'compare') element from
    //             the priority queue.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the priority queue is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: O(log n)
    virtual void pop();

    //Description: Return the most extreme (defined by 'compare') element of
    //             the priority queue.
    //Runtime: O(1)
    virtual const TYPE& top() const;

    //Description: Get the number of elements in the priority queue.
    //Runtime: O(1)
	virtual std::size_t size() const {
			return data.size();
	}

    //Description: Return true if the priority queue is empty.
    //Runtime: O(1)
    virtual bool empty() const {
		return data.empty();
    }

    //Description: Assumes that all elements in the priority queue are out of order.
    //             You must reorder the data so that the PQ invariant is restored.
    //Runtime: O(n)
    virtual void updatePriorities();

private:
    //Note: This vector *must* be used your priority queue implementation.
    std::vector<TYPE> data;
private:
    //TODO: Add any additional member functions or data you require here.
	void fixUp(int k) {
		while (k > 1 && (this->compare(data[k / 2 -1], data[k-1]))) {
			std::swap(data[k-1], data[k / 2 - 1]);
			k /= 2; // move up
		}
	}


	void fixDown(int k) {
		int heapsize = int(data.size());
		while (2 * k <= heapsize) {
			int j = 2 * k; // start with left child
			//if (j >= heapsize) {
			//	return; 
			//}
			if (j < heapsize && (this->compare(data[j-1], data[j]) )) {
				++j;
			}
			if ((this->compare(data[j-1], data[k-1]))) {
				break; // heap restored
			}
			std::swap(data[j-1], data[k-1]);
			k = j; // move down
		}
	}
};


//Description: Construct a priority queue out of an iterator range with an optional
//             comparison functor.
//Runtime: O(n) where n is number of elements in range.
//TODO: when you implement this function, uncomment the parameter names
template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp)
	: data(start, end)
{
	this->compare = comp; 
	//data.insert(data.begin(), *start); 
	updatePriorities(); 
    //TODO: Implement this function
	//done? 
}


//Description: Construct an empty priority queue with an optional comparison functor.
//Runtime: O(1)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(COMP_FUNCTOR comp ) {
	this->compare = comp;
}


//Description: Add a new element to the priority queue.
//Runtime: O(log n)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::push(const TYPE &  val ) {
	//if (data.size() == 0) {
	//	data.push_back(val);
	//	data.push_back(val);
	//}
	//else {
	//	data.push_back(val);
	//}
	data.push_back(val);
	fixUp(int(data.size())); 
    //TODO: Implement this function
	//done?
}


//Description: Remove the most extreme (defined by 'compare') element from
//             the priority queue.
//Note: We will not run tests on your code that would require it to pop an
//element when the priority queue is empty. Though you are welcome to if you are
//familiar with them, you do not need to use exceptions in this project.
//Runtime: O(log n)
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::pop() {
	//std::swap(data.back(), data[0]); 
	data.front() = data.back();
	data.pop_back(); 
	fixDown(1);
	//you have to fix down here
    //TODO: Implement this function
	//done?
}


//Description: Return the most extreme (defined by 'compare') element of
//             the priority queue.
//Runtime: O(1)
template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& BinaryPQ<TYPE, COMP_FUNCTOR>::top() const {
    //TODO: Implement this function
	//done?
    return data[0];     
}


//Description: Assumes that all elements in the priority queue are out of order.
//             You must reorder the data so that the PQ invariant is restored.
//Runtime: O(n)
template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::updatePriorities() {
	//TODO: Implement this function
	int k = int(data.size()) -1;
	int r = k / 2;
	while (r != 0) {
		fixDown(r);
		--r;
	}
}


#endif //BINARY_H
