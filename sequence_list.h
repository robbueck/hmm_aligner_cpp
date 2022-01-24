/*
 * sequence_list.h
 *
 *  Created on: Nov 4, 2019
 *      Author: rbuecki
 */

#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_
#include <string>


template<class T>
class sequence_list_element
{
	private:
		sequence_list_element *next_ptr;					// forward link to next element in list
	public:
		T data;												// holds the data, a sequence pair
		// constructor and destructor
		sequence_list_element<T>();
		~sequence_list_element<T>();
	template<class kind>
	friend class sequence_list;
};

template<class kind>
class sequence_list
{
	private:
		sequence_list_element<kind> *first_ptr;				// point to the first and last element of the list
		sequence_list_element<kind> *last_ptr;
		sequence_list_element<kind> *current_ptr;			// points to the current element to loop through the list
	public:
		// constructor and destructor
		sequence_list<kind>();
		~sequence_list<kind>();
		// other functions
		void add_list(const kind item);						// adds element to the end of the list
		sequence_list_element<kind>* next_element();		// returns current pointer and moves it one step further, to loop through list from the start
		void reset_current_ptr();							// resets current pointer to first pointer, to loop through the list from the start

};




/* defining functions
 * ******************
 */


/* constructor and destructor for sequence_list_element
 * ****************************************************
 */

template<class T>
sequence_list_element<T>::sequence_list_element() {next_ptr = NULL;}		// new_seqeunce_list_element gets appended to end of list => next_ptr has to be NULL

template<class T>
sequence_list_element<T>::~sequence_list_element() {}


/* functions for sequence_list
 * ***************************
 */

template<class kind>
sequence_list<kind>::sequence_list()										// without any data, all pointers should be NULL
{
	first_ptr = NULL;
	last_ptr = NULL;
	current_ptr = NULL;
}


template<class kind>
sequence_list<kind>::~sequence_list()
{
	sequence_list_element<kind> *delete_ptr;
	delete last_ptr;
	delete current_ptr;
	last_ptr = NULL;
	current_ptr = NULL;
	while(first_ptr != NULL)
	{
		delete_ptr = first_ptr->next_ptr;
		delete first_ptr;
		first_ptr = NULL;
		first_ptr = delete_ptr;
	}
}


template<class kind>
void sequence_list<kind>::add_list(const kind item)
{

	sequence_list_element<kind> *new_ptr;
	new_ptr = new sequence_list_element<kind>;
	new_ptr->data = item;

	if (first_ptr == NULL)						// if first_ptr == NULL, this is the first element in the list, else dont change first_ptr
	{
		first_ptr = new_ptr;
		last_ptr = new_ptr;
		last_ptr->next_ptr = NULL;				// last element has no next pointer
	}
	else
	{
		last_ptr->next_ptr = new_ptr;			// set pointer of the old last element to the new last element
		last_ptr = new_ptr;						// new element is last in list.
		last_ptr->next_ptr = NULL;				// last element has no next pointer

	}
	return;
}


template<class kind>
sequence_list_element<kind>* sequence_list<kind>::next_element()
{
	sequence_list_element<kind> *return_ptr = NULL;
	if (current_ptr != NULL)
	{
		return_ptr = current_ptr;
		current_ptr = current_ptr->next_ptr;
	}
	return(return_ptr);
}


template<class kind>
void sequence_list<kind>::reset_current_ptr() {current_ptr = first_ptr;}


#endif /* SEQUENCE_LIST_H_ */
