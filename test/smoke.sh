#!/bin/sh

FAILED=0

color() {
    local esc="\e["
    local color=${esc}$1m
    local end=${esc}0m

    printf "%s$2%s" $color $end
}

fail() {
    echo -e $(color 31 Failed) "${@}" 
    exit 1
}

ok() {
    echo -e $(color 32 Ok) "${@}"  
    exit 0
}


assert() {
    if [ "$1" = "$2" ]; then
        echo $(ok $1)
    else
        export FAILED=1
        echo $(fail $1 != $2)
    fi
}

echo Permutations number
assert "$(./permutate 9 | wc -l)" "362880"

echo Permutations uniqness 
assert "$(./permutate 9 | sort -h | uniq -d)" ""

echo Bruteforce number
assert "$(./brute_4x4 | wc -l)" "362880"

echo Bruteforce uniqness 
assert "$(./brute_4x4 | sort -h | uniq -d)" ""

echo
[ $FAILED -eq 0 ] && ok "No errors ocurred" || fail "Some errors occured"
