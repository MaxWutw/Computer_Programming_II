#!/bin/sh

make
read -p "Which test case you need(default=1): " test;
if [ -z "$test" ];then
    test=1
fi
dir="../2024_NTNU_ComputerProgramming-II_TestCase/HW01/"


read -p "Enter your test case amount(default=10): " cases;
if [ -z "$cases" ];then
    cases=10;
fi
cases=$((cases-1))
for i in $(seq 0 $cases)
do
    ./hw010$test < $dir/0$test/darrin/"in"/hw010$test\_0$i.in > output$i.out
    diff -uN $dir/0$test/darrin/"out"/hw010$test\_0$i.out output$i.out > pat$i.patch
    # diff -uN output$i.out output_$i.out > pat$i.patch
done

make clean
