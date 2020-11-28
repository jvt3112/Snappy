//CREATE
/* 
    The role of this function is to create the snaphot of
    the directory sprcified

    Usage: create [Directory]
    Usage: create [Directory] -d [Description.....]

    function details: creates a first copy of snap shot 
    and then for any subsequent snapshot hard link is created
    for the files that is not changed and a copy is created 
    if file is changed.

*/

void new_snap(char* src,char* dest,char* lastSnap,time_t lmt, FILE* Fp){

    DIR* dp;
    struct dirent* d;
    struct stat sb;
    if ((dp = opendir(src)) == NULL){

        // failed to open directory
        fprintf(stderr, "%s: %s\n", src,strerror(errno));
        exit(1);
    }
    char* filePathSrc;
    char* filePathDest;
    char* filePathLast;
    ssize_t size;
    char* filename;
    char* parent;
    time_t ts;
    int upd,res;

    //enter into the directory
    while ((d = readdir(dp)) != NULL){
        filename = d->d_name;
        if (filename[0]!='.'){

            //length of filename
            size = strlen(filename)+strlen(src)+2; 

            //initialising memory to store path
            filePathSrc = malloc(size*sizeof(char));
            strcpy(filePathSrc, "");
            strcat(filePathSrc,src);
            strcat(filePathSrc,"/");
            strcat(filePathSrc, filename);
            
            size = strlen(filename)+strlen(dest)+2;
            
            //initialising memory to store path
            filePathDest = malloc(size*sizeof(char));
            strcpy(filePathDest, "");
            strcat(filePathDest,dest);
            strcat(filePathDest,"/");
            strcat(filePathDest, filename);
            size = strlen(filename)+strlen(lastSnap)+2;

            //initialising memory to store path
            filePathLast = malloc(size*sizeof(char));
            strcpy(filePathLast, "");
            strcat(filePathLast,lastSnap);
            strcat(filePathLast,"/");
            strcat(filePathLast, filename);
            
            if (stat(filePathSrc, &sb) == -1){
                // stat failed on the given path
                fprintf(stderr, "%s: %s\n", filePathSrc,strerror(errno));
                exit(1);
            }
            //modified time
            ts = sb.st_mtime;
            if (ts>lmt){
                upd = 0;
            }
            else{
                upd = 1;
            }
            if (upd == 1){
                
                //checkhs for file or directory
                if (S_ISDIR(sb.st_mode)){
                    res = mkdir(filePathDest,permission);
                    new_snap(filePathSrc,filePathDest,filePathLast, lmt,Fp);
                }
                else if (S_ISREG(sb.st_mode)){

                    //creates the hard link
                    res = link(filePathLast,filePathDest);
                    if (res == -1){
                        fprintf(stderr, "%s\n",strerror(errno));
                        exit(1);
                    }
                }
            }
            else{
                
                //checks for directory or file
                if (S_ISDIR(sb.st_mode)){
                    res = mkdir(filePathDest,permission);
                    new_snap(filePathSrc,filePathDest,filePathLast, lmt,Fp);
                }
                else if (S_ISREG(sb.st_mode)){
                    cp(filePathSrc,filePathDest);

                    //if file changes logs into the file 
                    //about the status of file
                    fputs("-->",Fp);
                    fputs(filePathSrc,Fp);
                    fputs(": Changed\n",Fp);
                }
            }

            //free the memory
            free(filePathSrc);
            free(filePathDest);
            free(filePathLast);
            filePathSrc = NULL;
            filePathDest = NULL;
            filePathLast = NULL;         
        }
    }
    closedir(dp);
}

