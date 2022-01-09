#ifndef PAIRING_PQ_H
#define PAIRING_PQ_H

#include "Eecs281PQ.h"
#include <algorithm>    // std::sort
#include <stack>          // std::stack
//A specialized version of the priority queue ADT implemented as a pairing heap.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
	//Description: Construct a priority queue out of an iterator range with an optional
	//             comparison functor.
	//Runtime: O(n) where n is number of elements in range.
	template<typename InputIterator>
	PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

	//Description: Construct an empty priority queue with an optional comparison functor.
	//Runtime: O(1)
	PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());

	//Description: Copy constructor.
	//Runtime: O(n)
	PairingPQ(const PairingPQ &other);

	//Description: Copy assignment operator.
	//Runtime: O(n)
	PairingPQ &operator=(const PairingPQ &rhs);

	//Description: Destructor
	//Runtime: O(n)
	~PairingPQ();

	//Description: Add a new element to the priority_queue. This has been provided for you,
	//             in that you should implement push functionality in the
	//             addNode function.
	//Runtime: Amortized O(1)
	virtual void push(const TYPE& val) { addNode(val); }

	//Description: Remove the most extreme (defined by 'compare') element from
	//             the priority queue.
	//Note: We will not run tests on your code that would require it to pop an
	//element when the priority queue is empty. Though you are welcome to if you are
	//familiar with them, you do not need to use exceptions in this project.
	//Runtime: Amortized O(log n)
	virtual void pop();

	//Description: Return the most extreme (defined by 'compare') element of
	//             the priority queue.
	//Runtime: O(1)
	virtual const TYPE &top() const;

	//Description: Get the number of elements in the priority queue.
	//Runtime: O(1)
	virtual std::size_t size() const {
		//TODO: Implement this function (done?)
		return howbigyourmomis; // TODO: Delete or change this line
	}

	//Description: Return true if the priority queue is empty.
	//Runtime: O(1)
	virtual bool empty() const {
		//TODO: Implement this function (done?)
		return (howbigyourmomis == 0); // TODO: Delete or change this line
	}

	//Description: Assumes that all elements in the priority queue are out of order.
	//             You must reorder the data so that the PQ invariant is restored.
	//Runtime: O(n)
	virtual void updatePriorities();

	// Each node within the pairing heap
	class Node {
	public:
		Node(const TYPE &val)
			: elt(val), sibling(nullptr), child(nullptr), prev(nullptr)
		{}
	public:
		//Description: Allows access to the element at that Node's position.
		//Runtime: O(1) - this has been provided for you.
		const TYPE &operator*() const { return elt; }
		const Node *sibling_ptr() const { return sibling; }
		const Node *child_ptr() const { return child; }
		const Node *prev_ptr() const { return prev; }

		//The following line allows you to access any private data members of this
		//Node class from within the PairingPQ class. (ie: myNode.elt is a legal
		//statement in PairingPQ's add_node() function).
		friend PairingPQ;
	private:
		TYPE elt;
		Node *sibling;
		Node *child;
		Node *prev;
	};

	//Description: Updates the priority of an element already in the priority_queue by
	//             replacing the element refered to by the Node with new_value.
	//             Must maintain priority_queue invariants.
	//
	//PRECONDITION: The new priority, given by 'new_value' must be more extreme
	//              (as defined by comp) than the old priority.
	//
	//Runtime: As discussed in reading material.
	void updateElt(Node* node, const TYPE &new_value);

	//Description: Add a new element to the priority_queue. Returns a Node* corresponding
	//             to the newly added element.
	//Runtime: Amortized O(1)
	Node* addNode(const TYPE& val);

	const Node *root_ptr() const { return root; }

private:
	Node *root;
	int howbigyourmomis;
	//TODO: Add any additional member functions or data you require here.
	//TODO: We recommend creating a 'meld' function (see the Pairing Heap papers).
	Node* meld(Node* tree1, Node* tree2) { // we gonna meld some muthfukaaaas
		if (tree1 == nullptr) {
			return tree2;
		}
		if (tree2 == nullptr) {
			return tree1;
		}
		if (this->compare(tree1->elt, tree2->elt)) {
			//If the tree1 root is less than tree 2 
			tree1->sibling = tree2->child;
			tree1->prev = tree2;
			if (tree1->sibling) {
				tree1->sibling->prev = tree1;
			}
			tree2->sibling = nullptr;
			tree2->child = tree1;
			return tree2;
		}
		else {
			tree2->sibling = tree1->child;
			tree2->prev = tree1;
			if (tree2->sibling) {
				tree2->sibling->prev = tree2;
			}
			tree1->sibling = nullptr;
			tree1->child = tree2;
			return tree1;
		}
	}



};


//Description: Construct a priority queue out of an iterator range with an optional
//             comparison functor.
//Runtime: O(n) where n is number of elements in range.
//TODO: when you implement this function, uncomment the parameter names
template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(
	InputIterator  start,
	InputIterator  end,
	COMP_FUNCTOR  comp
	) :root(nullptr), howbigyourmomis(0) { //(done?)
										   //TODO: Implement this function
	this->compare = comp;
	for (InputIterator i = start; i != end; ++i) {
		push(*i);

	}
}


//Description: Construct an empty priority queue with an optional comparison functor.
//Runtime: O(1)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(COMP_FUNCTOR  comp) :root(nullptr), howbigyourmomis(0) {
	//TODO: Implement this function
	this->compare = comp;
}


//Description: Copy constructor.
//Runtime: O(n)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(const PairingPQ &  other) :root(nullptr), howbigyourmomis(0) {

	*this = other;
}


