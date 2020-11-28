//REVERT
/* 
    The role of this function is to revert the original
    folder to specific snap number.

    Usage: revert [SnapNum] [Directory]

    function details: deleting the original data folder
    and copying the current snap
*/

//Gets Parent of the snap
char* GetParent(char* str){
    int i = 0, pos = -1;
    while (str[i]!='\0'){
        if (str[i]=='/') pos = i;
        i++;
    }
    str[pos] = '\0';
    return str;
}

//checks the snap
int CheckSnap(char* path){
    struct stat sb;
    if (stat(path,&sb)==-1){
        return 0;
    }
    return 1;
}

int snap_revert(char** args){
    int n = args_cnt;

    //checks for the number of arguments
    if (n!=3){
        fprintf(stderr, "Missing Arguements\n");
        exit(0);
    }
    else{
        char* dest = args[1];
        char temp[255];

        //gets the realpath
        realpath(dest,temp);
        char* SnapNum = args[2];
        char* dirname = basename(dest);
        char* path;
        size_t size = strlen(snap_path) + strlen(dirname) + strlen(SnapNum) + 20;

        //initialising memory to store the path
        path = malloc(size*sizeof(char));
        char * snapid = nametoNum(dest);
        strcpy(path,snap_path);
        strcat(path, "/");
        strcat(path,snapid); 
        strcat(path, "/");
        strcat(path,"Snapshot");
        strcat(path,SnapNum);
        strcat(path, "/");
        strcat(path,dirname);

        //checks the snaps existence
        int res = CheckSnap(path);
        if (res == 0){
            fprintf(stderr, "There does not exist a Snapshot %s for %s\n", SnapNum, dest);
            exit(0);
        }

        char* parentdir3 = GetParent(temp);
        
        //calling execute to delte the original directory
        char* execarg[4];
        execarg[3]=NULL;
        execarg[0] = "rm";
        execarg[1] = "-r";
        execarg[2] = args[1];
        execute(execarg);

        //copies the snap to the original location
        cp(path, parentdir3);

        //changing the permission of the original folder 
        //as by default permission of snapshot is read only
        char* execarg2[5];
        execarg2[0]="chmod";
        execarg2[1]= "-R";
        execarg2[2]= "777";
        execarg2[3]=parentdir3;
        execarg2[4]=NULL;

        //calling inbuilt chmod
        execute(execarg2);

        //free memory
        free(path);
        free(snapid);
        path = NULL;
        snapid = NULL;
    }
    return 0;
}