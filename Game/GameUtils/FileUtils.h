#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <istream>
#include <ostream>
#include <sys/stat.h>

namespace Utils
{
    //! Check to see if a file is there
    inline bool isFile(const char* filename)
    {
        std::fstream file;
        file.open(filename);
        bool result = file.is_open();
        if (result == true)
            file.close();
        return result;
    }
    //! Get the size in bytes of a file
    inline unsigned int fileSize(const char* filename)
    {
        struct stat st;
        if (stat(filename, &st) == 0)
            return st.st_size;
        return -1;
    }
}

#endif // FILEUTILS_H
