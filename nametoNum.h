/*
  Utility function that cchecks in config.csv 
  for the path of the directory, if exists returns
  the number. If does't then adds new path to
  config file
*/

#define debug printf("Yeah\n");
#define   LOCK_EX   2    /* exclusive lock */
#define   LOCK_UN   8

//gets the index of source form the line
int getIndex(char* src){
  int i = 0;
  while(src[i]!='\0'){
    if (src[i] == ','){
      return i;
    }
    i++;
  }
}

//gets the prefix of src path- here number
void getPrefix(char* src, int index, char* prefix){
  for (int i =0; index>i;i++){
    prefix[i] = src[i];
  }
}

//gets the suffix of src path- here the path
void getSuffix(char* src, int index, char* suffix){
  
  int i=index +1;
  int j = 0;
  while(src[i]!='\0'){
    suffix[j] = src[i];
    i++;
    j++;
  }
}


char* entry(char* src,char* path){

  int fd, res;

  //open the config.csv file in storage folder
  fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  char c;
  char line[1024];
  memset(line,'\0', 1024);
  int pos;

  //initialising the memory to store the path
  char* suffix = (char*)malloc(sizeof(char)*1024);
  char* prefix = (char*)malloc(sizeof(char)*1024);
  char* Num = (char*)malloc(sizeof(char)*1024);

  int lines = 0;
  res = read(fd,&c,1);

  //memsetting- fills memory with the constant bytes
  memset(line,'\0', 1024);
  memset(suffix,'\0', 1024);
  memset(prefix,'\0', 1024);

  //checking in the file for the path's existence
  while(res>0){
    if (c=='\n'){
      lines++;

      if (strlen(line)){
        pos = getIndex(line);
        getSuffix(line,pos,suffix);
        getPrefix(line,pos,prefix);
        
        //compares the suffix with the src
        if (strcmp(suffix,src)==0){
          close(fd);

          //free memory
          free(Num);
          free(suffix);
          Num = NULL;
          suffix = NULL;

          return prefix;
        }
      }

      //memsetting- fills memory with the constant bytes
      memset(line,'\0', 1024);
      memset(suffix,'\0', 1024);
      memset(prefix,'\0', 1024);
      res = read(fd,&c,1);
    }
    else{
      strncat(line,&c,1);
      res = read(fd,&c,1);
    }
  }

  //if not found in config file creates new entry
  lines++;
  sprintf(Num,"%d",lines);

  //locking the file so that multiple users so not access at same time
  int filelock, fileunlock;

  //LOCK file
  filelock = flock(fd, LOCK_EX);

  //writing into the file
  write(fd, Num, strlen(Num));
  write(fd, ",", 1);
  write(fd, src, strlen(src));
  write(fd, "\n", 1);

  //UNLOCK file
  fileunlock = flock(fd, LOCK_UN);
  close(fd);

  //freeing memory
  free(prefix);
  free(suffix);
  prefix = NULL;
  suffix = NULL;
  
  return Num;
}

//main function that need to called
char* nametoNum(char* args){

  //initialising buffer for path
  char buffer[1024];

  //gets the real path of the directory
  realpath(args,buffer);

  //calling another utility fucntion to get number
  char* s = entry(buffer, config_path);

  return s;
}