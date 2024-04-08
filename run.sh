for (( p=1; p<=16; p*=2 ))
do
  for (( n_scale=40; n_scale<=320; n_scale*=2))
    do
      command="mpirun -np $p ./cmake-build-debug/MPI_Evaluate $n_scale"
      $command
    done
done