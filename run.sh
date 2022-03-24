# Run with 0 errors MSI

# echo "Running MSI"
# sh module.sh smp 128000 1 64 16 0 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated 1000
# echo "COMPLETE MSI RUN"

make clean
make
echo "Running Dragon"
sh module.sh smp 128000 1 64 16 3 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated 1000
echo "COMPLETE Dragon RUN"

