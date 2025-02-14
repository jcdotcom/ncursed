#!/bin/bash

# Backup previous build if one exists
if [ -f ./ncursed ]
then
	mv ncursed .ncursed~
fi

# Compile, then launch if successful (make returned 0)
if [ $(make) ]
then
	echo -e " [E] Build failure\n"
else
	./ncursed
fi
