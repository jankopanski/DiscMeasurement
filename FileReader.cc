#include "FileReader.h"

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <malloc.h>

/*
problem - O_DIRECT

"The thing that has always disturbed me about O_DIRECT is that
the whole interface is just stupid, and was probably designed
by a deranged monkey on some serious mind-controlling
substances."—Linus

http://man7.org/linux/man-pages/man2/open.2.html
http://man7.org/tlpi/code/online/diff/filebuff/direct_read.c.html
http://stackoverflow.com/questions/6001272/how-can-i-read-a-file-with-read-and-o-direct-in-c-on-linux
http://stackoverflow.com/questions/10512987/o-direct-flag-not-working

solution - pvalloc
*/

FileReader::FileReader(std::string path, size_t block_size, bool is_buffered) : block_size(block_size) {
    int flags = O_RDONLY;
    if (!is_buffered) flags |= O_DIRECT;
    fd = open(path.c_str(), flags);
    if (fd < 0) throw FileReaderException();
    file_size = static_cast<size_t >(lseek(fd, 0, SEEK_END));
    lseek(fd, 0, SEEK_SET);
    if (!is_buffered) buf = (char*) pvalloc(block_size);
    else buf = (char*) malloc(block_size);
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
    if (perm.empty()) return 0;
    lseek(fd, perm.back() * block_size, SEEK_SET);
    perm.pop_back();
    ssize_t read_bytes = read(fd, buf, block_size);
    return read_bytes;
}