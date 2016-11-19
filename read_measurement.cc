//
// Created by jan on 19.11.16.
//

#include <iostream>
#include "Timer.h"
#include "FileReader.h"

using namespace std;

int main(int argc, char *argv[]) {
    string path = string(argv[1]);

    {
        Timer t;
        SequentialFileReader fr(path, 8192, true);
        t.start();
        while (fr.read_block());
        t.stop();
        double speed;
        cout << "File size: " << fr.size() << " Time: " << t.read() << endl;
    }
}