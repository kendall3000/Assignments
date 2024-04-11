#!/bin/bash

for i in {1..8}; do
  echo ========= sum$i
  gcc -Wall sum$i.c -o sum$i
  ./sum$i 3 -12 14 0 7 -8 3
done

echo ========= python
python3 sum.py 3 -12 14 0 7 -8 3
