#define _NEW_OVERLOAD_IMPLEMENTATION_


#include "memcheck.h"

// 放在前面 后释放
bool MemCheck::checkStatus = true;
std::unordered_map<void*, MemInfo> MemCheck::_memPool; 
MemCheck MemCheck::memcheck; // memcheck 要放在 mempoll后面

void* operator new(size_t size, const char* file, unsigned long line){
    if (size == 0) size = 1;
    
    void* ptr = malloc(size);
    if (ptr == nullptr) {

    } else {
        // 记录
        MemCheck::setMemInfo(ptr, file, line, size);
    }

    return ptr;
}
void* operator new[](size_t size, const char* file, unsigned long line){
    if (size == 0) size = 1;
    void* ptr = malloc(size);
    if (ptr == nullptr) {
        std::cout << "ERR NEW[]!" << std::endl;
    } else {
        // 记录
        MemCheck::setMemInfo(ptr, file, line, size);
    }
    return ptr;
}

void operator delete(void* ptr){
    MemCheck::deleteMemInfo(ptr);
    
    if (ptr) free(ptr);
}

void operator delete[](void* ptr){
    MemCheck::deleteMemInfo(ptr);

    if (ptr) free(ptr);
}


MemCheck::MemCheck(){
    std::cout << "===============MemCheck constructor======================" << std::endl;
}

MemCheck::~MemCheck(){
    checkStatus = false;
    std::cout << "===================MEMCHECK DESTRUCTOR====================\n";
    if (memcheck._memPool.size() > 0) {
        std::cout << "----------------leak memory info --------------\n";
        for (auto it: memcheck._memPool) {
            std::cout << "Leak Memory Address [" << it.first << "]\n";
            std::cout << "File [" << it.second.file << "] ";
            std::cout << "Line [" << it.second.line << "] ";
            std::cout << "Size [" << it.second.size << "]\n";
        }
        std::cout << "----------------leak memory info --------------\n";
    }
}

void MemCheck::setMemInfo(void* p, const char* file, unsigned long line, unsigned long size){
    if (!checkStatus) return;

    std::cout << "MALLOC " << p << " size= " << size << std::endl;
    MemInfo pInfo(file, line, size);
    memcheck._totalMemSize += size;
    memcheck._memPool[p] = pInfo;
}

void MemCheck::deleteMemInfo(void* p){
    if (!checkStatus) return;

    std::cout << "FREE " << p << std::endl;
    auto pInfo = memcheck._memPool.find(p);
    if (pInfo != memcheck._memPool.end()) {
        memcheck._totalMemSize -= pInfo->second.size;
        memcheck._memPool.erase(pInfo);
    }
}


