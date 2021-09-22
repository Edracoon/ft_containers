#!/bin/bash

args=("$@")
if [ ${args[0]} = "vector" ]
then
	make fclean -C ./vector
	make TESTER=${args[1]} -C ./vector
	echo -e "========== FT_"${args[1]}" =========="
	./vector/FT_${args[1]}.exe # > ft.log
	echo -e "========== STL_"${args[1]}" =========="
	./vector/STL_${args[1]}.exe # > stl.log
	#echo "=== diff ft.log stl.log ==="
	#diff ft.log stl.log | cat
	rm -f *.log
	rm -f */*/*.o
	rm -f */*.exe
fi

if [ ${args[0]} = "all" ]
then
	make fclean -C ./vector
	make TESTER=${args[1]} -C ./vector
	echo -e "========== FT_"${args[1]}" =========="
	./vector/FT_${args[1]}.exe # > ft.log
	echo -e "========== STL_"${args[1]}" =========="
	./vector/STL_${args[1]}.exe # > stl.log
	#echo "=== diff ft.log stl.log ==="
	#diff ft.log stl.log | cat
	rm -f *.log
	rm -f */*/*.o
	rm -f */*.exe
	rm -f *.o
	rm -f */*.o
	rm -f */*/*.o
fi