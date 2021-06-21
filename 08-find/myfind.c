/*
A simple scaffolding to implement myfind (lab 7)
based on the long_ls example
*/

 #include <stdio.h>
 #include <dirent.h>
 #include <sys/stat.h>
 #include <string.h>
 #include <time.h>

// convert file mode into a printable string
void mode_to_string(int mode, char str[]) {
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0]='d'; // directory?
    if(S_ISCHR(mode)) str[0]='c'; // terminal?
    if(S_ISBLK(mode)) str[0]='b'; // disk?
    if(S_ISLNK(mode)) str[0]='l'; // link?

    if(mode & S_IRUSR) str[1]='r'; // bits for the user
    if(mode & S_IWUSR) str[2]='w';
    if(mode & S_IXUSR) str[3]='x';

    if(mode & S_IRGRP) str[4]='r'; // bits for the group
    if(mode & S_IWGRP) str[5]='w';
    if(mode & S_IXGRP) str[6]='x';

    if(mode & S_IROTH) str[7]='r'; // bits for the others
    if(mode & S_IWOTH) str[8]='w';
    if(mode & S_IXOTH) str[9]='x';
}

// display stat information for a single file
void show_dir_entry(char *dir_entry_name, struct stat *info) {
    char modestring[11];
    mode_to_string(info->st_mode, modestring);
    printf("%s ", modestring);
    printf("%4d ", (int)info->st_nlink);
    printf("%8d ", (int)info->st_size);
    printf("%.20s", ctime(&info->st_mtim.tv_sec));
    printf("%s\n", dir_entry_name); 
}


// a simple wrapper around stat() for error checking and printing file info
// this function is called for every encountered directory entry
void process_entry(char *dir_entry_name) {
    struct stat info;
    if(stat(dir_entry_name, &info)==-1)
        perror(dir_entry_name);
    else {
        if(S_ISDIR(info.st_mode)){
            printf("%s is a directory\n", dir_entry_name);
            //do_find(dir_entry_name);
        }
        if(1)  { //strstr(...) 
            printf("Directory entry: %s\n", dir_entry_name);
            //show_dir_entry(dir_entry_name, &info);
        }
    }
}

// explore all entries of the given directory
void do_find(char *dir_name) {
    DIR *dir_ptr;               // pointer to a directory structure
    struct dirent *dirent_ptr;  // pointer to the current directory entry
    dir_ptr = opendir(dir_name);
    if(dir_ptr==0) {            // opendir could fail, possibly because
        perror(dir_name);       // the directory does not exist
    }
    else {                      // iterate over all directory entries
        while((dirent_ptr=readdir(dir_ptr)) != 0) {
            process_entry(dirent_ptr->d_name);
        }
        closedir(dir_ptr);
    }
}

int main() {
    do_find(".");                 // explore the contents of the current directory
    return 0;
}
