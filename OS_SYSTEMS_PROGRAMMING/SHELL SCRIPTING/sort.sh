#!/bin/bash

# the reason we put the above line...the SHEBANG sequence is that the SHELL executes the script with the path of the shebang seq...here "/bin/bash"

echo -n "Enter the size of the array:- "
read size

arr=""


for((i=0;i<size;i++))
do
	echo -en "\nEnter the element $(( $i + 1 )) :-   "	
	read arr[$i]
done

#bubble sort
for(( i=0;i<size-1;i++))
do
	for((j=0;j<size-i-1;j++ ))
	do
		if [ ${arr[$j]}  -gt  ${arr[$(( $j + 1))]}  ] 
		then
			temp=${arr[$j]}
			arr[$j]=${arr[$(($j+1))]}
			arr[$(($j+1))]=$temp
		fi
	done
done

echo ""
echo -en "\nSorted elements are :-\t"

for((i=0;i<size;i++))
do
	echo -en "${arr[$i]}\t"
done

echo -e "\n\n"
