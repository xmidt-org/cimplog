#!/bin/sh
ONBOARDING_LOG=../build/src/onboarding_log
$ONBOARDING_LOG "TEST" "Simple onboarding log with module"
$ONBOARDING_LOG "Simple onboarding log without module"
ARGS="arguments"
$ONBOARDING_LOG "Simple onboarding log with $ARGS"
