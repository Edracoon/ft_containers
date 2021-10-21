#!/bin/bash

args=("$@")

if [[ (${args[0]}) && (${args[1]} = "all") ]]
then
	rm -f */*.exe
	rm -f */*/*.o
	make fclean -C ./${args[0]}_tests
	make TESTER=${args[1]} -C ./${args[0]}_tests
	./${args[0]}_tests/FT_${args[1]}.exe > ft.log
	./${args[0]}_tests/STL_${args[1]}.exe > stl.log
	diff ft.log stl.log > diff_all.log
	cat diff_all.log
	rm -f */*.exe
	rm -f */*/*.o

elif [ ${args[0]} = "vector" ]
then
	rm -f */*.exe
	rm -f */*/*.o
	make fclean -C ./${args[0]}_tests
	make TESTER=${args[1]} -C ./${args[0]}_tests
	echo -e "-=###############=- FT_"${args[1]}" -=###############=-"
	./${args[0]}_tests/FT_${args[1]}.exe
	echo -e "-=###############=- STL_"${args[1]}" -=###############=-"
	./${args[0]}_tests/STL_${args[1]}.exe 
	rm -f *.log
	rm -f */*/*.o
	rm -f */*.exe

elif [ ${args[0]} ]
then
	rm -f */*.exe
	rm -f */*/*.o
	make fclean -C ./${args[0]}_tests
	make TESTER=${args[1]} -C ./${args[0]}_tests
	echo -e "\n-=###############=- FT_"${args[1]}" -=###############=-\n"
	./${args[0]}_tests/FT_${args[1]}.exe
	echo -e "\n-=###############=- STL_"${args[1]}" -=###############=-\n"
	./${args[0]}_tests/STL_${args[1]}.exe 
	rm -f *.log
	rm -f */*/*.o
	rm -f */*.exe
fi