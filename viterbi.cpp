/*
 * viterbi.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: rbuecki
 */
#include "viterbi.h"
#include "sequence_pair.h"
#include "sequence_list.h"
#include <iostream>
#include <string>
//#include "multi_array.h"


// contain transition probabilities from state row to state column
float transition_probabilities[5][5] = {
		{0.0, 0.333, 0.333, 0.333, 0},
		{0.0, 0.7, 0.1, 0.1, 0.1},
		{0.0, 0.25, 0.65, 0.0, 0.1},
		{0.0, 0.25, 0.0, 0.65, 0.1},
		{0.0, 0.0, 0.0, 0.0, 0.0}
};





std::pair<float, int> find_max_value(const float v_matrix[5], const int state)
{
	// check if arguments are in range
	if ((state < 0) | (state > 4))
	{
		std::cerr <<"state out of range in function find_max_value\n";
		exit(8);
	}

    float max_prob = v_matrix[0] * transition_probabilities[0][state];					// start with first previous state, the start state
    int max_pointer(0);
    for (int k = 1; k < 4; k++) {														// loop through all other previous states
        float new_prob = v_matrix[k] * transition_probabilities[k][state];
        if (((new_prob == max_prob) & (new_prob > 0)) & verbose)						// give a warning, if multiple state paths have the same probability
        {
            std::cout << "More than one most likely paths for state " << state;
            std::cout << " pointing to " << max_pointer << " and " << k << " with probs: " << new_prob << max_prob << '\n';
        }
        if (new_prob > max_prob) { 														// check if any other states can generate a higher probability and update max_prob and max_pointer, if so
            max_prob = new_prob;
            max_pointer = k;
        }
    }
    return std::make_pair(max_prob, max_pointer);
}




void initializing (float v_matrix[20][20][5], int p_matrix[20][20][5], const int x_len, const int y_len)
{
	if (verbose) {std::cout << "Initializing\n";}
	float *v_matrix_ptr;					// matrix pointer to loop through the matrix
	for (v_matrix_ptr = &v_matrix[0][0][0]; v_matrix_ptr <= &v_matrix[x_len][y_len][4]; v_matrix_ptr++)
	{
		*v_matrix_ptr = 0;
	}
	int *p_matrix_ptr;
	for (p_matrix_ptr = &p_matrix[0][0][0]; p_matrix_ptr <= &p_matrix[x_len][y_len][4]; p_matrix_ptr++)
	{
		*p_matrix_ptr = -1;
	}
	v_matrix[0][0][0] = 1;
	return;
}




void recursion(float v_matrix[20][20][5], int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs)
{
	if (verbose) {std::cout << "Recursion\n";}
	std::pair<float, int> max_pointer_prob (0.0, -1);						// pair to hold the probability and the pointer for the state path with the highest probability leading to a given state at given sequence positions
	float emission_prob(0.0);												// emission probability depends on state and emitted characters
	for (unsigned int a = 0; a <= seqs->data.seq_len('A'); a++)				// loop over first sequence

	{
		for (unsigned int b = 0; b <= seqs->data.seq_len('B'); b++)			// loop over second sequence
		{
			if (a + b != 0)													// do not recalculate element in matrix[0][0], at this position all paths need to start in the start state, otherwise gap to gap alignment would occur at the start
			{
				// calculate matrix elements for each state that is not the start or the end state
				if ((a != 0) & (b != 0))									// state 1 is a match state, so ate least one character has to be read from each sequence
				{
					// calculate matrix element, if state is a match state
					max_pointer_prob = find_max_value(v_matrix[a-1][b-1], 1);
					if (seqs->data.get_seq_char('A', a-1) == seqs->data.get_seq_char('B', b-1))		// set emission probability during match state, when sequence characters match. .at() is zero based, loop counts 1 based
					{
						emission_prob = 4.0/28.0;
					}
					else
					{
						emission_prob = 1.0/28.0;													// set emission probability during match state, when sequence characters dont match
					}
					v_matrix[a][b][1] = emission_prob * max_pointer_prob.first;
					p_matrix[a][b][1] = max_pointer_prob.second;
				}


				// calculate matrix element for emit a, align character from sequence a with gap in sequence b
				emission_prob = 0.25; 							// emission probability is 0.25 for aligning one character with a gap
				if (a != 0)										// to emit a, a has to be at least 1
				{
					max_pointer_prob = find_max_value(v_matrix[a-1][b], 2);
					v_matrix[a][b][2] = emission_prob * max_pointer_prob.first;
					p_matrix[a][b][2] = max_pointer_prob.second;
				}


				//calculate matrix element for emit b, align character from sequence b with a gap in sequence a, as done above, emission probability stays the same
				if (b != 0) 									// to emit b, b has to be at least 1
				{
					max_pointer_prob = find_max_value(v_matrix[a][b-1], 3);
					v_matrix[a][b][3] = emission_prob * max_pointer_prob.first;
					p_matrix[a][b][3] = max_pointer_prob.second;
				}
			}
		}
	}
	return;
}




void termination(float v_matrix[20][20][5], int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs)
{
	if (verbose) {std::cout << "Termination\n";}
	std::pair<float, int> max_pointer_prob = find_max_value(v_matrix[seqs->data.seq_len('A')][seqs->data.seq_len('B')], 4);	// get a pair with the probability of the viterbi path and the first pointer to it
	v_matrix[seqs->data.seq_len('A')][seqs->data.seq_len('B')][4] = max_pointer_prob.first;
	p_matrix[seqs->data.seq_len('A')][seqs->data.seq_len('B')][4] = max_pointer_prob.second;
	return;
}




void backtracking(int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs)
{
	if (verbose) {std::cout << "Backtracking\n";}
	int a = seqs->data.seq_len('A');										// sequence positions in each sequence to move along
	int b = seqs->data.seq_len('B');

	// initialisation of backtracking, first step is from silent state to an emit state => dont move along any sequence position
    int backtrack_pointer = p_matrix[a][b][4]; 								// initial backtrack pointer at end state
    int new_pointer(-1);
	std::string path(""); 													//state path to be generated, ends at the backtrack pointer at the end state


    while ( backtrack_pointer != 0)											// move along the sequences, stop, when start state is reached
    {
    	if ((backtrack_pointer < 0) | (backtrack_pointer > 3))
    	{
    		std::cerr << "Backtrack pointer out of range in function backtracking\n";
    		exit(8);
    	}

		path = std::to_string(backtrack_pointer) + path;		// add pointer to state path
		new_pointer = p_matrix[a][b][backtrack_pointer];		// check pointer to previous state

		if (backtrack_pointer == 1)								// if state is a match, go one step back on both sequences
    	{
			a--;
			b--;
    	}
    	else if (backtrack_pointer == 2)						// if state is emit a or b, go one step back in the corresponding sequence
		{
    		a--;
		}
    	else if (backtrack_pointer == 3)
    	{
    		b--;
    	}
		backtrack_pointer = new_pointer;						// update pointer

    }
    seqs->data.annotate_alignment(path);
    return;
}




void run_viterbi(sequence_list_element<sequence_pair>* const seqs)
{

	float viterbi_matrix[20][20][5];							// viterbi matrix to hold the probabilities of most likely state paths
	int pointer_matrix[20][20][5];								// pointer matrix to hold the pointers for the most likely state paths
	initializing(viterbi_matrix, pointer_matrix, seqs->data.seq_len('A'), seqs->data.seq_len('B'));
	recursion(viterbi_matrix, pointer_matrix, seqs);
	termination(viterbi_matrix, pointer_matrix, seqs);
	backtracking(pointer_matrix, seqs);
	return;
}
