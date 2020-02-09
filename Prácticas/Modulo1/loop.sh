#!/bin/bash

VAR=0

for (( i=0; i<$1; i++ ))
do
    (( 10+12*2 ))
    (( VAR++ ))
done

echo "el valor de la variable es $VAR" 
