//
// Created by jan on 19.11.16.
//

#include <iostream>
#include <zconf.h>
#include "Timer.h"
#include "FileReader.h"

#define MB 1048576.0

using namespace std;

int main(int argc, char *argv[]) {
//    string path = string(argv[1]);
    string path = "/home/jan/ClionProjects/DiscMeasurement/dummy";

    {
        Timer t;
        SequentialFileReader fr(path, 8192, false);
        t.start();
        while (fr.read_block());
//        sleep(1);
        t.stop();
        double speed = fr.size() / MB / t.read();
        cout << "File size: " << fr.size() << " Time: " << t.read() << " Read speed: " << speed << endl;
    }

    {
        Timer t;
        RandomAccessFileReader fr(path, 8192, false);
        t.start();
        while (fr.read_block());
//        sleep(1);
        t.stop();
        double speed = fr.size() / MB / t.read();
        cout << "File size: " << fr.size() << " Time: " << t.read() << " Read speed: " << speed << endl;
    }
}