void snap_create(char* src, char** args){
    size_t size;
    char* name = basename(src);
    char* snapid = nametoNum(src); 
    size = strlen(snap_path) + strlen(snapid) + 2;

    //initialising memory to store path
    char* pathDir = malloc(size*sizeof(char));
    strcpy(pathDir, "");
    strcat(pathDir, snap_path);
    strcat(pathDir,"/");
    strcat(pathDir, snapid);
    
    //creating new directory
    int res, id;
    res = mkdir(pathDir, permission);
    if (res == -1 && errno!=EEXIST){
        fprintf(stderr, "Directory creation failed at %s : %s", pathDir, strerror(errno));
        exit(1);
    }
    
    //getting the nextSnap
    id = getNextSnap(pathDir);
    
    char indexId[3];
    sprintf(indexId,"%d",id);
    char num[3];
    sprintf(num,"%d",id);
    char dirnameDest[10] = "Snapshot";
    strcat(dirnameDest, num);
    size = strlen(pathDir) + strlen(dirnameDest) + 2;

    //initialising memory to store path
    char* pathSnap = malloc(size*sizeof(char));
    strcpy(pathSnap, "");
    strcat(pathSnap, pathDir);
    strcat(pathSnap,"/");
    strcat(pathSnap, dirnameDest);

    //creating new directory
    res = mkdir(pathSnap, permission);
    if (res == -1){
        fprintf(stderr, "Directory creation failed at %s : %s", pathSnap, strerror(errno));
        exit(1);
    }
    
    FILE* Fp;
    size = strlen(pathDir) + 10;

    //initialising memory to store path
    char* logfile = malloc(size*sizeof(char));
    strcpy(logfile, "");
    strcat(logfile,pathDir);
    strcat(logfile,"/");
    strcat(logfile,"log.txt");

    //opening log file in append mode
    Fp = fopen(logfile,"a+");
    if(id!=0){
        size = strlen(pathSnap) + strlen(name) + 2;
        char* dest = malloc(size*sizeof(char));
        strcpy(dest, "");
        strcat(dest,pathSnap);
        strcat(dest,"/");
        strcat(dest, name);

        //creating directory
        res = mkdir(dest, permission);
        if (res == -1){
            fprintf(stderr, "3Directory creation failed at %s : %s", pathSnap, strerror(errno));
            exit(1);
        }
        sprintf(num,"%d",id-1);
        char dirnameLast[10] = "Snapshot";
        strcat(dirnameLast,num);
        size = strlen(pathDir) + strlen(dirnameLast) + 2;

        //initialising memory to store path
        char* last = malloc(size*sizeof(char));
        strcpy(last, "");
        strcat(last,pathDir);
        strcat(last,"/");
        strcat(last, dirnameLast);
        size = strlen(last) + strlen(name) + 2;

        //initialising memory to store path
        char* lastSnap = malloc(size*sizeof(char));
        strcpy(lastSnap, "");
        strcat(lastSnap,last);
        strcat(lastSnap,"/");
        strcat(lastSnap, name);

        //initialising the stat
        struct stat sb;

        if (stat(lastSnap, &sb) == -1){
            // stat failed on the given path
            fprintf(stderr, "1 %s: %s\n", lastSnap,strerror(errno));
            exit(1);
        }

        //tilestamp
        time_t lmt;
        lmt = sb.st_mtime;
        char timestamp[100];
        format_time(timestamp);
        fputs(timestamp,Fp);
        fputs("Snap Created\n",Fp);

        //fucntion call to create new snap
        new_snap(src,dest,lastSnap,lmt,Fp);

        //free the memory
        free(last);
        free(lastSnap);
        free(dest);
        last = NULL;
        lastSnap = NULL;
        dest = NULL;
    }
    else{

        //if created for first time
        cp(src,pathSnap);

        //timestamp
        char timestamp[100];
        format_time(timestamp);
        fputs(timestamp,Fp);

        //writing into the file
        fputs("Snap Created\n",Fp);
    }

    fputs("\n",Fp);
    fclose(Fp);

    //if optional flag is also there then writing 
    //description while creating
    if(args_cnt>2){
        if(strcmp(args[2],"-d")==0){

            //initialising memory to store path
            char** argsM = malloc(snap_arg_bufsize*sizeof(char*));
            char* temp = "desc";
            argsM[0] = temp;
            argsM[1] = indexId;
            argsM[2] = args[1];

            for (int i = 3; args_cnt> i; i++){
                argsM[i] = args[i];
            }
            
            //calling desc function to add desrcption
            snap_description(argsM);
            free(argsM); 
        }
    }

    size = strlen(pathSnap) + strlen(name) + 2;

    //initialising memory to store path
    char* permissionPath = malloc(size*sizeof(char));
    strcpy(permissionPath,pathSnap);
    strcat(permissionPath,"/");
    strcat(permissionPath, name);

    //calling chmod to change permission of all 
    //the files to read only of all the snaps created
    
    char* execarg[5];
    execarg[0]="chmod";
    execarg[1]= "-R";
    execarg[2]= "555";
    execarg[3]=permissionPath;
    execarg[4]=NULL;
    execute(execarg);

    //free the memory
    free(permissionPath);
    free(pathDir);
    free(pathSnap);
    free(logfile);
    free(snapid);
    pathDir = NULL;
    pathSnap = NULL;
    logfile = NULL;
    snapid = NULL;
    permissionPath= NULL;
}