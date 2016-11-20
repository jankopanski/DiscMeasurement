#ifndef DISCMEASUREMENT_FILEREADER_H
#define DISCMEASUREMENT_FILEREADER_H


#include <string>
#include <vector>

class FileReader {
protected:
    int fd;
    size_t file_size;
    size_t block_size;
    char * buf;

public:
    class FileReaderException : std::exception { };

    FileReader(std::string path, size_t block_size, bool is_buffered);

    ~FileReader() {
        free(buf);
    }

    virtual ssize_t read_block() = 0;

    virtual size_t size() {
        return file_size;
    }
};

class SequentialFileReader : public FileReader {
public:
    using FileReader::FileReader;

    virtual ssize_t read_block();
};

class RandomAccessFileReader : public FileReader {
private:
    std::vector<unsigned> perm;
public:
    RandomAccessFileReader(std::string path, size_t block_size, bool is_buffered);

    virtual ssize_t read_block();
};

#endif //DISCMEASUREMENT_FILEREADER_H
