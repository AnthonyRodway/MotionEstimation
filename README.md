# Motion Estimation
Currently, our program is built to run on Linux-based machines.  

## SAD Implementations
For our project we implemented the SAD algorithm with a few different optimizations in order to evaluate the performance.  

The following files contain their respective implementations:  
* ./sad contains the unoptimized solution  
* ./sad1 contains the Loop Unrolling Implementation 
* ./sad2 contains the Registers Implementation 
* ./sad3 contains the Storing Multiple Pixels in Each Register Implementation 
* ./sad4 contains an extra implementation not covered in the report or compilation/testing scripts

## Using the Makefile
The makefile is written to make compiling the software implementations easier on Linux Machines:
* The basic command `make` will compile the implementations in the sad, sad1, sad2 and sad3 directories.

You may also compile them individually:
* To compile the software implementation in sad: `make basic`
    * the resulting executable is named `sad_executable`
* To compile the software implementation in sad1: `make first`
    * the resulting executable is named `sad_executable1`
* To compile the software implementation in sad2: `make second`
    * the resulting executable is named `sad_executable2`
* To compile the software implementation in sad3: `make third`
    * the resulting executable is named `sad_executable3`

Lastly, if you want to easily remove the executables made from the Makefile. Run `make clean`.

If you want to compile our implementations on a 32-bit ARM machine or on a 64-bit Linux machine with optimization flags, please follow the steps below. 

## Compilation
The user is able to compile the executable running one of the following commands depending on the target system:  
* **32-bit (ARM)**: `arm-linux-gcc -static main.c bmp_parser.c [sad|sad1|sad2|sad3|sad4]/sad.c -o [executable name]`
* **64-bit (Linux)**: `gcc main.c bmp_parser.c [sad|sad1|sad2|sad3|sad4]/sad.c -o [executable name]`

We also recommend testing with optimization flags. For example:  
* **32-bit (ARM)**: `arm-linux-gcc -static -marm -O3 main.c bmp_parser.c [sad|sad1|sad2|sad3|sad4]/sad.c -o [executable name]`  
* **64-bit (Linux)**: `gcc -Os main.c bmp_parser.c [sad|sad1|sad2|sad3|sad4]/sad.c -o [executable name]`

If you would like to compile sad, sad1, sad2, and sad3 with all 7 available optimization flags on arm-linux-gcc (for running on ARM), you can run `./compile_arm-linux-gcc.sh`. Running this script will create 7 directories in each of the SAD implementation folders (sad, sad1, sad2, sad3). These directories are numbered 1, 2, 3, 4, 5, 6, 7. README files in each of these directories include what command was used to compile the executable. We encourage you to check out the script!  

If you would like to do the same for Linux, you can run `./compile_gcc.sh`. Running this script will create 6 directories in each of the SAD implementation folders (sad, sad1, sad2, sad3). These directories are numbered 1, 3, 4, 5, 6, 7, skipping 2 because the second optimization flag is not for Linux (`-march=armv5`).  

Please note that running both these scripts would overwrite each other. We recommend you only run one, and if you want to run the other, delete the directories it created first.  

## Execution
Execute the program by running `./[executable name] [path/to/reference_frame] [path/to/current_frame]`  
You can find some test images in the _testing_ directory.  

### Output
Following the completion of the program, there will be a results file called `output.txt`, which includes all of the motion vectors created in the motion estimation process.  

## Profiling
We have provided a script for profiling and benchmarking the program on a Linux machine. This script is to be run for one implementation at a time, to prevent long runtimes. To run the script, run `./test_local.sh [sad|sad1|sad2|sad3]`.

We have also provided a script for benchmarking on an ARM device (profiling tools not available on the ARM device). To run the script, run `./test_arm.sh [sad|sad1|sad2|sad3]`.  

## Notes
If you have any difficulties running the program, please don't hesitate to reach out to Shea or Anthony.
