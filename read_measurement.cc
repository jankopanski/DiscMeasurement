//
// Created by jan on 19.11.16.
//

#include <iostream>
#include "Timer.h"
#include "FileReader.h"

#define MB 1048576.0
#define BLOCK_SIZE 8192

using namespace std;

void measure_seq(string path, unsigned blocks, bool is_buffered) {
    Timer t;
    SequentialFileReader fr(path, blocks * BLOCK_SIZE, is_buffered);
    t.start();
    while (fr.read_block());
    t.stop();
    double speed = fr.size() / MB / t.read();
    cout << "Sequential file read" << "\nBlocks: " << blocks << "\nBuffered: " << (is_buffered ? "YES" : "NO") << endl;
    cout << "File size: " << fr.size() << " B\nTime: " << t.read() << " s\nRead speed: " << speed << " MB/s\n" << endl;
}

void measure_rand(string path, unsigned blocks, bool is_buffered) {
    Timer t;
    RandomAccessFileReader fr(path, blocks * BLOCK_SIZE, is_buffered);
    t.start();
    while (fr.read_block());
    t.stop();
    double speed = fr.size() / MB / t.read();
    cout << "Random access file read" << "\nBlocks: " << blocks << "\nBuffered: " << (is_buffered ? "YES" : "NO") << endl;
    cout << "File size: " << fr.size() << " B\nTime: " << t.read() << " s\nRead speed: " << speed << " MB/s\n" << endl;
}

int main(int argc, char *argv[]) {
//    string path = string(argv[1]);
    string path = "/home/jan/ClionProjects/DiscMeasurement/meddummy";

    measure_seq(path, 1, false);
    measure_seq(path, 1, false);
    measure_seq(path, 2, false);
    measure_seq(path, 4, false);
    measure_seq(path, 8, false);
    measure_seq(path, 16, false);
    measure_seq(path, 32, false);
    measure_seq(path, 64, false);
    measure_seq(path, 128, false);
    measure_seq(path, 256, false);
    measure_seq(path, 512, false);
    measure_seq(path, 1024, false);
    measure_rand(path, 1, false);
    measure_rand(path, 1, false);
    measure_rand(path, 2, false);
    measure_rand(path, 4, false);
    measure_rand(path, 8, false);
    measure_rand(path, 16, false);
    measure_rand(path, 32, false);
    measure_rand(path, 64, false);
    measure_rand(path, 128, false);
    measure_rand(path, 256, false);
    measure_rand(path, 512, false);
    measure_rand(path, 1024, false);
    measure_seq(path, 1, true);
    measure_seq(path, 1, true);
    measure_seq(path, 2, true);
    measure_seq(path, 4, true);
    measure_seq(path, 8, true);
    measure_seq(path, 16, true);
    measure_seq(path, 32, true);
    measure_seq(path, 64, true);
    measure_seq(path, 128, true);
    measure_seq(path, 256, true);
    measure_seq(path, 512, true);
    measure_seq(path, 1024, true);
    measure_rand(path, 1, true);
    measure_rand(path, 1, true);
    measure_rand(path, 2, true);
    measure_rand(path, 4, true);
    measure_rand(path, 8, true);
    measure_rand(path, 16, true);
    measure_rand(path, 32, true);
    measure_rand(path, 64, true);
    measure_rand(path, 128, true);
    measure_rand(path, 256, true);
    measure_rand(path, 512, true);
    measure_rand(path, 1024, true);
}