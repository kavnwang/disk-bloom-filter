# disk-bloom-filter

I chose to use a hierarchical bloom filter for the task. Because we are constrained to disk operations and use multiple hash functions, each hash function will likely cause each section of flash memory to be entirely rewritten for each bit update, causing writing to be computationally expensive. The hierarchical bloom filter creates multiple bloom filters, each the size of a flash memory unit, and uses hashing to map an element to its corresponding bloom filter. Then, applying k hash functions will only rewrite one or two units of flash memory instead of k units. 

I had the choice between memory-mapped files and RAM buffering to speed up writing. I used memory-mapped files because they felt simpler to implement under time constraints, but RAM buffering seems more optimal for performance.

With more time, I would consider leveraging the L1 cache and computing index bits using fewer hash functions or in parallel. I would implement Bloom constructors from files, batch addition, and batch search.

To run: 
g++ -std=c++11 test.cpp filter.cpp file-handler.cpp MurmurHash3.cpp -o test
./test