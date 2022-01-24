/*
 * alignment_model.cpp
 *
 *  Created on: Oct 7, 2019
 *      Author: rbuecki
 *
 *  alignment_model reads sequence pairs from a file ../in_pairs.txt and calculates the alignment with the highest probability
 *  Alignments are written to ../predicted_alignments.txt
 *  For each alignment, the optimal state path is written to ../paths_alignment_model.txt
 *
 */


#include <iostream>
#include "sequence_pair.h"
#include "sequence_list.h"
#include "viterbi.h"
#include "file_r_w.h"
#include "main.h"

void usage()
{
	std::cerr << "Usage: " << program_name << " [options] \n";
	std::cerr << "Options\n";
	std::cerr << "	-v		verbose\n";
	std::cerr << "	-f		input file name\n";
	exit(8);
}

int main(int argc, char *argv[])
{
	program_name = argv[0];

	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
		case 'v':
			verbose = true;			// turn on verbose mode
			break;
		case 'f':
			in_file = &argv[1][3];
			break;
		default:
			std::cerr << "Bad option " << argv[1] << '\n';
			usage();
		}
		--argc;
		++argv;
	}
	sequence_list<sequence_pair> all_pairs;									// list to be filled with all sequence pairs

	// read file
	read_file(&all_pairs, in_file);
	std::cout << "Analyzing " << sequence_pair::get_count() << " sequence pairs present in the file\n";

	// reset list to the beginning
	all_pairs.reset_current_ptr();

    // loop over all sequence pairs
    sequence_list_element<sequence_pair>* seqs_to_loop = all_pairs.next_element();		// retrieve first element from list and start looping through
	while (seqs_to_loop != NULL)
	{
		run_viterbi(seqs_to_loop);
		seqs_to_loop = all_pairs.next_element();
	}


	std::cout << "Finished analyzing all sequence pairs\nWriting data to file\n";

	// reset list to the beginning
	all_pairs.reset_current_ptr();


    // Write state paths to file
	write_path_file(&all_pairs);

	// reset list to the beginning
	all_pairs.reset_current_ptr();

    // Write alignment to file
    write_alignment_file(&all_pairs);

	std::cout << "Finished\n";

	return(0);
}
