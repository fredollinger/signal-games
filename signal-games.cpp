#include <handle-stop-logging-signal.h>

using namespace csxsig;

int main(){
    mkdir(CSXSIG_LOG_DIR.c_str(), 0777);
    std::string logpath="/media/usb/mylogfile.txt";

    // BEGIN MAKE PATH TO LOG FILE
    FILE *fd;
    fd=fopen(CSXSIG_LOG_PATH.c_str(), "w");
    fprintf(fd,"%s", logpath.c_str());
    fclose(fd);
    // END MAKE PATH TO LOG FILE

    // MAKE ACTUAL LOGFILE
    fd=fopen(logpath.c_str(), "w");
    // Do not close it yet...

    csxsig::handleSignalCloseFile();

    while(true){}
}
