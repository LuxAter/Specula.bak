#!/bin/sh

VERSION=$1

if [ "$VERSION" == "patch" ] || [ "$VERSION" == "minor" ] || [ "$VERSION" == "major" ]; then
    VERSION=$(. "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" $VERSION)
elif [ -z "$VERSION" ]; then
    VERSION=$(. "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" release)
else
    . "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" release
fi

echo $VERSION
exit 0
