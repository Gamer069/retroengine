#!/bin/zsh

clear;

function play_suc_sound {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        afplay /System/Library/Sounds/Funk.aiff
    fi
}

function play_fail_sound {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        afplay /System/Library/Sounds/Bottle.aiff
    fi
}

function check_fail {
    if [ $? -ne 0 ]; then
        echo "\e[91mFAILED\e[0m"
        play_fail_sound
        exit -1
    else 
        echo "\e[92mSUCCESS\e[0m"
        play_suc_sound
    fi
}

function check_fail_inp_suc_out {
    if [ $? -ne 0 ]; then
        printf "\e[91m"
        printf $1
        printf "\e[0m"
        printf "\n"

        play_fail_sound
        exit -1
    else
        echo "\e[92mSUCCESS\e[0m"
        play_suc_sound
    fi
}

function check_fail_no_out {
    if [ $? -ne 0 ]; then
        printf "\e[91m"
        printf "FAILED"
        printf "\e[0m"
        printf "\n"

        play_fail_sound

        exit -1
    fi
}

printf "\e[96mTesting if libs exist...\e[0m " 
ls lib/glfw > /dev/null 2>&1
check_fail_no_out
ls lib/imgui > /dev/null 2>&1
check_fail_no_out
ls lib/spdlog > /dev/null 2>&1
check_fail_inp_suc_out "ERROR: Make sure that you clone'ed the retroengine repository recursively or just fill in all of the libraries."

printf "\e[96mGenerating unix makefile...\e[0m "
cmake . > /dev/null 2>&1
check_fail
printf "\e[96mMaking...\e[0m "
make > /dev/null 2>&1
check_fail
printf "\e[96mInstalling sandbox...\e[0m "
make -f install.mk > /dev/null 2>&1
check_fail
