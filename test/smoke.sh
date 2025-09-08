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

TMP_FILE=test/$(date --iso-8601=seconds).tmp
trap "rm -rf -- $TMP_FILE" EXIT

echo Permutations number
./permutate 9 > $TMP_FILE
assert "$(wc -l --total=only $TMP_FILE)" "362880"

echo Permutations uniqness 
assert "$(sort -h $TMP_FILE | uniq -d)" ""

echo Bruteforce number
./brute_4x4 3x3 $(nproc) all > $TMP_FILE
assert "$(wc -l --total=only $TMP_FILE)" "362880"

echo Bruteforce uniqness 
assert "$(sort -h $TMP_FILE | uniq -d)" ""

echo Bruteforce result
./brute_4x4 3x3 $(nproc) min > $TMP_FILE
assert "$(tail -n 1 $TMP_FILE | cut -d' ' -f1)" "97"

echo Generate lookup table
assert "$(./gentab outcome 3x3 1,2,3,4,0,5,6,7,8 pretty 0 | sed -n 's/^monotonous outcome intervals: \(.*\)$/\1/p')" "97"
assert "$(./gentab outcome 3x4 default pretty 0 | sed -n 's/^monotonous outcome intervals: \(.*\)$/\1/p')" "1332"
assert "$(./gentab outcome 4x4 1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,15 pretty 0 | sed -n 's/^monotonous outcome intervals: \(.*\)$/\1/p')" "35617"

echo
[ $FAILED -eq 0 ] && ok "No errors occurred" || fail "Some errors occured"
