#!/bin/bash
set -e

#set vars
EXEC=/data/rpicomponents/build/rpicomponents_test_project

# RUN INPUT
if [ "$1" = 'start' ]; then
    $EXEC
else 
    exec "$@"
fi