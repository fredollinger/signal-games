#ifndef HANDLE_SIGNAL_CLOSE_FILE_H
#define HANDLE_SIGNAL_CLOSE_FILE_H


#include <dirent.h>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace csxsig {

#define CSXSIG_LOG_DIR std::string("/tmp/logs")
#define CSXSIG_LOG_FILE std::string("logpath")
#define CSXSIG_LOG_PATH std::string(CSXSIG_LOG_DIR + "/" + CSXSIG_LOG_FILE)

std::string csx_readlink(std::string const &path) {
	char buff[1024];
	std::string str="";
	ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff) - 1);
	if (len != -1) {
		buff[len] = '\0';
		str=std::string(buff);
	} 
	else
	    std::cout << " error reading: [" << path << "]" << std::endl;
	return str;
}

pid_t get_pid_from_proc_self() {
	char target[32];
	int pid;
	readlink("/proc/self", target, sizeof(target));
	sscanf(target, "%d", &pid);
	return static_cast<pid_t>(pid);
	//return (pid_t)pid;
}

static std::string ReadFileAsString(std::string path){
    std::string str="";
    FILE *fd;
    ssize_t bytes=0;
    char buf[BUFSIZ];
    struct stat sb;

    if (0 != stat(path.c_str(), &sb)){
        printf("path does not exist: [%s] \n", path.c_str());
        return str;
    }

    fd=fopen(CSXSIG_LOG_PATH.c_str(), "r");
    while (fgets(buf, sizeof(buf), fd)) { 
	    str = str + buf;
    }
    fclose(fd);
    printf("read file: [%s] from [%s] \n", str.c_str(), path.c_str());
    return str;
}

void csx_close_file() {
    pid_t mypid = get_pid_from_proc_self();
    std::ostringstream pidstr;
    pidstr << mypid;
    std::string proc="/proc/" + pidstr.str() + "/fd";
    struct dirent *dp;
    static std::string path=std::string("/var/volatile") + ReadFileAsString(CSXSIG_LOG_PATH);
    if (path.size() < 2){
	    std::cout << __PRETTY_FUNCTION__ << " Path invalid (too short). Bailing: [" << path << "]" << std::endl;
        return;
    }
    path.erase(path.find_last_not_of(" \n\r\t")+1);
    //printf("signal close file [%s] \n", path.c_str());

    //int errnum = 0;
    DIR *dirp = opendir(proc.c_str());

    while (dirp) {
        //errnum = 0;
	if ((dp = readdir(dirp)) != NULL) {
	    std::string str = csx_readlink(proc + "/" + std::string(dp->d_name));
	    std::cout << dp->d_name << "->" << str << std::endl;
	    if (0 == path.compare(str)){
	        std::cout << " match: [" << str << "]" << std::endl;
            int pid = atoi(dp->d_name);
            close(pid);
        }
        else 
	        std::cout << "[" << str << "]" << " did not match: [" << path << "]" << std::endl;
	}
	else{
	    closedir(dirp);
	    return;
	}

    } // END while()
    closedir(dirp);

    // 2. in proc, get a list of all open files matching the logfile
    // 3. close them!
}

void csx_open_file(const std::string &path){
    printf("signal open file \n");
}

void csx_signal_handler(int signal){
    static bool fileopen=true;
    static std::string logfile=ReadFileAsString(CSXSIG_LOG_PATH);
    if (fileopen){
    	csx_close_file();
	fileopen=false;
    }
    else { 
    	csx_open_file(logfile);
	fileopen=true;
    }

    return;
}

void handleSignalCloseFile() {
    printf("*************************************************************************************************setup\n");
    struct sigaction sa;
    sa.sa_handler = csx_signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("**************************************************************************************Dying here!!\n");
        exit(1);
    }
} // END handleSignalCloseFile()

} // namespace csxsig

#endif
