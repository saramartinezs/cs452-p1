# Summary of Project 1 

## Functionality of the Shell
- I have gotten the shell to work well. All given tests are passing. The shell is able to run built-in commands as well as other commands. I was able to create a child process and I was also able to add background processes. 

## Task 3 - Print Version
- To achieve this task, I focused on understanding how the getopt function works. Adding the appropriate code was not difficult. At this point in the project, I was able to get "./myprogram -v" to return "Version 1.0". 

## Task 4 - User Input
- Completing task 4 was also pretty straightforward. I added the provided information into my main.c file. This helped me achieve getting user input through the use of the GNU readline library. 

## Task 5 - Custom Prompt
- I used the man page for getenv to get a basis for what I should do. I first handled what to do if the pointer that getenv() returned was NULL. If this was the case, I knew I wanted give the shell the default prompt of "shell>". If the return value of getenv() was not NULL, then I wanted to set it to value that was passed in. I then finished the get_prompt() function with this in mind. Once I completed that, I began to integrate the get_prompt() function into main.c. After accomplishing this I was able to pass two of the given tests from test-lab.c. 

## Task 6 - Built-in Commands 

-  While I was working on this task, I also implemented most of the lab.c functions, so that I could test out the built-in commands in main.c. A lot of the lab.c functions were simple, but were time consuming for me, since it has been a while since I used C. There were some that I wasn't sure how to implement, such as sh_init. 
- For the `exit` command, I was able to get  `exit` to work, however, I had a harder time with the EOF/ctrl+d part of it. I had to come back to this later on when working on main.c. There, I added an if statement that checked if the command for the shell was null. 
- For the `cd` command, I had to move towards implementing the change_dir() function. For this, I needed to look at the chdir, getenv, getuid, and getpwuid man pages. I added code that first attempts to use getenv("HOME") to obtain the user's home directory. If this returns null, then it falls back onto getuid and getpwuid. The second part of this was trickier for me because I had never used getuid or getpwuid before. However, once I understood how these worked, it made it easier to work on it. Changing into a given directory was much simpler. 
- `pwd` was pretty straightforward and I used getcwd(). 
- For the `history` command, I read about the history library. This is where I found that the function that I need was `history_list()`. I used this to print the out the user's command history. 

## Task 7 - Create a Process
-  I read about and used execvp, fork, and waitpid. One of the most important parts for me to understand was the return value for fork. This helped me with setting things up in main. Once I had that general set up, I added execvp in the child process section and waitpid in the parent process section. 

## Task 8 - Signals
- For this task, I used some of the code from the "glibc - Initializing the Shell" article. It was added into the sh_init() function that I wasn't sure what to do with earier. This made it so that the shell would ignore the specified signals. Then I went in and set the signals back to the default value for the child process. 

## Task 9 - Background Processes
- For this task, I had to create a job struct that would help me keep track of background jobs. I created some functions: is_background(), add_job(), and check_background_jobs(). The hardest one to implement was check_background_job. These helped to simplify the implementation of main. There, I added to the child process section and parent section of the code. The code that I added allowed for a background job to occur while allowing the shell to still prompt for another command. 

## Task 10 - Jobs command
- I did not have enough time to implement task 10. However, I did start working on it. I wrote a print_jobs() function, but did not have enough time to add it to main. 
 
