#!/bin/zsh

echo "VertexNum,Position,CNFSAT,CNFSAT_Time,CNFSAT_Ratio,APPROX_V1,APPROX_V1_Time,APPROX_V1_Ratio,APPROX_V2,APPROX_V2_Time,APPROX_V2_Ratio" > data.csv

mkdir -p Analysis

THREADS=16
parallel --bar --gnu -j$THREADS --header : \
       '
  #Run Vertex Cover Solver
  mkdir -p Analysis/{VertexNum}-{Position}
  pushd Analysis/{VertexNum}-{Position}
  $VCSOLVER/graphGen {VertexNum} | $VCSOLVER/prjece650 > output.txt

  #extract values
  CNFSAT=`cat output.txt | grep "CNF-SAT-VC:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1 |  tr "," " " | wc -w`
  CNFSAT_Time=`cat output.txt | grep "CNF_SAT time is:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1`
  CNFSAT_Ratio='0'
  APPROX_V1=`cat output.txt | grep "APPROX-VC-1:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1 |  tr "," " " | wc -w`
  APPROX_V1_Time=`cat output.txt | grep "APPROX_V1 time is:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1`
  APPROX_V1_Ratio='0'
  APPROX_V2=`cat output.txt | grep "APPROX-VC-2:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1 |  tr "," " " | wc -w`
  APPROX_V2_Time=`cat output.txt | grep "APPROX_V2 time is:" | cut -d":" -f 2 | sed "s/^ //g" | cut -d" " -f 1 | tail -n 1`
  APPROX_V2_Ratio='0'

  popd

  #Dump results in .csv file
  sem --id mystr echo {VertexNum},{Position},$CNFSAT,$CNFSAT_Time,$CNFSAT_Ratio,$APPROX_V1,$APPROX_V1_Time,$APPROX_V1_Ratio,$APPROX_V2,$APPROX_V2_Time,$APPROX_V2_Ratio >> data.csv | cat'\
  ::: VertexNum 5 10 15 \
  ::: Position 1 2 3 4 5 6 7 8 9 10 \
  
