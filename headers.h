#define snap_cmd_bufsize 1024
#define snap_arg_bufsize 1024
#define CYAN 		"\033[0;36m"
#define RESET  		"\e[0m" 
#define RED   		"\033[0;31m"
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// Global Parameters

int args_cnt;
mode_t permission = 0777;
char* snap_path = "/mnt/c/Users/Janvi Thakkar/Desktop/Snappy/storage";
char* config_path = "/mnt/c/Users/Janvi Thakkar/Desktop/Snappy/storage/config.csv";


// Utility Functions
#include "formattime.h"
#include "getnextsnap.h"
#include "execute.h"
#include "cp.h"
#include  "nametoNum.h"
#include "description.h"
#include "create.h"
#include "cleanup.h"
#include "snap_delete.h"
#include "revert.h"
#include "compare.h"
#include "status.h"
#include "listsnap.h"
#include "logsnap.h"
#include "help.h"