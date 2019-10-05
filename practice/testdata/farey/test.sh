#!/bin/bash
for ((i=0;i<=9;i++))
do
cp farey$i.in farey.in
time ./farey
diff farey.out farey$i.out
rm farey.in farey.out
read -p "ENTER"
done
