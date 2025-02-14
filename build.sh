#!/bin/bash

# Backup previous build if one exists
if [ -z ./ncursed ]
then
  mv ncursed .ncursed~
fi

# Compile, then launch if successful
if [ make ]
then
  ./ncursed
else
  echo -e " [E] Build failure\n"
fi
