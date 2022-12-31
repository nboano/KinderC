#pragma once
#include "../kinderc.hpp"

/// @brief This class wraps the JavaScript File object.
class File : public object {
    public:
    File() {};
    File(string fname) : object(fname) {}

    #ifndef __INTELLISENSE__
    unsigned long get_LastModified();
    unsigned long get_Size();
    string get_Name();
    string get_MimeType();

    __declspec(property(get=get_LastModified)) unsigned long LastModified;
    __declspec(property(get=get_Size)) unsigned long Size;
    __declspec(property(get=get_Name)) string Name;
    __declspec(property(get=get_MimeType)) string MimeType;
    #else

    /// @brief The UNIX timestamp when the file was modified for the last time.
    unsigned long LastModified;

    /// @brief The size of the file, in bytes.
    unsigned long Size;

    /// @brief The file name.
    string Name;

    /// @brief The file MIME type, if available.
    string MimeType;	
    #endif

    /// @brief Asynchronously reads the text of the file.
    /// @param callback A callback for when the file will be read, with a param of type const char* where the text will be stored.
    void ReadAsTextAsync(void(*callback)(const char* data));
};