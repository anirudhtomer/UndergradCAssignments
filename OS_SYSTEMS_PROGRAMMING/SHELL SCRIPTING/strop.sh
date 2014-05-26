#!/bin/bash

if [ $# -ne 2 ] # checks if the two strings are entered as command line by counting the no. of parameters passed to the script 
then
	echo "ENTER STRING1 and STRING2 AS COMMAND LINE PARAMETERS...e.g $  ./strop.sh toshish ananya"
	exit 1
fi


str1=$1
str2=$2

lenstr1=$(expr length $1)
lenstr2=$(expr length $2)

while [ 1 ] #infinite loop...
do
	echo -e "\n\t************ STRING OPERATIONS **************\t\n"
	echo -e "1. REVERSE 1st String\t2.Check 1st String for PALINDROME\t3.Find 2nd String as SUBSTRING in 1st String \t4.EXIT\n"
	read -p "Enter your choice:-  " ch

	case $ch in
			
		1)	revstr=""
			for((i=${lenstr1};i>=1;i--))			 
			do
				revstr=${revstr}$(echo $str1 | cut -b $i-$i)
			done

			echo "The reverse of the string \"${str1}\" is \"${revstr}\" "
			;;
		
		2)  # 2options---------do reverse of the string & check if they are equal .... or read from both ends & check at center
			# I am picking up the second option to work more on shell scripts
	
			flag=0
			for((i=1,j=${lenstr1};i<=j;i++,j--))
			do
				if [ $(echo $str1 | cut -b $i-$i) != $(echo $str1 | cut -b $j-$j)  ]
				then
					flag=1
					break
				fi
			done

			if [ $flag -eq 1  ]
			then
				echo "String $str1 is not a palindrome"
			else
				echo "String $str1 is a palindrome"
			fi
			;;

		3)  flag=0
			cnt=0
			temp=0

			for((i=1;i<=$lenstr1;i++))
			do
				
				if [ $(echo $str1 |  cut -b $i-$i) = $(echo $str2 | cut -b 1-1) ]
				then 
					
					flag=0
					temp=$i
					
					for((j=1;j<=$lenstr2;j++))
					do
						if [ $i -gt $lenstr1 ]
						then
							flag=1
							break	
						fi
					
						# even though the above condition executes the same code as the condition below...u can't OR them
						# coz in OR the condition below is gonna get checked which may lead to error if $i>string length
						if [ $(echo $str1 |  cut -b $i-$i) != $(echo $str2 | cut -b $j-$j) ] 
						then
							flag=1
							break
						fi

						i=$(($i + 1))
					done

					if [ $flag -eq 0 ]
					then 
						cnt=$(( $cnt + 1 ))
						i=$(($i-1))
					else
						i=$temp
					fi
				fi

			done

			echo "String \"$str2\" occured $cnt times as a substring in String \"$str1\"";
			;;

		4) exit 0 ;;

		*) echo -e "\nWrong choice entered"   
		# *) matches 0 or more character string...if u say "?)" that means u r trying to match one single character...called REGEX

	
	esac
	
	read -p "Press Enter to continue" anything

done
