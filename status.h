//STATUS
/* 
    The role of this function is to lists all the files whose
    content differs of two snapshot of particular directory recursively.

    Usage: status [SnapNum] [SnapNum] [Directory]
    Usage: status -i [SnapNum] [SnapNum] [Directory] 

    function details: using inbuilt diff and its flag to lists all the 
    files that differs. -i flag also allows to list the identical files
*/


int snap_status(char **args){
    int n = args_cnt;
    //checks for total number of arguments
	if (n<4){
        fprintf(stderr, "Invalid Number of Arguements.\n Use snapshot -help for details");
        return 0;
    }
    else{
        //using inbuilt diff to compare content of 2 folder
        char* execarg[5];
        execarg[0] = "diff";
        execarg[1] = "-raq";

        //initialising memory to store path
        char* src = malloc(snap_cmd_bufsize*sizeof(char));
        char* snapid = nametoNum(args[args_cnt-1]);
        strcpy(src,snap_path);
        strcat(src,"/");
        strcat(src, snapid);
        strcat(src,"/");
        strcat(src,"Snapshot");

        //initialising memory to store path
        char* src_name =  malloc(snap_cmd_bufsize*sizeof(char));
        char* dest_name =  malloc(snap_cmd_bufsize*sizeof(char));
        strcpy(src_name,src);
        strcat(src_name,args[args_cnt-3]);
        strcpy(dest_name,src);
        strcat(dest_name,args[args_cnt-2]);

        //passing execargs
        execarg[2] = src_name;
        execarg[3] = dest_name;
        execarg[4] = NULL;

        //if argcount is 5(that is optional flag is included)
        if(n==5){
            if(!strcmp(args[args_cnt-4],"-i")){
                execarg[1] = "-raqs";
            }
        }

        //calling execute function
        execute(execarg);

        //free the memory
        free(src_name);
        free(dest_name);
        free(src);
        free(snapid);
        src_name = NULL;
        dest_name = NULL;
        src = NULL;
        snapid = NULL;
    }
    return 1;
}
