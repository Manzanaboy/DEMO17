#!/bin/bash

# required files
SOURCE_FILE="projet17.c"
TEST_FILE="projet17.x"
INTER_FILE="inter_demo.x"

# compile SOURCE_FILE
echo "RELAX WHILE I COMPILE AND TEST YOUR CODE (RENDU1)!"
gcc "$SOURCE_FILE" -o "$TEST_FILE" -lm

# counter for test files nbr
let "i = 1"

WRONG=""
LAST_INTER=6

# iterates through the first 6 test files
while [ $i -le $LAST_INTER ]; do
	
	# print current test number
	echo
	echo "TEST $i"
	
	# run TEST_FILE for test i , print and save results
	MY_OUT_STRING=$("./$TEST_FILE" < "test$i.txt")
	echo "OUTPUT IS: "
	echo "$MY_OUT_STRING"
	
	# run INTER_FILE for test i , save results
	OUT_STRING=$("./$INTER_FILE" < "test$i.txt")
	
	# compare output of the programs
  	if [ "$MY_OUT_STRING" == "$OUT_STRING" ]; then
  		echo "BOTH OUTPUT ARE THE SAME"
	else
		echo "NOT QUITE, IT SHOULD BE:"
		echo "$OUT_STRING"
		WRONG="$WRONG$i "
	fi
	let "i++"
done

echo
if [ "$WRONG" != "" ]; then
	echo "your program did not passed test(s) $WRONG"
else
	echo "your program produced the same output as the demo"
	echo "but for test6.txt, it does not guarantee that your program is correct"
fi
echo
