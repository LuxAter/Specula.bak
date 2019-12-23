#!/bin/bash

echo > "$1"
for file in $2/*.cl; do
  filename=$(echo "$file" | sed -E 's/.*\/([^\/]+)$/\1/g' | sed -E 's/\.| |-/_/g' | sed -E 's/_cl/_kernel/g')
  echo -e "static const char $filename[] = {$(hexdump "$file" -ve '1/1 "0x%.2x,"')};\nstatic const long unsigned int ${filename}_size = sizeof($filename);\n" >> "$1"
done