//HELP
/*
  Lists the usage of all the commands that tool is configured for. 
*/

void help(){ 
  printf(" Usage --help\n");
  printf("\n1.create:    -create snapshot of the input directory, optional flag -d to add description\n          -Usage: create [Directory] , create [Directory] -d [Description]\n");
  printf("\n2.revert:     -revert to some older version \n          -Usage: revert [Directory] [SnapNum]\n");
  printf("\n3.cleanup:  -remove all the snapshots and store the snapshot of the latest version\n          -Usage: cleanup [Directory]\n");
  printf("\n4.compare:  -lists the difference between the contents of folder/files\n          -Usage: compare [SnapNum1] [SnapNum2] [Directory]\n");
  printf("\n5.status:     -lists out the modfied or added file in 2 folders\n          -Usage: status -i(optional) [SnapNum1] [SnapNum2] [Directory]\n");
  printf("\n6.delete:   -delete a specific snap of a directory\n          -Usage: delete [Snap_Number] [Directory]\n");
  printf("\n7.listsnap:   - list out the snapshots taken of the directory \n          -Usage: listsnap [Directory]\n");
  printf("\n8.logsnap:     -displays the changes done to the directory\n          -Usage: logsnap [Directory]...\n");
  printf("\n9.desc:  -attach a description to a snapshot\n          -Usage: desc [SnapNum] [Directory] [Description]\n");
}