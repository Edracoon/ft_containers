#!/bin/bash

args=("$@")

if [[ (${args[0]} = "vector") && (${args[1]} = "all") ]]
then
	make fclean -C ./vector
	make TESTER=${args[1]} -C ./vector
	./vector/FT_${args[1]}.exe > ft.log
	./vector/STL_${args[1]}.exe > stl.log
	diff ft.log stl.log > diff_all.log
	cat diff_all.log
	rm -f */*.exe
	rm -f */*/*.o

elif [ ${args[0]} = "vector" ]
then
	make fclean -C ./vector
	make TESTER=${args[1]} -C ./vector
	echo -e "========== FT_"${args[1]}" =========="
	./vector/FT_${args[1]}.exe
	echo -e "========== STL_"${args[1]}" =========="
	./vector/STL_${args[1]}.exe 
	rm -f *.log
	rm -f */*/*.o
	rm -f */*.exe
fi