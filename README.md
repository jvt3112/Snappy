# Snappy

In computer systems, a snapshot is the state of a system at a particular point in time. Snappy is a command line tool for linux file system that supports snapshot management. It provides user various functionalities to create,delete and manage the snapshots of the directories.
For more information refer : Report. 
- - - -
## Installation
1. Clone the repository
2. Inside Local Repository Run ```$ make ```
- - - -
## Following commands are supported by Snappy:
1. help: show supported commands and their usage
    - Usage: ```$ help```
    
1. create: create snapshot of the input directory, optional flag -d to add description
    - Usage: ```$ create [Directory]```
    - Usage: ```$ create [Directory] -d [Description]```

2. revert: revert to some older version
    - Usage: ```$ revert [Directory] [SnapNum]```

3. cleanup: remove all the snapshots and store the snapshot of the latest version       
    - Usage: ```$ cleanup [Directory]```

4. compare: lists the difference between the contents of folder/files 
    - Usage: ```$ compare [SnapNum1] [SnapNum2] [Directory]```

5. status: lists out the modified or added file in 2 folders, flag -i for including identical files       
    - Usage: ```$ status -i(optional) [SnapNum1] [SnapNum2] [Directory]```

6. delete: delete a specific snap of a directory
    - Usage: ```$ delete [Snap_Number] [Directory]```

7. listsnap: list out the snapshots taken of the directory 
    - Usage: ```$ listsnap [Directory]```

8. logsnap: displays the changes done to the directory
    - Usage: ```$ logsnap [Directory]```

9. desc: attach a description to a snapshot
    - Usage: ```$ desc [SnapNum] [Directory] [Description]```
- - - -
## Contributors
[Aishna Agrawal](https://github.com/aishna-agrawal) | [Janvi Thakkar](https://github.com/jvt3112) | [Mihir Jain](https://github.com/mihirjain-iitgn) | [Priyam Tongia](https://github.com/Priyam1418)
- - - -
