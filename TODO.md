Thursday 29/11

Please update this file when tasks are finished and tested thouroughly. 

For the bonuses, there are some test cases in the correction sheet which should be tried.

What we need to do (in priority order):
*	[X]	Handle quotes and backticks in a functioning manner.
*	[]	Heredoc to finish that bonus.
*	[]	History file. Command history that is saved when shell exits (Pique)
*	[]	What is "proper tabulations management"? (mandatory)
*	[]	The expansion (!$), any number substitues $-sign


Bonuses that are completed and fully functional:
*	Local variables
*	Line edition (?)
*	Dynamic Autocompletion


Bonuses that need some more work:
*	Inhibitors (Almost done, bug fixing)
*	Back quotes (Almost done, bug fixing)
*	Advanced redirections: file output aggregation and heredoc
*	Command History (a history file, ! expansion)?


Test cases with problems. If it is fixed, don'tremove. Just put a checked box:
*	[X]	/bin/ls -laF
*	[X]	in ft_setenv and ft_unsetenv we should call the function create_path_map() after modifying PATH. 
		That means that a function in libft uses a function from the program. Take out env from libft?
*	[X]	cd to /nfs. Then type only cd. Error: cd: Bad address
*	[X]	"cd -"
*	[X]	"foo=bar" in parse_tokens.c
*	[X]	create a file with a tab in it. execute: `cat file`. 
*	[X]	setenv FOO bar; setenv FOO=baz bar; unsetenv FOO; # should not remove both variables.
*	[X]	Setting a variable to something like: "setenv PATH /bin:/usr/bin"  splits argument at :
*	[X]	setting a local var, PATH=/bin. 1st: it executes it?
*	[X]	local var PATH, this is valid for finding execs.
*	[X]	only one space "42sh$> " heap-buffer-overflow.
*	[X]	What should we do with command line arguments? compare to sh.
*	[X]	ctrl-c to kill a running exec kills the shell as well
*	[X]	no reprompt for: "base64 /dev/urandom | head -c 1000". because of mulitple line output?
*	[X]	parser splits words by "," and "=" even though it shouldn't. figure out exactly when to split.
*	[X]	ls; should not be syntax error.
*	[X]	ls '"$foo"'       '"hello"'. Should split $foo and hello into 2 words in the parser.
*	[X]	echo "`echo "result "`". One extra space.
*	[X]	write something, hold delete button. Results in invalid free.
*	[X]	"Il doit etre possible de copier/coller une partie ou toute la ligne de commande avec un raccourcie clavier."
*	[X]	autocompletion of a path. like "/tm" and tab press
*	[X]	ls `echo '$PATH'`
*	[X]	leak caused by push_stack_elem
*	[X]	ls "\foo". problem in strip quotes.
*	[X]	echo ls -l > a
*	[X]	'echo hello'. Should be one token, two atm.
*	[X]	foo=bar. assignments no longer work
*	[X]	"; cat" error message is weird.

Sunday Dec 2nd:
*	[]	execute: ls \ and press enter on prompt. should exec normal ls
*	[]	2>&-
*	[]	with a redirection like 2>&1, 2 gets passed as an argument
*	[]	ls \ ls
*	[]	"echo && ;"
*	[]	deleting a line longer than the window is a bit buggy.
*	[]	echo "hello"| cat -e
*	[]	ls "`echo "ok tis this"`" 2> a (tries to execute ls on the 2)