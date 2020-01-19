#!/bin/sh

if [ "$1" == "hotfix" ]; then
    VERSION="PATCH"
elif [ "$1" == "release" ]; then
    VERSION="MINOR"
elif [ "$1" == "patch" ]; then
    VERSION="PATCH"
elif [ "$1" == "minor" ]; then
    VERSION="MINOR"
elif [ "$1" == "major" ]; then
    VERSION="MAJOR"
else
    VERSION="PATCH"
fi

CMAKE=$(git rev-parse --show-toplevel)/CMakeLists.txt
if [ "$VERSION" == "PATCH" ]; then
    sed -i -r 's/(.*) VERSION ([0-9]+)\.([0-9]+)\.([0-9]+)(.*)/echo "\1 VERSION \2.\3.$((\4+1))\5"/ge' $CMAKE
elif [ "$VERSION" == "MINOR" ]; then
    sed -i -r 's/(.*) VERSION ([0-9]+)\.([0-9]+)\.([0-9]+)(.*)/echo "\1 VERSION \2.$((\3+1)).\4\5"/ge' $CMAKE
elif [ "$VERSION" == "MAJOR" ]; then
    sed -i -r 's/(.*) VERSION ([0-9]+)\.([0-9]+)\.([0-9]+)(.*)/echo "\1 VERSION $((\2+1)).\3.\4\5"/ge' $CMAKE
fi
sed -r 's/(.*) VERSION ([0-9]+)\.([0-9]+)\.([0-9]+)(.*)/\2.\3.\4/;t;d' $CMAKE
