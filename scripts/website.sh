#!/bin/bash

if [[ -d @CMAKE_CURRENT_BINARY_DIR@/pages ]]; then
  rm -r @CMAKE_CURRENT_BINARY_DIR@/pages
fi
mkdir @CMAKE_CURRENT_BINARY_DIR@/pages
mkdir @CMAKE_CURRENT_BINARY_DIR@/pages/files

if [[ -d @CMAKE_CURRENT_SOURCE_DIR@/docs ]]; then
  cp -r @CMAKE_CURRENT_SOURCE_DIR@/docs/* pages/
fi
if [[ -d @CMAKE_CURRENT_BINARY_DIR@/html ]]; then
  cp -r @CMAKE_CURRENT_BINARY_DIR@/html pages/api
fi
if [[ -d @CMAKE_CURRENT_BINARY_DIR@/latex ]]; then
  cd @CMAKE_CURRENT_BINARY_DIR@/latex && make
  cp @CMAKE_CURRENT_BINARY_DIR@/latex/refman.pdf @CMAKE_CURRENT_BINARY_DIR@/pages/files/
fi
