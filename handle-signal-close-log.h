#ifndef HANDLE_SIGNAL_CLOSE_FILE_H
#define HANDLE_SIGNAL_CLOSE_FILE_H

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace csxsig {

#define CSXSIG_LOG_DIR std::string("/tmp/log")
#define CSXSIG_LOG_FILE std::string("logfile")
#define CSXSIG_LOG_PATH std::string(CSXSIG_LOG_DIR + "/" + CSXSIG_LOG_FILE)

pid_t get_pid_from_proc_self() {
	char target[32];
	int pid;
	readlink("/proc/self", target, sizeof(target));
	sscanf(target, "%d", &pid);
	return (pid_t)pid;
}

static std::string ReadFileAsString(std::string path){
    std::string str="";
    FILE *fd;
    ssize_t bytes=0;
    char buf[BUFSIZ];

    fd=fopen(CSXSIG_LOG_PATH.c_str(), "r");
    while (fgets(buf, sizeof(buf), fd)) { 
	str = str + buf;
    }
    fclose(fd);
    printf("read file: [%s] from [%s] \n", str.c_str(), path.c_str());
    return str;
}

void csx_close_file(const std::string &path) {
    printf("signal close file \n");
    pid_t mypid = get_pid_from_proc_self();
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
    	csx_close_file(logfile);
	fileopen=false;
    }
    else { 
    	csx_open_file(logfile);
	fileopen=true;
    }

    return;
}

void handleSignalCloseFile(){
    signal(SIGUSR2, csx_signal_handler);
    printf("setup\n");
}

} // namespace csxsig

#endif
