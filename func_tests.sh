#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
DEF='\033[0m'

test_num=1
failed_num=0
success_num=0

echo "Functional testing started"

for curl_file in func_tests/curl_*
do   
    CURL_OUTPUT=$(bash $curl_file)
    GREP_OUTPUT=$(bash ${curl_file//curl/grep} <<< $CURL_OUTPUT)

    if [ $? -eq 0 ]
    then
        echo -e "Test ${test_num}: ${GREEN}success${DEF}"
        let "success_num++"
    else
        echo -e "Test ${test_num}: ${RED}failure${DEF}"
        let "failed_num++"
    fi

    let "test_num++"
done

echo "Test results"
echo -e "${GREEN}Successful tests: ${success_num}${DEF}"
echo -e "${RED}Failed tests: ${failed_num}${DEF}"

echo "Functional testing finished"
