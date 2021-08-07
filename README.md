# MotionEstimation
### Project Repository for SENG 440 Class on Embedded Systems 
#### Currently our program is optimized and will run on linux based machines. Mac is untested and on Windows there is a stack size problem. 
The user is able to compile all project files with the provided Makefile using the command:
<pre><code>make
</code></pre>
The user may also compile and test the unoptimized project files usingthe command:
<pre><code>make unoptimized
</code></pre>
</code></pre>
or furthermore to clean all executables in the directory, the command:
<pre><code>make clean
</code></pre>
<br/><br/>
Afterwards the user will type the following to run the program:
<pre><code>./main [reference file] [current file]
</code></pre>
If two input files are not handed into the program, then it will return an error
<br/><br/>
There have been testing images provided in the ./testing directory. To use them for running the program, type:
<pre><code>./main testing/[reference file] testing/[current file]
</code></pre>
<br/><br/>
Following the completion of the program, there will be a outputted file called 'Motion Estimation Output.txt' in the current directory which will showcase all of the motion vectors created in out motion estimation process. 