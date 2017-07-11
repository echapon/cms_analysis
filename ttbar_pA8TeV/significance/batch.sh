#!/bin/bash

basedir=/afs/cern.ch/user/e/echapon/workspace/private/cms_analysis/ttbar_pA8TeV/significance
source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh; source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

workdir=/tmp/echapon/tmp_$SEED
mkdir -p $workdir
cd $workdir

echo SEED $SEED

cp $basedir/*C $basedir/*root .

echo "root -l -b -q computeSignif.C'(\"fit_finalworkspace_wmodel0_0_20170706.root\",'${SEED}')' 2>&1 | tail -n100 2>&1"
root -l -b -q computeSignif.C'("fit_finalworkspace_wmodel0_0_20170706.root",'${SEED}')' 2>&1 | tail -n100 2>&1
cp Freq* $basedir
