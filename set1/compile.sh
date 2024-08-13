#!/bin/bash
bin=bin
out=${1%.*}

mkdir ./"$bin" -p

# for i in "$@"; do
#     case "$i" in
#         *.cpp)
#             source+=("$i")
#             shift
#         ;;
#         *)
#             GXXFlags+=("$i")
#             shift
#         ;;
#     esac
# done
#echo "flags:" "${GXXFlags[@]}"
#echo "sources:" "${source[@]}"
g++ -std=c++17 -g3 -ggdb -O0 -DDEBUG -Wall -I./../ "$@" -o ./"$bin"/"$out"
./"$bin"/"$out"