/*
 * sequence_pair.h
 *
 *  Created on: Oct 16, 2019
 *      Author: rbuecki
 */

#ifndef SEQUENCE_PAIR_H_
#define SEQUENCE_PAIR_H_
#include <string>


class sequence_pair
{
	private:
		static int pair_count;	// holds the number of sequence pairs generated
		std::string seq_a;		// two sequences are stored in seq_a and seq_b, the order is not important
		std::string seq_b;
		float ali_prob;			// the probability of the sequences under the alignment model
		float rand_prob;		// the probability of the sequences under the random model
		std::string annotation;	// annotation of the sequence alignment


	public:
		// constructors and deconstructors:
		sequence_pair();
		sequence_pair(const std::string a_seq, const std::string b_seq);
		sequence_pair(const sequence_pair &v);
		~sequence_pair();

		// functions
		// change values
//		void count(void);													// count sequence pairs
		void set_prob(const float prob, const char Ali_or_Rand);			// set probabilities for alignment (A) or random model (R)
		void annotate_alignment(const std::string state_path);				// set annotation of the sequence alignment
		// return values
		static int get_count(void);											// returns pair_count
		unsigned int seq_len(const char A_or_B);							// returns length of seq_a or seq_b
		float get_prob(const char Ali_or_Rand);								// return probabilities for alignment (A) or random (R) model
		char get_seq_char(const char A_or_B, const unsigned int pos);		// returns character of sequence a or b at postition pos
		std::string get_annotation(void);									// returns annotation path
		std::string insert_gaps(const char A_or_B);							// returns sequence a or b including gaps for the alignment

		// operators
		sequence_pair& operator = (const sequence_pair &pair);

};

#endif /* SEQUENCE_PAIR_H_ */
