#!/usr/bin/env bash

# Color setup
RED='\033[1;31m'
LIGHT_RED='\033[0;31m'
GREEN='\033[1;32m'
LIGHT_GREEN='\033[0;32m'
NO_COLOR='\033[0m'

correct=0
total=0

test_find() {
    dir="$1"
    shift
    opts="$*"

    if [ "$opts" == "" ]; then
        act=$(../my_find "$dir")
        exp=$(find "$dir")
    else
        act=$(../my_find "$dir" $opts)
        exp=$(find "$dir" $opts)
    fi

    if [ "$act" == "$exp" ]; then
        if [ "$opts" == "" ]; then
            echo -e "${GREEN}[PASS]${LIGHT_GREEN} ./my_find "$dir"${NO_COLOR}"
        else
            echo -e "${GREEN}[PASS]${LIGHT_GREEN} ./my_find "$dir" "$opts"${NO_COLOR}"
        fi
        correct=$(($correct + 1))
    else
        if [ "$opts" == "" ]; then
            echo -e "${RED}[FAIL]${LIGHT_RED} ./my_find "$dir" - Expected: "$exp". Got: "$act"${NO_COLOR}"
        else
            echo -e "${RED}[FAIL]${LIGHT_RED} ./my_find "$dir" "$opts" - Expected: "$exp". Got: "$act"${NO_COLOR}"
        fi
    fi

    total=$(($total + 1))
}

# ====================================

test_find "."
test_find "." "-name caca"
test_find "." "-iname" "caca"
test_find "/mnt/c/Users/noefr/Downloads/" "-name" "caca"
