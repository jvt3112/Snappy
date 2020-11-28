//LOGSNAP
/* 
    The role of this function is to open the log.txt
    file for the particular directory.
    Log files contains detailed history of snap 
    creation and changes that happened.

    Usage: logsnap [Directory]

    function details: using inbuit cat to show
    all the content in the file
*/


int snap_log(char** args){
    int n = args_cnt;

    //checking for number of arguments 
    if (n!=2){
        fprintf(stderr, "Invalid Number of Arguements.\n Use snapshot -help for details.\n");
        return 0;
    }
    else{
        
        char* src = args[1];
        size_t size;
        size = strlen(snap_path) + strlen(src) + 2 + strlen("log.txt");

        //initialising memory to store the path
        char* path = malloc(size*sizeof(char));
        strcpy(path,snap_path);
        strcat(path,"/");
        char* snapid = nametoNum(src);
        strcat(path,snapid);
        strcat(path,"/");
        strcat(path,"log.txt");
        
        //using inbuilt cat to show the content of log file for that directory
        char* execarg[3];
        execarg[0] = "cat";
        execarg[1] = path;
        execarg[2] = NULL;
        execute(execarg);

        //free memory
        free(path);
        free(snapid);
        snapid = NULL;
        path = NULL;
    }
    return 0;
}