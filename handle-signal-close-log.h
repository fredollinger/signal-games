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

static std::string ReadFileAsString(std::string logpath){
    std::string str="";
    return str;
}

void csx_signal_handler(int signal){
    printf("sig\n");
    std::string logfile=ReadFileAsString(CSXSIG_LOG_PATH);
}

void handleSignalCloseFile(){
    signal(SIGUSR2, csx_signal_handler);
    printf("setup\n");
}

} // namespace csxsig

#endif
