# Urnukh Tsogt
# URT633
# 11267557
#
# Mitchell Risling
# MJR810
# 11221612
#
# CMPT332
# a01-phase01
# 09:00, 19/09/2022

#!bin/bash

# requirements
# invoke by:
# 		partB.bash version
#			or
#			partB.bash version < inputfile
#				where version is partA1, partA2, or partA3 or partA4
# check proper archtitecture for version to be ran
# loop until user wishes to quit (with q or quit)
# file will contain 3 ints per line
#
# args to partA[1-4] on cmd line in form of:
# 	/partA threads deadline size

usage_info="Usage:\npartA[1-4] int int int\na\tswitch part being executed"
usage_info+="PartA[1-4]\nh\tdisplay this menu\nq\tquit\n"

# get, check and set info about users computer
# and commands invokation so we can compiles
# and execute
detected_OS=`uname`
version=$1
if ! [[ $version =~ partA[1-4] || $# -ne 1 ]]
then
	echo -e "Usage:\n./partB.bash partA[1-4]"
	echo -e "or\n./partB.bash partA[1-4] < input file "
	exit 1
fi

doPartA1 () {
	if [[ $detected_OS != Windows_NT ]]
	then
		echo must be on Windows to run A.1
		echo select a different part to run or quit with q
	else
		./partA1 ${args[0]} ${args[1]} ${args[2]}
	fi
}

doPartA2 () {
	if [[ $detected_OS != Linux ]]
	then
		echo must be on Linux to run A.2
		echo select a different part to run or quit with q
	else
		./partA2 ${args[0]} ${args[1]} ${args[2]}
	fi
}

doPartA3 () {
	if [[ $detected_OS != Linux ]]
	then
		echo must be on Linux to run A.3
		echo select a different part to run or quit with q
	else
		./partA3 ${args[0]} ${args[1]} ${args[2]}
	fi
}

doPartA4 () {
	echo A4 not yet implemented
	# ./partA4
}


#
# main loop
#

while read line
do
	if [[ $line =~ ^\ *[aA]\ +partA[1-4]\ *$ ]]
	then
		echo version was $version
		version=`expr match "$line" '.*\(partA[1-4]*\)'`
		echo version now $version

	elif [[ $line =~ ^\ *[qQ](uit)?\ *$ ]]
	then
		exit 0

	elif [[ $line =~ ^\ *[hH](elp)?\ *$ ]]
	then
		echo -e $usage_info

	else
		IFS=' ' read -r -a args <<< "$line"
		if [[ ${#args[@]} -ne 3  ]]
		then
			echo ${#args[@]} args provided. expect 3
			echo -e $usage_info

		else
			inputIsValid=0
			for item in ${args[@]}
			do
				if ! [[ $item =~ ^[0-9]|[1-9][0-9]+$ ]]
				then
					echo $item is not an integer
					inputIsValid=1
				fi
			done

			if [[ $inputIsValid ]]
			then
				case $version in
					("partA1")
						doPartA1
						;;
					("partA2")
						doPartA2
						;;
					("partA3")
						doPartA3
						;;
					("partA4")
						doPartA4
						;;
					*)
						echo invalid version
						exit 1
				esac
			fi
		fi
	fi
done
