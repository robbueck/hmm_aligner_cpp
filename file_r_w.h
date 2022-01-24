/*
 * file_r_w.h
 *
 *  Created on: Nov 7, 2019
 *      Author: rbuecki
 */

#ifndef FILE_R_W_H_
#define FILE_R_W_H_

#include "sequence_list.h"
#include "sequence_pair.h"


/* read sequences
 * **************
 * opens the file ../in_pairs.txt, reads the sequences and orders them in pairs.
 * takes an empty array of sequence pairs and fills it
 */

void read_file (sequence_list<sequence_pair>* const pair_list, char *file_name);



/* Write file with state paths
 * ***************************
 * takes a list with annotated sequence pairs, writes the annotation paths to the file ../paths_alignment_model.txt
 */

void write_path_file(sequence_list<sequence_pair>* sequences);



/* write file with alignments
 * **************************
 * takes a list with annotated sequence pairs, writes the alignment for each pair to the file ../predicted_alignments.txt
 */

void write_alignment_file(sequence_list<sequence_pair>* sequences);


#endif /* FILE_R_W_H_ */
