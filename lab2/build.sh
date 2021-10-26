#!/usr/bin/bash
[[ -f main ]] && { echo "removed executable"; rm main; } || echo "executable not found, thus not removed"
g++ -o main main.cpp permutations.cpp
echo "build complete"
