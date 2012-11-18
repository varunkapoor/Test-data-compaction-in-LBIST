#!/bin/csh -f
#RUN ATPG FOR THE FIRST TIME,GENERATING PATTERN SET
source /sw/cshrc/linux64/lsf.cshrc
source /sw/cshrc/linux64/unicad_24kernel3.4.1
tmax -64 -tcl -shell firstrun.tcl
#CONVERT STIL FILE TO READABLE PATTERN FILE AND START LOOP#
new_stil_to_patterns ./PATTERNS/Patterns.serial.stil
set c = ` awk '{ } END { print NR } ' ip_file`
while ( $c > 31)
#SET FILE PARAMETERS ACCORDING TO PATTERN FILE GENERATED#
wc -l ip_file | awk '{printf "#define NP " $1} ' > file_parameters.h
head ip_file -n 1 | sed 's/./& /g' | wc -w | awk '{printf "\n#define PL " $1} ' >> file_parameters.h
#RUN PATTERN MERGING CODE AND DUMP THIRTY TWO PATTERNS#
g++ pattern_merging_code_cbl.cpp
a.out
#RANDOM FILL THE PATTERNS#
gcc random_fill.c
a.out
cat x_filled_patt >> ./PATTERNS/Final_patterns
#CONVERT PATTERN FILE TO STIL FILE FOR ATPG
new_merged_to_stil_linflex x_filled_patt
cp x_filled_patt.stil ./PATTERNS/x_filled_patt.stil
#RUN ATPG FAULT SIMULATION AND GENERATE NEW SET OF PATTERNS#
tmax -64 -tcl -shell fault_sim.tcl
new_stil_to_patterns ./PATTERNS/Patterns.serial_mod.stil
set c = ` awk '{ } END { print NR } ' ip_file`
end