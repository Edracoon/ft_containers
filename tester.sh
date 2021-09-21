#!/bin/bash

args=("$@")
if [ ${args[0]} = "vector" ]
then
	make fclean -C ./vector
	make TESTER=${args[1]} -C ./vector
	echo -e "\n========== FT_"${args[1]}" =========="
	./vector/FT_${args[1]}.exe
	echo -e "\n========== STL_"${args[1]}" =========="
	./vector/STL_${args[1]}.exe
	rm -f */*/*.o
	rm -f */*.exe
fi
if [ ${args[0]} = "clean" ]
then
	rm -f *.o
	rm -f */*.o
	rm -f */*/*.o
fi