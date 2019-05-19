#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


#include <cstdlib>
#include <errno.h> 
#include <cstring>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h> 


#include "../Sem-sv/sv_shm.h"
#include "../Sem-sv/sv_sem.h"

using namespace std;

#define SEMAF_OXIG_NAME "oxig"
#define SEMAF_HIDRO_NAME "hidro"

#define SEMAF_OXIG_POS 0
#define SEMAF_HIDRO_POS 0

void exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    
    printf("%s", result.c_str());
}

void debug(char* message) {

    char sz[1000] = "echo ";
    strcat(sz, message);
    system(sz);
}

void debug_int(int i) {
    char sz[10] = "";
    sprintf(sz, "%d", i);
    debug(sz);
}

void print_state() {
    system("ipcs -s | tail -4 | grep \"^$\" -v | sed \"s/[^ ]* \\([0-9]*\\).*/ipcs -si\\1 | tail -4/\" > debug.sh");
    system("chmod +x debug.sh");
    system("echo ------------------------------------------------");
    system("./debug.sh");
    system("echo ------------------------------------------------");
}
