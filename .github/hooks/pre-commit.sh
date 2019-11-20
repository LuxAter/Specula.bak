#!/bin/sh

sed -i -r 's/(project)(.*)(VERSION) ([0-9]+).([0-9]+).([0-9]+)(.*)/echo "\1\2\3 \4.\5.$((\6+1))\7"/ge' $(git rev-parse --show-toplevel)/CMakeLists.txt
git add $(git rev-parse --show-toplevel)/CMakeLists.txt
