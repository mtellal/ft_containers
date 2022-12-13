# How to use

open `tester.sh`
- modify `include="../include/" # path for containers (default in include/ from repo)` var
- or modify ( -I <your_header_folder> ) `flags="-Wall -Wextra -Werror -std=c++98"`

# Commands

- all containers : `./tester.sh` executes tests for all containers (vector-map)
- specific container : `./tester.sh <container>` - example: `./tester.sh vector`
- one file : `./tester.sh <file>` - example: `./tester.sh src/vector/assign.cpp`

# About the tester

The tester tests: ( THE MOST PART OF TESTS CAME FROM https://github.com/mli42/containers_test )
- `compilation` with `flags="-Wall -Wextra -Werror -std=c++98"` flags. Compilations errors are in output/err.
- `time` execution from your container and std::<container>
- `diff` your container output and std::<container> output. Diff can be found in diff/ (and output in output/(ft || std)_<container>_<file_test>.output)
- `leaks` check with allocs > frees and errors (ERROR SUMMARY). Errors are in output/ folder.

![tester](https://user-images.githubusercontent.com/60407248/207082123-4c291799-a591-472d-8b81-dad6bbda6a9d.png)
