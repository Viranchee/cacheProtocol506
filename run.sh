#!/bin/bash

# Run the program
chmod +x *.sh simulate_cache*
# Arguments: Cache Size, Cache Associativity, Block Size, Number of Threads, Protocol
runAll() {
    echo "Cache Size: $1, CacheAssoc: $2, Block Size: $3"

    # sh module.sh project_name cache_size assoc block_size num_processors protocol trace_file number_of_references

    echo "MSI"
    date +"%T"
    sh module.sh smp $1 $2 $3 16 0 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated
    sleep 0.5
    mv result.txt ran/msi-Cache$1-Assoc$2-Block$3.txt
    echo "MOSI"
    date +"%T"
    sh module.sh smp $1 $2 $3 16 1 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated
    sleep 0.5
    mv result.txt ran/mosi-Cache$1-Assoc$2-Block$3.txt

    echo "Firefly"
    date +"%T"
    sh module.sh smp $1 $2 $3 16 2 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated
    sleep 0.5
    mv result.txt ran/firefly-Cache$1-Assoc$2-Block$3.txt

    echo "Dragon"
    date +"%T"
    sh module.sh smp $1 $2 $3 16 3 /afs/eos.ncsu.edu/lockers/workspace/csc/CSC506-1/trace/swaptions_truncated
    sleep 0.5
    mv result.txt ran/dragon-Cache$1-Assoc$2-Block$3.txt
}

# Block Size Default: 64
# Block Size: 32,64,128,256,512

# Associativity Default: 1
# Associativity: 1,2,4

# Cache Size Default: 256
# Caches: 128, 256, 512

varyCacheSize() {
    echo "Varying Cache Size"
    # Cache Size: 128kb 256kb 512kb
    runAll 128 1 64
    runAll 256 1 64
    runAll 512 1 64
}

varyAssociativity() {
    echo "Varying Associativity"
    # Associativity: 1way 2way 4way
    # runAll 256 1 64
    runAll 256 2 64
    runAll 256 4 64
}

varyBlockSize() {
    echo "Varying Block Size"
    # Block Size: 32 64 128 256
    # runAll 256 1 32
    # runAll 256 1 64
    runAll 256 1 128
    runAll 256 1 256
}

# varyCacheSize # Complete
# varyAssociativity
varyBlockSize
