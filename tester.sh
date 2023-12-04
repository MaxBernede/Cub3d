#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

TIMEOUT=0.5

run_test() {
	./cub3D "$1" > /dev/null 2>&1 &
	command_pid=$!
	sleep $TIMEOUT

	if ps -p $command_pid > /dev/null; then
		kill -TERM $command_pid > /dev/null 2>&1
		return 1
	fi
	return 0
}

echo -e "${BLUE}START BAD TESTS${NC}"
for file in maps/bad/*.cub
do
  run_test "$file"
  
if [ $? -eq 0 ]; then
  echo -e "${GREEN}Test Passed Successfully${NC} for $file"
elif [ $? -eq 1 ]; then
   echo -e "${RED}Test Timed Out Worked while shouldnt${NC} for $file"
else
	echo -e "${RED}NOT POSSIBLE${NC} for $file"
fi
done

echo -e "${BLUE}START GOOD TESTS${NC}"
for file in maps/good/*.cub
do
  run_test "$file"
  
	if [ $? -eq 0 ]; then
		echo -e "${RED}Test Crashed${NC} for $file"
	elif [ $? -eq 1 ]; then
		echo -e "${GREEN}Test Passed Successfully${NC} for $file"
	else
		echo -e "${RED}NOT POSSIBLE${NC} for $file"
	fi
done
