#include <iostream>
#include <chrono>
#include <unistd.h>
//#include <bits/fcntl-linux.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>
#include <malloc.h>
#include "Timer.h"
#include "FileReader.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
//    chrono::system_clock::time_point t1 = chrono::system_clock::now();
//    sleep(1);
//    chrono::system_clock::time_point t2 = chrono::system_clock::now();
//    chrono::duration<long double> d = t2 - t1;
//    long double dd = d.count();
//    cout << d.count() << endl;
//    Timer t;
//    t.start();
//    sleep(1);
//    t.stop();
//    cout << t.read() << endl;

//    string s = "/home/jan/Pulpit/tmp.txt";
////    int fd = open(s.c_str(), O_RDWR);
//    FileReader fr(s, true);

//    int t[] = {1,2,3,4,5};
//    random_shuffle(t, t+5);

    string path = "/home/jan/ClionProjects/DiscMeasurement/dummy";
    int fd = open(path.c_str(), O_RDONLY | O_DIRECT/* | O_SYNC*/);
//    char buf[8192];
    char *buf = (char*) pvalloc(8192);
//    memalign();
    ssize_t bytes;
    bytes = read(fd, buf, 8192);
    cout << bytes << endl;
    cout << buf << endl;
//    while((bytes = read(fd, buf, 8192))) {
//        cout << bytes << endl;
//        cout << buf << endl;
//    }

    return 0;
}