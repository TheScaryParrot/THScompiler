#!/bin/bash

time ./THScompiler ../testing/testFile.ths -o testFile -k --link-files ../testing/lib/print.o ../testing/lib/mod.o ../testing/lib/toChar.o
mv a.s testFile.s
rm a.o
