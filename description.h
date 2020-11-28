//DESCRIPTION
/* 
    The role of this function is to add a description
    to particular snaphot of the directory

    Usage: desc [SnapNum] [Directory] [Description]
    
*/
int snap_description(char** args){
    int n = args_cnt;

    //getting the number to which the directory corresponds
    char* dirname = nametoNum(args[2]);
    size_t size = strlen(snap_path) + strlen(args[2]) + strlen(dirname) + 120;

    //initialising the memory to store path
    char* temp = malloc(size*sizeof(char));
    strcpy(temp,snap_path);
    strcat(temp,"/");
    strcat(temp,dirname);
    strcat(temp,"/");
    strcat(temp, "Snapshot");
    strcat(temp, args[1]);
    strcat(temp,"/");
    strcat(temp,"des.txt");

    //opens the des.txt to the path
    int fd;
    fd = open(temp,O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR );

    //adds time stamp of the description added
    char timestamp[100];
    format_time(timestamp);
    write(fd, timestamp, strlen(timestamp));

    //writing the desc in the file
    for(int j=3; j<args_cnt; j++){
        char* description = args[j]; 
        write(fd, description, strlen(description));
        write(fd, " ", 1);
    }

    write(fd,"\n",1);
    close(fd);
    free(temp);
    free(dirname);
    dirname = NULL;
    temp = NULL;
    return 0;
}