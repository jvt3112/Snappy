//DELETE
/* 
    The role of this function is to delete specific snap
    of the directory specified

    Usage: delete [SnapNum] [Directory]

    function details: using inbuit rm to delete the snap.
    And renaming all the old snap with new snaphot number
    (i.e. shifitng by 1 digit if any) 
*/


void snap_delete(char** args){
    
    //using inbuilt rm to delete the snap
    char* execarg[5];
    execarg[4] = NULL;
    execarg[0] = "sudo";
    execarg[1] = "rm";
    execarg[2] = "-r";

    //initialising the memory to store path
    char* path = malloc(snap_cmd_bufsize*sizeof(char));
    char* snapid = nametoNum(args[args_cnt-1]);
    strcpy(path,snap_path);
    strcat(path,"/");
    strcat(path,snapid);

    int count = getNextSnap(path)-1;
    strcat(path,"/");
    strcat(path,"Snapshot");

    int i=atoi(args[1]);

    //initialising the memory to store path
    char* dirname = malloc(snap_cmd_bufsize*sizeof(char));

    while (i<=count)
    {   
        strcpy(dirname,path);

        if(i==atoi(args[1])){
            strcat(dirname,args[1]);
            execarg[3] = dirname;

            //calling execute function
            execute(execarg);
        }
        else{
            //initialising the memory to store path
            char* newname = malloc(snap_cmd_bufsize*sizeof(char));
            char* id = malloc(snap_arg_bufsize*sizeof(char));

            strcpy(newname,dirname);
            sprintf(id,"%d",i);
            strcat(dirname,id);
            sprintf(id,"%d",i-1);
            strcat(newname,id);

            //renaming the files
            rename(dirname,newname);

            //free memory
            free(newname);
            free(id);
            newname = NULL;
            id = NULL;
        }
        i++;
    }

    //free memory
    free(path);
    free(snapid);
    free(dirname);
    path = NULL;
    snapid = NULL;
    dirname = NULL;
}

