#!/bin/bash

OUTPUT=""
TYPE="png"

function show_help() {
  printf "usage: gen.sh [options] SOURCE\n"
  printf "Generates a video/gif given a sequence of images.\n\n"
  printf "  options:\n"
  printf "    -h -?          Show this help text\n"
  printf "    -o OUTPUT      Sets ouput path\n"
  printf "    -t EXT         Sets source file extension\n"
  exit 0
}

OPTIND=1

while getopts "h?o:t:" opt; do
  case "$opt" in
    h|\?)
      show_help
      ;;
    o)
      OUTPUT=$OPTARG
      ;;
    t)
      TYPE=$OPTARG
      ;;
  esac
done

shift $((OPTIND-1))

SOURCE="$1"

if [[ -z "$SOURCE" ]]; then
  show_help
fi

if [[ -z "$OUTPUT" ]]; then
  OUTPUT="$SOURCE/$(basename $SOURCE).gif"
fi

ffmpeg -i $SOURCE/%d.$TYPE $OUTPUT
