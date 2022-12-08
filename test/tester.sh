#!/usr/bin/bash

cc="clang++"
flags="-Wall -Wextra -Werror -std=c++98"
include="../" 
nbargs=$#
argfile=$1
white="\033[1;37m"
grey="\033[0;37m"
red="\033[1;31m"
green="\033[1;32m"

exe()
{
	$cc $flags -I ./ -I $include -D NAMESPACE=std src/$1/$2 2> output/err/std_compile_$1_$2.err
       ./a.out 1> output/std_$1_$2.output 
	$cc $flags -I ./ -I $include -D NAMESPACE=ft src/$1/$2 2> output/err/ft_compile_$1_$2.err
       ./a.out 1> output/ft_$1_$2.output 

}

check_diff_files()
{
	echo -e -n  $white "DIFF :"
	file=$2
	container=$1
	diff output/ft_$1_$2.output  output/std_$1_$2.output  > diff/$file.diff
	if [ -s diff/$file.diff ]; then
		echo -e $red "KO" $grey
		cat diff/$file.diff
	else
		rm output/ft_$1_$2.output  output/std_$1_$2.output 
		echo -e -n $green "OK" $grey
	fi
}

check_compile_err()
{
	echo -e -n $white "Compile :"
	file=$1 
	if [ -s output/err/ft_compile_vector_$1.err ]; then 
		echo -e -n $red "KO" $grey " (if *_err.cpp = "$green"OK"$grey")"
	else
		echo -e -n $green  "OK" $grey
	fi
}

launch_exe ()
{	
	if [[ $nbargs -eq 1 ]]; then 
		echo -e $white $argfile $grey
		file=$(basename "${argfile}")
		exe  vector $file
		check_compile_err $file
		check_diff_files vector $file
		echo ""
	else
		for file in src/vector/*
		do 
			echo -e $white $file $grey
			file=$(basename "${file}")
			exe  vector $file
			check_compile_err $file
			check_diff_files vector $file
			echo -e "\n"
		done
	fi
}

purge_files()
{
	folder=$1
	for files in $folder/*
	do 
		if [ ! -s $files ]; then
			rm $files
		fi
	done
}

mkdir output output/err 2> /dev/null

echo -e "\n////////////////		" $white "T E S T E R" $grey "		////////////////\n"

launch_exe

purge_files diff
purge_files output/err




