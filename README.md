# minishell

SUBJECT:

Your shell should:

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

• Not use more than one global variable. Think about it. You will have to explain its purpose.

• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
• Implement redirections:
  ◦ < should redirect input.
  ◦ > should redirect output.
  ◦ << should be given a delimiter, then read the input until a line containing the
    delimiter is seen. However, it doesn’t have to update the history!
  ◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
  ◦ ctrl-C displays a new prompt on a new line.
  ◦ ctrl-D exits the shell.
  ◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
  ◦ echo with option -n
  ◦ cd with only a relative or absolute path
  ◦ pwd with no options
  ◦ export with no options
  ◦ unset with no options
  ◦ env with no options or arguments
  ◦ exit with no options

EXTERNAL FUNCTIONS: (description is not garanteed to be accurate and can change anytime... plus i'm silly)

-------------------------------------------------------------------------------------------------------------------- readline
readline:         Display a message in standard input and read one line from it, RETURNS CHAR *
rl_clear_history: euh
rl_on_new_line:   euh
rl_replace_line:  could be nice if worked lol
rl_redisplay:     euh
add_history:      euh
-------------------------------------------------------------------------------------------------------------------- stdio
printf:           write in standard input, can add in-code variable with the corresponding flag, RETURNS INT
-------------------------------------------------------------------------------------------------------------------- stdlib
malloc:           Allocate memory
free:             Free memory
-------------------------------------------------------------------------------------------------------------------- unistd
write:            write in the corresponding input, 0 is stdin files are between 3 and OPEN_MAX
access:           euh
-------------------------------------------------------------------------------------------------------------------- fnctl
open:             can create a link to a file or create a new file,the first parameter gives the path of the file
                  the second gives the indication of the action you want to apply to it and the third apply a chmod
                  in octal (ex: 0666), RETURNS INT
-------------------------------------------------------------------------------------------------------------------- unistd
read:             modify a string to put BUFFER_SIZE char from a file or stdin, RETURNS INT
-------------------------------------------------------------------------------------------------------------------- fnctl
close:            break a link created with open, RETURNS INT
-------------------------------------------------------------------------------------------------------------------- signal
fork:             create a duplicate of the code below, kinda work like a thread
wait:             stops the process execution until it gets a signal or a threads end
waitpid:          same as wait but until the process corressponding to the pid changes
wait3:            wait but gives intell about the process
wait4:            waitpid but gives intell about the process
signal:           calls the fonction in parameter 2 when gets the corresponding signal of parameter 1
sigaction:        to not mix with sidaction, completely different, it's the same as signal but more complicated and
                  portable, takes a struct in parameter, looks annoying
sigemptyset:      takes the struct sigaction wanna yum and initialize and empty it
sigaddset:        well, you kinda see the point of it if the one above empty it, well it puts a signal in there
kill:             send the given signal to the process corresponding to the pid given
-------------------------------------------------------------------------------------------------------------------- c lib
exit:             stops everything, kinda the hold up meme from Fallout
-------------------------------------------------------------------------------------------------------------------- fnctl
getcwd:           copy the path of the directory you are in a string and, RETURNS IT(CHAR *)
chdir:            change directory, takes path, go path, simple
stat:             gives intell about the file, takes path
lstat:            I didn't get it, says it returns intell 'bout symbolic link need research
fstat:            intell is fd here
unlink:           delete name and possibly the file it refers to from the file system
execve:           execute a program corresponding to the path given
dup:              copy fd and allocate a copy in the lowest ununsed one it finds
dup2:             choose where to allocate the copy
pipe:             wanna chat from one process to another and get ghost ? well pipe is here for ya
-------------------------------------------------------------------------------------------------------------------- dirent
opendir:          The opendir() function opens a directory stream corresponding to
                  the directory name, and returns a pointer to the directory
                  stream.  The stream is positioned at the first entry in the
                  directory. TLDR CTRL+C CTRL+V from MAN
readdir:          well if you are fluent in fnctl, it's the same but with directories
closedir:         close.
-------------------------------------------------------------------------------------------------------------------- string
strerror:         gives the error message corresponding to the number
perror:           basically, yo whats the pb ? 42 ! Ok I guess i have strerror translate for me
-------------------------------------------------------------------------------------------------------------------- unistd
isatty:           is a tty says if fd is terminal (tty is not text to yspeech...)
ttyname:          gives the terminal pid 
ttyslot:          find the slot of the current user's terminal in some file (etc/ttys i think)
ioctl:            lol, https://linuxhint.com/c-ioctl-function-usage/
-------------------------------------------------------------------------------------------------------------------- stdlib
getenv:           get environement variable corresponding to name given, RETURNS CHAR *
-------------------------------------------------------------------------------------------------------------------- termios
tcsetattr:        see ya later i'm done with this shit, i don't get it yet           
tcgetattr:        
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
