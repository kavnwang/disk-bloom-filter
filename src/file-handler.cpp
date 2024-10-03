#include "MurmurHash3.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/mman.h>   
#include <sys/stat.h>   
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class FileHandler {
    public:
        FileHandler(string filename, uint64_t size)
        {
            this->filename = filename;
            this-> size = size;
        }
        bool Read(uint32_t filter, uint32_t filter_size, uint32_t filter_count, vector<uint32_t> &positions) 
        {   
            uint64_t offset = filter * filter_size;
            int fd = open(this->filename.c_str(), O_RDONLY);
            assert (fd != -1);
            ftruncate(fd, this->size);
            void *map = mmap(0,size, PROT_READ, MAP_SHARED, fd, 0);
            if (map == MAP_FAILED) {
                close(fd);
                cout << ( "Error mapping file") << endl;
                return false;
            }
            bool output = true;
                uint64_t* data = reinterpret_cast<uint64_t*>(map);            
            for(int i = 0;i<positions.size();i++) {
                uint32_t index = positions[i] + offset;
                if((data[index / 64] & (1ULL << (index % 64))) == 0) {
                    output = false;
                    break;
                }
            }
            close(fd);
            return output;
        }
        bool Write(uint32_t filter, uint32_t filter_size, uint32_t filter_count, vector<uint32_t> &positions) 
        {
            uint64_t offset = filter * filter_size;
            int fd = open(this->filename.c_str(), O_RDWR | O_CREAT, 0644);
            assert (fd != -1);
            ftruncate(fd, this->size);
            void *map = mmap(0,this->size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (map == MAP_FAILED) {
                close(fd);
                cout << ("Error mapping file") << endl;
                return false;
            }
            bool output = true;
            uint64_t* data = reinterpret_cast<uint64_t*>(map);
            for(int i = 0;i<positions.size();i++) {
                uint32_t index = positions[i] + offset;
                data[index / 64] |= (1ULL << (index % 64));
            }
            msync(map, size, MS_SYNC);
            munmap(map, this->size);
            close(fd);
            return true;
        }
        ~FileHandler()
        {

        }

        void Clear() 
        {
            int fd = open(this->filename.c_str(), O_RDWR);
            assert (fd != -1);
            ftruncate(fd, 0);
            close(fd);
        }
    private:
        string filename;
        uint64_t size;
};