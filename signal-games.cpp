#include <handle-signal-close-log.h>

using namespace csxsig;

int main(){
    mkdir(CSXSIG_LOG_DIR.c_str(), 0777);
    std::string logpath=CSXSIG_LOG_DIR+"/mylogfile.txt";
    int fd=creat(logpath.c_str(), 0777);
    close(fd);
    csxsig::handleSignalCloseFile();
    while(true){
    }
}
