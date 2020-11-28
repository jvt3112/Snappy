/*
    Utility function to get the current time to store the
    time of creation for particular snapshot
*/


void format_time(char* output){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime (&rawtime);
    sprintf(output,"Date: %d-%d-%d , Time: %d:%d:%d\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}