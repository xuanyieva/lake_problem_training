#!/bin/sh

SEEDS=$(seq 1 50)
for SEED in ${SEEDS}
do 
  FILENAME="output_${SEED}.txt"
  ./lake_4obj_borg.exe  ${SEED} >& ${FILENAME}
# ./lake_4obj_borg.exe  ${SEED} >>output.txt


done