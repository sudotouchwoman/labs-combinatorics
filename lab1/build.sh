#!/usr/bin/bash
[[ -f main ]] && { echo "removed executable"; rm main; } || echo "executable not found, thus not removed"
g++ -o main main.c trees.c
echo "build complete"
