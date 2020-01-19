#!/bin/sh

ROOT=$(git rev-parse --show-toplevel)/
ln -s $ROOT/.github/hooks/filter-flow-release-start-version.sh $ROOT/.git/hooks/filter-flow-release-start-version
ln -s $ROOT/.github/hooks/filter-flow-hotfix-start-version.sh $ROOT/.git/hooks/filter-flow-hotfix-start-version
