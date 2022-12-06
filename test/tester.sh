#!/usr/bin/bash

cc="clang++"
flags="-Wall -Wextra -Werror -std=c++98"
include="../"

exe()
{
	$cc $flags -I ./ -I $include -D NAMESPACE=std src/$1/$2 2> output/err/std_compile_$1_$2.err
       ./a.out 2> output/err/std_$1_$2.err 1> output/std_$1_$2.output 
	$cc $flags -I ./ -I $include -D NAMESPACE=ft src/$1/$2 2> output/err/ft_compile_$1_$2.err
       ./a.out 2> output/err/ft_$1_$2.err 1> output/ft_$1_$2.output 

}

mkdir output output/err

for file in src/vector/*
do 
	echo "////////////////	DIFF for " vector_$file " ////////////////////"
	file=$(basename "${file}")
	exe  vector $file
	diff output/ft_vector_$file.output output/std_vector_$file.output
done

