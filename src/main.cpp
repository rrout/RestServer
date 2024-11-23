#include "Utils.h"

extern int ServerStart();


// Define the main function
int main() {
    //Cfg::certFileName = "server.crt";
    //Cfg::certKeyFileName = "server.key";
    ServerStart();
    return 0;
}