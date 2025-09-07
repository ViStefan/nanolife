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

echo Generate lookup table
assert "$(./gentab outcome 4x4 1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,15 pretty 0 | sed -n 's/^monotonous outcome intervals: \(.*\)$/\1/p')" "35617"

echo
[ $FAILED -eq 0 ] && ok "No errors occurred" || fail "Some errors occured"
