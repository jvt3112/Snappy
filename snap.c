#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdarg.h>
#include "headers.h"

//our snap tool functions
char *builtin_name[] = {
  "create",
  "cleanup",
  "delete",
  "revert",
  "compare",
  "status",
  "listsnap",
  "logsnap",
  "desc",
  "help"
};

//command line function created
void dec_func(int i, char** args){
   switch(i){
	case 1: snap_create(args[1],args);
		break;
	case 2: snap_cleanup(args);
		break;
	case 3: snap_delete(args);
		break;
	case 4: snap_revert(args);
		break;
	case 5: snap_compare(args);
		break;
	case 6: snap_status(args);
		break;
	case 7: snap_ls(args);
		break;
	case 8: snap_log(args);
		break;
	case 9: snap_description(args);
		break;
	case 10: help();
		break;
	default:
		printf("We will never get here\n");
		break;
	}
}

//main fucntion of tool
int main(int n, char** argv){
  char** args = (char**)malloc((n-1)*sizeof(char*));
  int i = 0;
  int j = 1;

  while (argv[j]!=NULL){
    args[i++] = argv[j++];
  }

  args_cnt = n-1;
  int len = sizeof(builtin_name)/sizeof(char *);

  for (int i = 0; i < len; i++){
    if(!strcmp(args[0], builtin_name[i])){
      dec_func(i+1,args);
    }
  }
  
  //free the memory
  free(args);
  args = NULL;
  return 0;
}