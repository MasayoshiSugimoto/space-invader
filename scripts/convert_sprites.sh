#!/bin/bash


CONFIG_DATA_SPRITE_DIRECTORY_OUT='/mnt/c/Users/hanbu/Dev/space-invader/data/sprites'
CONFIG_DATA_SPRITE_DIRECTORY_IN='/mnt/c/Users/hanbu/Dev/space-invader/sprites'


function convert_file {
  local sprite_file="$1"
  local width=$(wc -L "$sprite_file" | cut -d' ' -f1)
  local height=$(($(wc -l "$sprite_file" | cut -d' ' -f1) + 1))
  echo "$width $height"
  # Read needs an empty new line at the end of the stream so we add one if not found.
  local file_content=''
  if ! grep '^$' "$sprite_file"; then
    file_content=$(cat "$sprite_file" <(echo ""))
  else
    file_content=$(cat "$sprite_file")
  fi
  file_content=$(
    echo "$file_content" \
      | while IFS= read -r -e line; do
        printf "%-${width}s\n" "$line"
      done
  )
  echo "$file_content"
  echo "$file_content" \
    | while IFS= read -r -e line; do
      sed -E 's/./008/g'
    done
}

#convert_file 'credits.txt'


for file_name in $(ls $CONFIG_DATA_SPRITE_DIRECTORY_IN); do
  input_file="$CONFIG_DATA_SPRITE_DIRECTORY_IN/$file_name"
  output_file="$CONFIG_DATA_SPRITE_DIRECTORY_OUT/$(echo "$file_name" | sed 's/\.txt$/.dat/')"
  echo "input_file=$input_file"
  echo "output_file=$output_file"
  convert_file "$input_file" > "$output_file"
done
