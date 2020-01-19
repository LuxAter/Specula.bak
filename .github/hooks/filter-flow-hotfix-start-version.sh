#!/bin/sh

VERSION=$1

if [ "$VERSION" == "patch" ] || [ "$VERSION" == "minor" ] || [ "$VERSION" == "major" ]; then
    VERSION=$(. "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" $VERSION)
elif [ -z "$VERSION" ]; then
    VERSION=$(. "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" hotfix)
else
    . "$(git rev-parse --show-toplevel)/.github/hooks/bump_version.sh" hotfix
fi

echo $VERSION
exit 0
