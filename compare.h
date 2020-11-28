//COMPARE
/* 
    The role of this function is to lists the difference of the content of 
    files of two snapshot of particular directory recursively.

    Usage: compare [SnapNum] [SnapNum] [Directory]

    function details: using inbuilt diff and its flag to lists the 
    difference of content of files
*/


int snap_compare(char **args){
    int n = args_cnt;
    //checks for total number of arguments
	if (n!=4){
        fprintf(stderr, "Invalid Number of Arguements.\n Use snapshot -help for details");
        return 0;
    }
    else{
        //using inbuilt diff to compare content of 2 folder
        char* execarg[5];
        execarg[0] = "diff";
        execarg[1] = "-ra";

        //initialising memory to store path
        char* src = malloc(snap_cmd_bufsize*sizeof(char));
        strcpy(src,snap_path);
        strcat(src,"/");
        char* snapid = nametoNum(args[args_cnt-1]);
        strcat(src,snapid);
        strcat(src,"/");
        strcat(src,"Snapshot");

        //initialising memory to store path
        char* src_name =  malloc(snap_cmd_bufsize*sizeof(char));
        char* dest_name =  malloc(snap_cmd_bufsize*sizeof(char));
        strcpy(src_name,src);
        strcat(src_name,args[1]);
        strcpy(dest_name,src);
        strcat(dest_name,args[2]);

        //passing execargs
        execarg[2] = src_name;
        execarg[3] = dest_name;
        execarg[4] = NULL;

        //calling execute function
        execute(execarg);

        //free the memory
        free(src);
        free(src_name);
        free(dest_name);
        free(snapid);
        snapid = NULL;
        src = NULL;
        src_name = NULL;
        dest_name = NULL;
    }
    return 1;
}