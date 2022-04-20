#!/bin/bash

count=0

# lower bound 100, upper bound 300
make clean
make
while [ $count -lt 1 ]
do
    low="$count"
    up="`expr $count + 10`"
    /home/vagrant/NVC/pin-2.14-71313-gcc.4.4.7-linux/intel64/bin/pinbin -p32 /home/vagrant/NVC/pin-2.14-71313-gcc.4.4.7-linux/ia32/bin/pinbin -t obj-intel64//dcache.so -_lb "$count" -_ub `expr $count + 10` -- /home/vagrant/NVC/Benchmarks/CrashTests/NPB3.3-OMP-C/bin/lh.A.x 2 200
    count=`expr $count + 10`
done
