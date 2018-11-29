Thursday 29/11

Please update this file when tasks are finished and tested thouroughly. 

What we need to do (in priority order):
*	Handle quotes and backticks in a functioning manner. (Theo is on it)
*	Heredoc to finish that bonus. (Anton)
*	History file. Command history that is saved when shell exits (Pique)
*	What is "proper tabulations management"? (mandatory)
*	The expansion (!$), any number substitues $-sign
*	Dynamic Autocompletion (if we want)


Bonuses that are completed and fully functional:
*	Local variables
*	Line edition (?)


Bonuses that need some more work:
*	Inhibitors (quote removal, how it's parsed, when to expand etc)
*	Back quotes (same issue as inhibitors)
*	Advanced redirections: file output aggregation and heredoc
*	Command History (a history file, ! expansion)?


Test cases with problems. If it is fixed, don'tremove. Just put a checked box:
*	[X]	/bin/ls -laF
*	[]	cd to /nfs. Then type only cd. Error: cd: Bad address
*	[]	"cd -"
*	[]	"foo=bar" in parse_tokens.c
*	[]	create a file with a tab in it. execute: `cat file`. 
*	[]	setenv FOO bar; setenv FOO=baz bar; unsetenv FOO; # should not remove both variables.
*	[X]	in ft_setenv and ft_unsetenv we should call the function create_path_map() after modifying PATH. 
		That means that a function in libft uses a function from the program. Take out env from libft?
*	[]	Setting a variable to something like: "setenv PATH /bin:/usr/bin"  splits argument at :
*	[]	setting a local var, PATH=/bin. 1st: it executes it?
*	[]	local var PATH, this is valid for finding execs.