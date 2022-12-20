# How to use

open `tester.sh`
- modify `include="../include/" # path for containers (default in include/ from repo)` var
- or modify ( -I <your_header_folder> ) `flags="-Wall -Wextra -Werror -std=c++98"`

## Commands

- all containers : `./tester.sh` executes tests for all containers (vector-map)
- specific container : `./tester.sh <container>` - example: `./tester.sh vector`
- one file : `./tester.sh <file>` - example: `./tester.sh src/vector/assign.cpp`

### About the tester

The tester tests: ( THE MOST PART OF TESTS CAME FROM https://github.com/mli42/containers_test )
- `compilation` with `flags="-Wall -Wextra -Werror -std=c++98"` flags. Compilations errors are in output/err.
- `time` execution from your container and std::<container>
- `diff` your container output and std::<container> output. Diff can be found in diff/ (and output in output/(ft || std)_<container>_<file_test>.output)
- `leaks` check with allocs > frees and errors (ERROR SUMMARY). Errors are in output/ folder.

![tester](https://user-images.githubusercontent.com/60407248/207082123-4c291799-a591-472d-8b81-dad6bbda6a9d.png)

## Random docs

- containers / iterators https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/Intro--Conteneurs-Iterateurs.html 
- iterator traits https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits 
- allocator https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed 
- constructor errors/exceptions safety https://en.cppreference.com/w/cpp/memory/uninitialized_copy
- exceptions safety https://www.stroustrup.com/except.pdf 
- SFINAE https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/ 
- size_t ptrdiff_t https://pvs-studio.com/en/blog/posts/cpp/a0050/
- typename keyword https://cplusplus.com/forum/general/219039/
- tree iterators https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
- explicit + conversion operator https://subscription.packtpub.com/book/programming/9781786465184/1/ch01lvl1sec14/using-explicit-constructors-and-conversion-operators-to-avoid-implicit-conversion 
- conversion operators https://stackoverflow.com/questions/1307876/how-do-conversion-operators-work-in-c 
https://www.nextptr.com/question/a20838968/safe-type-conversions-with-explicit-conversion-operators
- iterator to cons_iterator https://pastebin.com/51GvtVeA 


