/*
    Utility function to copy the data from one path
    to another recursively.
*/


void cp(char* src, char* dest){

    //initialising stat
    struct stat sb;
    if (stat(src, &sb) == -1){
        // stat failed on the given path
        fprintf(stderr, "ls: stat failed on the path '%s': %s\n", src,strerror(errno));
        exit(1);
    }

    int res = 0;
    if (S_ISDIR(sb.st_mode)){
        res = 1;
    }

    //using inbuilt cp with flag to create copy
    char* execarg[5];
    execarg[0] = "cp";
    execarg[1] = "-r";
    execarg[2] = src;
    execarg[3] = dest;
    execarg[4] = NULL;
    
    //calling execute
    execute(execarg);
}