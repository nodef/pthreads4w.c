#!/usr/bin/env bash
# Fetch the latest version of the library
fetch() {
if [ -d "pthreads4w" ]; then return; fi
URL="https://webwerks.dl.sourceforge.net/project/pthreads4w/pthreads4w-code-v3.0.0.zip?viasf=1"
ZIP="${URL##*/}"
ZIP="${ZIP%%\?*}"
mkdir -p .build
cd .build

# Download the release
if [ ! -f "$ZIP" ]; then
  echo "Downloading $ZIP from $URL ..."
  curl -L "$URL" -o "$ZIP"
  echo ""
fi

# Unzip the release
if [ ! -d "$DIR" ]; then
  echo "Unzipping $ZIP to .build/$DIR ..."
  cp "$ZIP" "$ZIP.bak"
  unzip -q "$ZIP"
  rm "$ZIP"
  mv "$ZIP.bak" "$ZIP"
  echo ""
fi
DIR="$(ls -d pthreads4w-*/ | head -n 1)"
DIR="${DIR%/}"
cd ..

# Copy the libs to the package directory
echo "Copying libs to pthreads4w/ ..."
rm -rf pthreads4w
mkdir -p pthreads4w
cp -f ".build/$DIR"/*.c pthreads4w/
cp -f ".build/$DIR"/*.h pthreads4w/
echo ""
}


# Test the project
test() {
echo "Running 01-thread-creation.c ..."
clang -I. -o 01.exe examples/01-thread-creation.c      && ./01.exe && echo -e "\n"
echo "Running 02-mutex-locking.c ..."
clang -I. -o 02.exe examples/02-mutex-locking.c        && ./02.exe && echo -e "\n"
echo "Running 03-condition-variables.c ..."
clang -I. -o 03.exe examples/03-condition-variables.c  && ./03.exe && echo -e "\n"
}


# Main script
if [[ "$1" == "test" ]]; then test
elif [[ "$1" == "fetch" ]]; then fetch
else echo "Usage: $0 {fetch|test}"; fi
