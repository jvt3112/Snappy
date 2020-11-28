//CLEANUP
/* 
    The role of this function is to cleanup all the current 
    snapshot of the directory specified and create the latest snapshot 
    of the folder.

    Usage: cleanup [Directory]

    function details: using inbuit rm to delete all the 
    snapshots and creating latest snap by calling snap_create
    fucntion.
*/


void snap_cleanup(char** args){
    //checks for the total number of arguments
    if (args_cnt!=2){
        fprintf(stderr, "Invalid Number of Arguements.\n Use snapshot -help for details");
    }
    else
    {
        //using inbuilt rm to delete all the snapshot in the storage/<folder name>
        char* execarg[5];
        execarg[4] = NULL;
        execarg[0] = "sudo";
        execarg[1] = "rm";
        execarg[2] = "-r";

        //initialising memory to store path
        char* path = malloc(snap_cmd_bufsize*sizeof(char));
        strcpy(path,snap_path);
        strcat(path,"/");
        char* snapid = nametoNum(args[args_cnt-1]);
        strcat(path,snapid);
        execarg[3] = path;

        //calling execute function
        execute(execarg);
        //creating the latest snap after deleting all the old snapshots
        snap_create(args[args_cnt-1],args);

        //free the memory 
        free(path);
        free(snapid);
        path = NULL;
        snapid = NULL;
    }
}