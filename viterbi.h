/*
 * viterbi.h
 *
 *  Created on: Nov 7, 2019
 *      Author: rbuecki
 */

#include <string>
#include "sequence_pair.h"
#include "sequence_list.h"


#ifndef VITERBI_H_
#define VITERBI_H_
extern bool verbose;

// contain transition probabilities from state row to state column
extern float transition_probabilities[5][5];

/* maximisation
 * ************
 * maximizes the viterbi element at a given position and gives the previous state leading to this maximum and its value.
 *
 */

std::pair<float, int> find_max_value(const float v_matrix[5], const int state);


/* Initializing
 * ************
 * initializes the viterbi and pointer matrix by setting 0 all viterbi and -1 all pointer matrix elements
 * takes the viterbi and pointer matrix as input and modifies them. additionally the length of both sequences are required
 */
void initializing (float v_matrix[20][20][5], int p_matrix[20][20][5], const int x_len, const int y_len);


/* Recursion
 * *********
 * performs the recursion to calculate the values of the viterbi matrix and the pointer matrix, takes an initialized viterbi matrix and pointer matrix and fills in all values for all sequence positions and states
 * additionally requires a sequence pair
 */
void recursion(float v_matrix[20][20][5], int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs);


/* Termination
 * ***********
 * after reading all symbols from the input sequences, find the path with the highest probability to the end state.
 * takes a viterbi and pointer matrix and a sequence pair. pointer to the state path with highest probability and the probability are stored by this function in element [len_a][len_b][4] of both matrices.
 */
void termination(float v_matrix[20][20][5], int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs);


/* Backtracking
 * ************
 * trace back the viterbi path through the pointer matrix
 * takes as input the poiner matrix and the sequence pair and adds the state path to the sequence pair
 */
void backtracking(int p_matrix[20][20][5], sequence_list_element<sequence_pair>* const seqs);


/* run viterbi
 * ***********
 * performs the viterbi algorithm for a sequence pair
 * takes a sequence pair and calculates its annotation
 */

void run_viterbi(sequence_list_element<sequence_pair>* const seqs);


#endif /* VITERBI_H_ */
