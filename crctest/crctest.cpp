#include "../libdeflate.h"
#include <stdio.h>
#include <errno.h>
#include <string>
#include <windows.h>

std::string get_file_contents(const char* filename)
{
    std::FILE* fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    throw(errno);
}

int main()
{
    auto RtlComputeCrc32 = (DWORD(NTAPI*)(DWORD dwInitial, const BYTE * pData, INT iLen))(void*)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlComputeCrc32");
    std::string data = get_file_contents("testdata.json");
    unsigned crc32_winapi = RtlComputeCrc32(0, (const BYTE*)data.c_str(), (int)data.size());
    unsigned crc32_libdeflate = libdeflate_crc32(0, data.data(), data.size());
    printf("crc32:%u\n", crc32_winapi);
    if (crc32_winapi == crc32_libdeflate)
        return 0;
    printf("ERROR: libdeflate crc32:%u\n", crc32_libdeflate);
    return 1;
}
