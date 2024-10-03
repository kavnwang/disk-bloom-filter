#include "MurmurHash3.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "file-handler.cpp"

using namespace std;

#define BYTE_SIZE 8
#define FILTER_SIZE 4096

class BloomFilter
{
    public:
        BloomFilter(string filename, uint64_t max_element_count, double error)
        {
            this->max_element_count = max_element_count;
            this->filename = filename;
            this->size = ceil(-1 * log(error) * max_element_count / (double) (log(2) * log(2)));
            this->hash_count = ceil(-1 * log(error)/log(2));
            this->filter_count = ceil(this->size / FILTER_SIZE);
            this->element_count = 0;
            this->file_handler = new FileHandler(filename, size);
            //cout << size << endl;
            this->filter_hash = rand();
            for (int i = 0; i < this->hash_count; i++) {
                uint32_t hash = rand();
                this->hashes.push_back(hash);
            }
        }
        ~BloomFilter()
        {
            delete this->file_handler;
        }
        void Add(string key) 
        {
            uint64_t filter_num = this->GetFilter(key);
            vector<uint32_t> indexes = this->GetIndexes(key);
            if(this->file_handler->Write(filter_num, filter_size, filter_count, indexes)) {
                this->element_count += 1;
            };
        };
        bool Contains(string key)
        {
            uint64_t filter_num = this->GetFilter(key);
            vector<uint32_t> indexes = this->GetIndexes(key);
            return file_handler->Read(filter_num, filter_size, filter_count, indexes);
        };

        uint32_t GetFilter(string key) {
            uint32_t hash;
            MurmurHash3_x86_32(key.c_str(), key.length(), this->filter_hash, &hash);
            uint64_t filter_num = hash % this->filter_count;
            return filter_num;
        }
        vector<uint32_t> GetIndexes(string key) {
            vector<uint32_t> indexes;
            for(int i = 0; i<this->hash_count; i++) {
                uint32_t index_hash;
                MurmurHash3_x86_32(key.c_str(), key.length(), this->hashes[i], &index_hash);
                uint32_t index = index_hash % this->filter_size;
                indexes.push_back(index);
            }
            return indexes;
        }
        uint64_t Size()
        {
            return this->size;
        };
        uint64_t Count()
        {
            return this->element_count;
        };
        void Clear()
        {
            this->size = 0;
            this->file_handler->Clear();
        };
    private:
        uint64_t size;
        uint64_t element_count;
        uint32_t filter_size = FILTER_SIZE; //can vary depending on machine
        uint64_t max_element_count;
        uint64_t hash_count;
        uint64_t filter_count;
        string filename;
        FileHandler* file_handler;
        vector<uint32_t> hashes;
        uint32_t filter_hash;
};