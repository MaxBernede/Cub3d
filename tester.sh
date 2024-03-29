#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

TIMEOUT=0.5

run_test() {
    #./cub3D "$1" > /dev/null 2> /dev/null &
    ./cub3D "$1" &
    command_pid=$!
    sleep $TIMEOUT

    if ps -p $command_pid > /dev/null; then
        kill -TERM $command_pid > /dev/null 2>&1
        wait $command_pid 2>/dev/null
        return 1
    fi
    wait $command_pid 2>/dev/null
    return 0
}

print_result() {
    local file=$1
    local status=$2

	if [ "$label" == "GOOD" ]; then
        status=$((status - 1))
    fi
    if [ $status -eq 0 ]; then
        echo -e "${GREEN}Test Passed Successfully${NC} for $file"
    elif [ $status -eq 1 ] || [ $status -eq -1 ]; then
        echo -e "${RED}Test Error${NC} for $file"
    else
        echo -e "${RED}NOT POSSIBLE${NC} for $file"
    fi
}

run_tests() {
    local path=$1
    local label=$2

    echo -e "${BLUE}START $label TESTS${NC}"
    for file in $path/*.cub
    do
        run_test "$file"
        print_result "$file" $?
    done
}

echo -e "Choose an option:"
echo -e "1. Check all files"
echo -e "2. Check only bad files"
echo -e "3. Check only good files"
read -p "Enter your choice (1/2/3): " choice

case $choice in
    1)
        run_tests "maps/bad" "BAD"
        run_tests "maps/good" "GOOD"
        ;;
    2)
        run_tests "maps/bad" "BAD"
        ;;
    3)
        run_tests "maps/good" "GOOD"
        ;;
    *)
        echo -e "${RED}Invalid choice${NC}"
        ;;
esac
