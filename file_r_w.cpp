/*
 * file_r_w.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: rbuecki
 */

#include "file_r_w.h"
#include "sequence_pair.h"
#include "sequence_list.h"
#include <iostream>
#include <fstream>



void read_file (sequence_list<sequence_pair>* const pair_list, char *file_name)
{
	//open file and read lines
	std::ifstream input_file(file_name);
	if (input_file.fail()) {
		std::cerr << "Unable to open " << file_name << "\n";
		exit(8);
	}
	std::string sequence_from_file;								// a sequence from file
	std::string first_seq = "X";								// two new sequences to be read from file and stored in a sequence pair
	std::string second_seq = "X";
	while (std::getline(input_file, sequence_from_file)) 		// read all lines to all_lines, count all lines and close file

	{
		if (first_seq  == "X")									// first sequence is not defined, sequence is the first of a pair
		{
			if (second_seq != "X")
			{
				std::cerr << "Second sequence not empty, but first one is in function read_file.\n";
				exit(8);
			}
			first_seq = sequence_from_file;
		}
		else if (second_seq == "X")													// first sequence is defined and second sequence not, sequence it the second of a pair, save pair and continue with next pair
		{
			second_seq = sequence_from_file;
			sequence_pair new_pair(first_seq, second_seq);
			pair_list->add_list(new_pair);											// add new sequence pair to list
//			new_pair.count();														// update count of pairs
			first_seq = "X";														// reset first and second sequence
			second_seq = "X";
		}
	}
	input_file.close();

	if (first_seq != "X")									// check if number of sequences in file is even, exit, if not
	{
		std::cerr << "Odd number of sequences in file\n";
		exit(8);
	}
	return;
}





void write_path_file(sequence_list<sequence_pair>* sequences)
{
    std::ofstream out_file("paths_alignment_model.txt", std::ios::out); // open and clear the output file
    sequence_list_element<sequence_pair>* seqs_to_write = sequences->next_element();
    while (seqs_to_write != NULL)
    {
    	out_file << seqs_to_write->data.get_annotation() << std::endl;
    	seqs_to_write = sequences->next_element();
    }
    return;
}



void write_alignment_file(sequence_list<sequence_pair>* sequences)
{
    std::ofstream out_file("predicted_alignments.txt", std::ios::out); // open and clear the output file
    sequence_list_element<sequence_pair>* seqs_to_write = sequences->next_element();
    while (seqs_to_write != NULL)
    {
        out_file << seqs_to_write->data.insert_gaps('A') << "\n" << seqs_to_write->data.insert_gaps('B') << '\n';
    	seqs_to_write = sequences->next_element();
    }
    return;
}


