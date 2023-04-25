#!/bin/bash

# default
# time ./main --uniform 1 --algorithm binary; \
# time ./main --uniform 0 --algorithm binary; \
# time ./main --uniform 1 --algorithm real; \
# time ./main --uniform 0 --algorithm real; \

# default optimal solution (large scale)
time ./main --uniform 1 --algorithm binary --pc 1 --p_select 500 --p_size 3800 --trial 1 --term 7000; \
# time ./main --uniform 0 --algorithm binary --pc 1 --p_select 500 --p_size 3800 --trial 1 --term 7000; \
time ./main --uniform 1 --algorithm real --pc 1 --p_select 500 --p_size 3800 --trial 1 --term 7000; \
# time ./main --uniform 0 --algorithm real --pc 1 --p_select 500 --p_size 3800 --trial 1 --term 7000; \

# n-point
# for p in $(seq 2 1 9); do \
#     time ./main --n_point $p --uniform 0 --algorithm binary; 
# done
# cross_prob
# for p in $(seq 0.1 0.3 1); do \
#     time ./main --pc $p --uniform 1 --algorithm binary; \
#     time ./main --pc $p --uniform 0 --algorithm binary; \
#     time ./main --pc $p --uniform 1 --algorithm real; \
#     time ./main --pc $p --uniform 0 --algorithm real; \
# done

# mut_prob
# for p in $(seq 0.1 0.3 1); do \
#     time ./main --pm $p --uniform 1 --algorithm binary; \
#     time ./main --pm $p --uniform 0 --algorithm binary; \
#     time ./main --pm $p --uniform 1 --algorithm real; \
#     time ./main --pm $p --uniform 0 --algorithm real; \
# done

# parent selection (tournament n)
# for p in $(seq 2 24 100); do \
#     time ./main --p_select $p --uniform 1 --algorithm binary; \
#     time ./main --p_select $p --uniform 0 --algorithm binary; \
#     time ./main --p_select $p --uniform 1 --algorithm real; \
#     time ./main --p_select $p --uniform 0 --algorithm real; \
# done

# population size
# for p in $(seq 100 300 1000); do \
#     time ./main --p_size $p --uniform 1 --algorithm binary; \
#     time ./main --p_size $p --uniform 0 --algorithm binary; \
#     time ./main --p_size $p --uniform 1 --algorithm real; \
#     time ./main --p_size $p --uniform 0 --algorithm real; \
# done

# termination
# for p in $(seq 500 300 1100); do \
#     time ./main --term $p --uniform 1 --algorithm binary; \
#     time ./main --term $p --uniform 0 --algorithm binary; \
#     time ./main --term $p --uniform 1 --algorithm real; \
#     time ./main --term $p --uniform 0 --algorithm real; \
# done	
