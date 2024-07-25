#!/bin/bash
bin=bin
out=${1%.*}

mkdir ./"$bin" -p

g++ -std=c++17 -O2 -Wall "$@" -o ./"$bin"/"$out" 
./"$bin"/"$out"