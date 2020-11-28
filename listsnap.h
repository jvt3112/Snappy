//LISTSNAP 
/* 
    The role of this function is to list all
    the snaps of directory folder that exists
    in the storage with their date and time.

    Usage: listsnap [Directory]

    function details: using stat to get the creation 
    time for specific folder and lists all the snapshots
    in the directory
*/


void ls(char* pathname){

    // prints contents in/at pathname
    struct stat sb, sb1;
    DIR *dp;
    struct tm * timeinfo;

    if (stat(pathname, &sb) == -1){
        // stat failed on the given path
        fprintf(stderr, "ls: stat failed on the path '%s': %s\n", pathname,strerror(errno));
        return;
    }
    size_t size = strlen(pathname) + 257;

    //initialising memory to store filenam
    char* filename = malloc(size*sizeof(char*)); 

    // If the path given is a directory
    if (S_ISDIR(sb.st_mode)) { 
        
        if ((dp = opendir(pathname)) == NULL){
            // failed to open directory
            fprintf(stderr, "ls : cannot open directory '%s': %s\n", pathname,strerror(errno));
            return;
        }

        struct dirent *d;

        // A subsequent error will cause errno to become non-zero.
        errno = 0; 

        // Iterating over all files/directories of the current directory.
        while ((d = readdir(dp)) != NULL) { 
            // not printing the files "." and ".."
            if (d->d_name[0]!='.' && strcmp(d->d_name,"log.txt")){
                fprintf(stderr,"%s : ", d->d_name);
                filename[0] = '\0';
                strcpy(filename, pathname);
                strcat(filename, "/");
                strcat(filename, d->d_name);
                stat(filename, &sb);
                char time[50];
                strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&sb.st_mtime));
                printf("%s\n", time);
            }
        }

        // If errno is non-zero and d is null this means some error occured.
        if (d==NULL && errno!=0){ 
            fprintf(stderr, "ls: cannot read directory '%s': %s\n", pathname,strerror(errno));
            return;
        }
        // closing directory
        closedir(dp); 
    } 
    else {
        // the given path corresponds to a file.
        fprintf(stderr,"%s ", pathname);
    }

    //free memory
    free(filename);
    filename = NULL;
}

void snap_ls(char** args){

    char* src = args[1];
    size_t size;
    size = strlen(snap_path) + strlen(src) + 2;

    //initialising memory to store path
    char* path = malloc(size*sizeof(char));
    char* pathid = nametoNum(src);

    path[0] = '\0';
    strcpy(path,snap_path);
    strcat(path,"/");
    strcat(path,pathid);

    //initialising stat to check for file status
    struct stat sb;
    if (stat(path, &sb) == -1){
        fprintf(stderr, "ls: stat failed on the path '%s': %s\n", src,strerror(errno));
        exit(1);
    }

    //custom ls function call
    ls(path);
    printf("\n");
    
    //free memory
    free(path);
    free(pathid);
    path = NULL;
    pathid = NULL;
}