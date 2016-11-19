//
// Created by jan on 18.11.16.
//

#include "FileReader.h"

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
//#include <iostream>
#include <algorithm>

FileReader::FileReader(std::string path, size_t block_size, bool is_buffered) : block_size(block_size) {
    int flags = O_RDONLY;
    if (!is_buffered) flags |= O_DIRECT;
    fd = open(path.c_str(), flags);
    if (fd < 0) throw FileReaderException();
    file_size = static_cast<size_t >(lseek(fd, 0, SEEK_END));
    lseek(fd, 0, SEEK_SET);
    buf = (char*) malloc(block_size);
}

ssize_t SequentialFileReader::read_block() {
    ssize_t read_bytes = read(fd, buf, block_size);
    return read_bytes;
}

RandomAccessFileReader::RandomAccessFileReader(std::string path, size_t block_size, bool is_buffered)
        : FileReader(path, block_size, is_buffered) {
    unsigned num = static_cast<unsigned>((file_size + block_size - 1) / block_size); // ceil
    for (unsigned i = 0; i < num; ++i) {
        perm.push_back(i);
    }
    random_shuffle(perm.begin(), perm.end());
}

ssize_t RandomAccessFileReader::read_block() {
    lseek(fd, perm.back() * block_size, SEEK_SET);
    perm.pop_back();
    ssize_t read_bytes = read(fd, buf, block_size);
    return read_bytes;
}