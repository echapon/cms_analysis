#!/bin/bash

for i in `seq 0 1000`; do 
   bsub -q 1nd -env "SEED=$i" batch.sh
done
