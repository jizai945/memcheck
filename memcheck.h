#ifndef __MEMCHECK_H__
#define __MEMCHECK_H__
#include <iostream>
#include <unordered_map>

struct MemInfo
{
    MemInfo() = default;
    MemInfo(const char* mFile, unsigned long mLine, unsigned long mSize)
    :file(mFile), line(mLine), size(mSize)
    {
    }
    std::string file;
    unsigned long line;
    unsigned long size;
};

class MemCheck{
private:
    
    static bool checkStatus; // 标识 memcheck被释放
    
    static MemCheck memcheck; 
    static std::unordered_map<void*, MemInfo> _memPool;
    unsigned long _totalMemSize;

public:
    MemCheck();
    ~MemCheck();
    static void setMemInfo(void* p, const char* file, unsigned long line, unsigned long size);
    static void deleteMemInfo(void* p);
};

void* operator new(size_t size, const char* file, unsigned long line);
void* operator new[](size_t size, const char* file, unsigned long line);

void operator delete(void* ptr);
void operator delete[](void* ptr);

#ifndef _NEW_OVERLOAD_IMPLEMENTATION_
#define new new(__FILE__, __LINE__)
#endif

#endif