//Description: Copy assignment operator.
//Runtime: O(n)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>&
PairingPQ<TYPE, COMP_FUNCTOR>::operator=(const PairingPQ &  rhs) {
	if (&rhs == this) {
		return *this;
	}
	this->compare = rhs.compare; //set comparison
	if (rhs.empty()
		&& empty()) {
		return *this;
	}
	if (rhs.empty() || !(empty())) {
		//lit just copied and pasted my destructor
		howbigyourmomis = 0;
		//if (!root) {
		//	return *this;
		//}
		std::stack<Node *> mydeque;
		mydeque.push(this->root);
		while (!mydeque.empty()) {
			Node*r = mydeque.top();
			mydeque.pop();
			if (r->sibling) {
				mydeque.push(r->sibling);

			}
			if (r->child) {
				mydeque.push(r->child);
			}
			delete r;
			//this->updateElt = 0; 
		}
		root = nullptr;

		//lit just copied and pasted my destructor
	}
	if (rhs.empty()) {
		root = nullptr;
		return *this;
	}

	std::stack<Node *> mymom;
	//root = nullptr;
	mymom.push(rhs.root);
	while (!mymom.empty()) {
		Node*r = mymom.top();
		mymom.pop();
		if (r->sibling) {
			mymom.push(r->sibling);
		}
		if (r->child) {
			mymom.push(r->child);
		}
		push(r->elt);
//		root = meld(root, r);
	}
	this->howbigyourmomis = rhs.howbigyourmomis;
	return *this;
}


//Description: Destructor
//Runtime: O(n)
template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::~PairingPQ() {
	//TODO: Implement this function (fuck me sideways and just all over kill me murder me)
	howbigyourmomis = 0;
	if (!root) {
		return;
	}
	std::stack<Node *> myleg;
	myleg.push(root);
	while (!myleg.empty()) {
		Node*r = myleg.top();
		myleg.pop();
		if (r->sibling) {
			myleg.push(r->sibling);

		}
		if (r->child) {
			myleg.push(r->child);
		}
		delete r;
	}
}

//Description: Remove the most extreme (defined by 'compare') element from
//             the priority queue.
//Note: We will not run tests on your code that would require it to pop an
//element when the priority queue is empty. Though you are welcome to if you are
//familiar with them, you do not need to use exceptions in this project.
//Runtime: Amortized O(log n)
template<typename TYPE, typename COMP_FUNCTOR>
void PairingPQ<TYPE, COMP_FUNCTOR>::pop() {
	--howbigyourmomis;
	std::vector<Node*> clintbae;
	Node * temp = root->child;
	delete root;
	while (temp && temp->sibling) {
		Node * pointertemp = temp->sibling->sibling;
		clintbae.push_back(meld(temp, temp->sibling));
		temp = pointertemp;
	}
	if (temp) {
		clintbae.push_back(meld(temp, temp->sibling));
	}
	root = nullptr;
	auto rit = clintbae.rbegin();
	for (; rit != clintbae.rend(); ++rit) {
		root = meld(root, *rit);
	}
	return;
}


//Description: Return the most extreme (defined by 'compare') element of
//             the priority queue.
//Runtime: O(1)
template<typename TYPE, typename COMP_FUNCTOR>
const TYPE &PairingPQ<TYPE, COMP_FUNCTOR>::top() const {
	//TODO: Implement this function
	return root->elt; //(done?)
}


//Description: Assumes that all elements in the priority queue are out of order.
//             You must reorder the data so that the PQ invariant is restored.
//Runtime: O(n log n)
template<typename TYPE, typename COMP_FUNCTOR>
void PairingPQ<TYPE, COMP_FUNCTOR>::updatePriorities() {
	//TODO: Implement this function
}


//Description: Updates the priority of an element already in the priority_queue by
//             replacing the element refered to by the Node with new_value.
//             Must maintain priority_queue invariants.
//
//PRECONDITION: The new priority, given by 'new_value' must be more extreme
//              (as defined by comp) than the old priority.
//
//Runtime: As discussed in reading material.
//TODO: when you implement this function, uncomment the parameter names
template<typename TYPE, typename COMP_FUNCTOR>
void PairingPQ<TYPE, COMP_FUNCTOR>::updateElt(Node *  node, const TYPE & new_value) {
	//TODO: Implement this function
	node->elt = new_value;
	if (node == root) {
		return; 
	}
	else {
		Node * temprev = node->prev; 
		if (temprev->sibling == node) {
			temprev->sibling = node->sibling;
			if (node->sibling) {
				node->sibling->prev = temprev; 
			}
		}
		if (temprev->child == node) {
			temprev-> child = node->sibling; 
			if (node->sibling) {
				node->sibling->prev = temprev;
			}
			
		}
		node->prev = nullptr;
		node->sibling = nullptr; 
		root=meld(node, root);
	}
}


//Description: Add a new element to the priority_queue. Returns a Node* corresponding
//             to the newly added element.
//Runtime: Amortized O(1)
//TODO: when you implement this function, uncomment the parameter name
template<typename TYPE, typename COMP_FUNCTOR>
typename PairingPQ<TYPE, COMP_FUNCTOR>::Node*
PairingPQ<TYPE, COMP_FUNCTOR>::addNode(const TYPE &  val) {
	//TODO: Implement this function (done?)
	Node * temp = new Node(val);
	root = meld(root, temp);
	++howbigyourmomis;
	return temp;
}


#endif //PAIRING_H
