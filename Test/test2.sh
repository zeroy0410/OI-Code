#!/bin/bash
argc=$#
if [ $argc -eq 0 ]
then
	echo "Missing arguments..."
	echo "Usage: cl [FILE]... OPTION..."
	echo "type --help for more information"
else
	((--argc))
	if [ $1 == "--help" ] || [ $1 == "-h" ]
	then
		echo "Usage: cl [FILE]... OPTION..."
		echo "Compile and Run cpp files"
		echo "        --licence = -l        Show licence infomation"
		echo "        --help = -h           Give this help list"
		echo "        --in = -i  [FILE]     Read from FILE"
		echo "        --out = -o [FILE]     Output to FILE"
	elif [ $1 == "--licence" ] || [ $1 == "-l" ]
	then
		echo "	This program is free software: you can redistribute it and/or modify"
		echo "    it under the terms of the GNU General Public License as published by"
		echo "    the Free Software Foundation, either version 3 of the License, or"
		echo "    (at your option) any later version."
		echo ""
		echo "    This program is distributed in the hope that it will be useful,"
		echo "    but WITHOUT ANY WARRANTY; without even the implied warranty of"
		echo "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
		echo "    GNU General Public License for more details."
		echo ""
		echo "    You should have received a copy of the GNU General Public License"
		echo "    along with this program.  If not, see <https://www.gnu.org/licenses/>."
	fi
	echo "Compiling..."
	g++ $1
	if [ $? -eq 0 ]
	then
		echo "Running..."
#		more ~/Desktop/A.in
		echo "----------------------"
		EXIT_CODE=$?
		__START_S=$(date +%s)
		__START_N=$(date +%N)
		if [ $argc -gt 0 ]
			((--argc))
			if [ $2 == "--in" ] || [ $2 == "-i" ]
			then
				if [ $argc -gt 0 ]
				then
					((--argc))
					if [$argc -eq 0 ]
					then
						./a.out < $3
						EXIT_CODE=$?
					else
						((--argc))
						if [ $4 == "--out" ] || [ $4 == "-o" ]
						then
							if [ $argc -gt 0 ]
							then
								((--argc))
								./a.out < $3 > $5
								EXIT_CODE=$?
							else
								echo "Missing arguments for \"--out\""
							fi
						fi
					fi
				else
					echo "Missing arguments for \"--in\""
				fi
			elif [ $2 == "--out" ] || [ $2 == "-o" ]
			then
				if [ $argc -gt 0 ]
				then
					((--argc))
					if [$argc -eq 0 ]
					then
						./a.out > $3
						EXIT_CODE=$?
					else
						((--argc))
						if [ $4 == "--in" ] || [ $4 == "-i" ]
						then
							if [ $argc -gt 0 ]
							then
								((--argc))
								./a.out < $5 > $3
								EXIT_CODE=$?
							else
								echo "Missing arguments for \"--in\""
							fi
						fi
					fi
				else
					echo "Missing arguments for \"--out\""
				fi
			else
				echo "Improper argument $2"
			fi
		else
			./a.out
			EXIT_CODE=$?
		fi
		__END_N=$(date +%N)
		__END_S=$(date +%s)
		__START_N=$(echo -e $__START_N | sed -r 's/0*([0-9])/\1/')
		__END_N=$(echo -e $__END_N | sed -r 's/0*([0-9])/\1/')
		_EXEC_TIME_S=$((__END_S - __START_S))
		_EXEC_TIME_N=$((__END_N - __START_N))
		if [ $_EXEC_TIME_N -lt 0 ]
		then
			_EXEC_TIME_N=$((0 - _EXEC_TIME_N))
			_EXEC_TIME_S=$((_EXEC_TIME_S - 1))
		fi
		echo "----------------------"
		printf "Process exited in %d.%09d second with exit code %d\n" "$_EXEC_TIME_S" "$_EXEC_TIME_N" "$EXIT_CODE"
		rm ./a.out
	else
		echo "Compile ERROR!"
	fi
fi