/*
 * sequence_pair.cpp
 *
 *  Created on: Oct 16, 2019
 *      Author: rbuecki
 */

#include "sequence_pair.h"
#include <string>
#include <iostream>



// define constructors

sequence_pair::sequence_pair()
{
	seq_a = "X";		// two sequences are stored in seq_a and seq_b, the order is not important
	seq_b = "X";
	ali_prob = 0;		// the probability of the sequences under the alignment model
	rand_prob = 0;		// the probability of the sequences under the random model
	annotation = "X";
	pair_count++;		// update counter of sequences
}

sequence_pair::sequence_pair(const std::string a_seq, const std::string b_seq)
{
	seq_a = a_seq;		// two sequences are stored in seq_a and seq_b, the order is not important
	seq_b = b_seq;
	ali_prob = 0;		// the probability of the sequences under the alignment model
	rand_prob = 0;		// the probability of the sequences under the random model
	annotation = "X";
	pair_count--;
}

sequence_pair::sequence_pair(const sequence_pair &v)
{
	seq_a = v.seq_a;
	seq_b = v.seq_b;
	ali_prob = v.ali_prob;
	rand_prob = v.rand_prob;
	annotation = v.annotation;
}



sequence_pair::~sequence_pair() {}



// other functions


//void sequence_pair::count(void)
//	{
//		pair_count++;
//		return;
//	}

void sequence_pair::set_prob(const float prob, const char Ali_or_Rand)
{
	if (Ali_or_Rand == 'A')
	{
		ali_prob = prob;
	}
	else if (Ali_or_Rand == 'R')
	{
		rand_prob = prob;
	}
	else
	{
		std::cerr << "Invalid value for Ali_or_Rand in function get_prob in class sequence_pair\n";
		exit(8);
	}
	return;
}




void sequence_pair::annotate_alignment(const std::string state_path)
{
	annotation = state_path;
	return;
}


int sequence_pair::get_count(void)
{
	return(pair_count);
}


unsigned int sequence_pair::seq_len(const char A_or_B)
	{
		if (A_or_B == 'A')
		{
			return(seq_a.length());
		}
		else if (A_or_B == 'B')
		{
			return(seq_b.length());
		}
		else
		{
			std::cerr << "Invalid value for A_or_B in function seq_len in class sequence_pair\n";
			exit(8);
		}
		return(0);
	}


float sequence_pair::get_prob(const char Ali_or_Rand)
{
	if (Ali_or_Rand == 'A')
	{
		return(ali_prob);
	}
	else if (Ali_or_Rand == 'R')
	{
		return(rand_prob);
	}
	else
	{
		std::cerr << "Invalid value for Ali_or_Rand in function get_prob in class sequence_pair\n";
		exit(8);
	}
	return(0);
}


char sequence_pair::get_seq_char(const char A_or_B, const unsigned int pos)
{
	if ((0 > pos) | (seq_len(A_or_B) <= pos))
	{
		std::cerr << "Position out of range in get_seq_char in class sequence_pair\n";
		exit(8);
	}

	if (A_or_B == 'A')
	{
		return(seq_a.at(pos));
	}
	else if (A_or_B == 'B')
	{
		return(seq_b.at(pos));
	}
	else
	{
		std::cerr << "Invalid value for A_or_B in function get_seq_char in class sequence_pair\n";
		exit(8);
	}
}


std::string sequence_pair::get_annotation(void)
{
	return(annotation);
}



std::string sequence_pair::insert_gaps(const char A_or_B)
{
	int gap_state = -1;
	if (A_or_B == 'A')
	{
		gap_state = '3';
	}
	else if (A_or_B == 'B')
	{
		gap_state = '2';
	}
	else
	{
		std::cerr << "Invalid value for A_or_B in function insert_gaps\n";
		exit(8);
	}

	if (annotation == "X")
	{
		std::cerr << "Sequence is not annotated yet. run_viterbi has to be performed before\n";
	}

	std::string gap_sequence = "";														// sequence containing gaps
	int seq_pos = 0;																	// next position of the sequence to be written
	unsigned int gap_count = 0;															// count the amount of gaps inserted
	for (unsigned int ali_pos = 0; ali_pos < annotation.length(); ali_pos++)			// loop over all alignment positions
	{
		if (annotation.at(ali_pos) == gap_state)										// if state is emit character from other sequence, insert gap and continue
		{
			gap_sequence = gap_sequence + '-';
			gap_count++;
			continue;
		}
		else
		{
			gap_sequence = gap_sequence + get_seq_char(A_or_B, seq_pos);				// if state is match or emit character from sequence, insert character from sequence and continue on sequence
			seq_pos++;
		}
	}

	// check if annotation was long enough
	if (seq_len(A_or_B) != (annotation.length() - gap_count))
	{
		std::cerr << "Sequence with gaps is not of equal length as annotation in function insert_gaps\n";
		exit(8);
	}

	return(gap_sequence);
}



// operators
sequence_pair& sequence_pair::operator = (const sequence_pair &pair)
{
	if (this != &pair)
	{
		seq_a = pair.seq_a;
		seq_b = pair.seq_b;
		ali_prob = pair.ali_prob;
		rand_prob = pair.rand_prob;
		annotation = pair.annotation;
	}
	return(*this);
}
