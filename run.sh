#!/bin/bash

time ./main --uniform 1 --algorithm binary; \
time ./main --uniform 0 --algorithm binary; \
time ./main --uniform 1 --algorithm real; \
time ./main --uniform 0 --algorithm real; \

# for p in $(seq 0.1 0.3 1); do \
#     time ./main --cross_prob $p --uniform 1 --algorithm binary; \
#     time ./main --cross_prob $p --uniform 0 --algorithm binary; \
#     time ./main --cross_prob $p --uniform 1 --algorithm real; \
#     time ./main --cross_prob $p --uniform 0 --algorithm real; \
# done

# for p in $(seq 0.1 0.3 1); do \
#     time ./main --mut_prob $p --uniform 1 --algorithm binary; \
#     time ./main --mut_prob $p --uniform 0 --algorithm binary; \
#     time ./main --mut_prob $p --uniform 1 --algorithm real; \
#     time ./main --mut_prob $p --uniform 0 --algorithm real; \
# done

# for p in $(seq 2 24 100); do \
#     time ./main --p_select $p --uniform 1 --algorithm binary; \
#     time ./main --p_select $p --uniform 0 --algorithm binary; \
#     time ./main --p_select $p --uniform 1 --algorithm real; \
#     time ./main --p_select $p --uniform 0 --algorithm real; \
# done

# for p in $(seq 100 300 1000); do \
#     time ./main --p_size $p --uniform 1 --algorithm binary; \
#     time ./main --p_size $p --uniform 0 --algorithm binary; \
#     time ./main --p_size $p --uniform 1 --algorithm real; \
#     time ./main --p_size $p --uniform 0 --algorithm real; \
# done

# for p in $(seq 500 300 1100); do \
#     time ./main --term $p --algorithm binary; \
#     time ./main --term $p --algorithm real; \
# done	
