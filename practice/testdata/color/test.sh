#!/bin/bash
for ((i=0;i<=9;i++))
do
cp color$i.in color.in
time ./color
diff color.out color$i.out
rm color.in color.out
read -p "ENTER"
done
