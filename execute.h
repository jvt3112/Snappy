/*
	Utility function used to call inbuilt commands
*/
void execute(char **arg){
	pid_t cpid;
	int status;
	cpid = fork();
	if(cpid == 0){

		//this execute the binary inbuilt function by replacing current process with new process
		if(execvp(arg[0], arg) < 0)  
		printf("snap: command not found: %s\n", arg[0]);
		exit(EXIT_FAILURE);
	}

	//if error forking the process
	else if(cpid < 0)   
		printf("Error forking \n");   
	else{
		//the flag WUNTRACED ensures that parent process until the 
		//child process is completed, ensuring determinism
		waitpid(cpid, &status, WUNTRACED);  
	}
}