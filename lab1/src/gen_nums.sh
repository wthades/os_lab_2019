#!/bin/bash

> numbers.txt

for i in {1..150}
do
    echo $(( $(od -An -N2 -i /dev/random) % 1000 )) >> numbers.txt
done