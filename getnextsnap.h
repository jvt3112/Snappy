/*
    Utility function to get the next snap number 
    of the snapshot to be taken by checking in the
    storage folder.
*/

int getNextSnap(char* path){

    //initialising dir type for directory
    DIR* dp;
    struct dirent* d;

    if ((dp = opendir(path)) == NULL){
        // failed to open directory
        fprintf(stderr, "ls : cannot open directory '%s': %s\n", path,strerror(errno));
        exit(1);
    }

    int count = 0;
    //counting total number of folder in the path
    while ((d = readdir(dp)) != NULL){
        count++;
    }
    closedir(dp);
    return max(0,count-3);
}