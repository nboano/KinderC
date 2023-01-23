#pragma once
#include "../kinderc.hpp"

#define LITERALIZE(txt) #txt

/// @brief Formats a given string.
#define fmt(txt, ...) formathelper(LITERALIZE(txt), {{__VA_ARGS__}})

/// @brief Formats a given string.
#define fmtl(txt, ...) formathelper(txt, {{__VA_ARGS__}})

#define expr(expr) #expr, expr

struct fmtargs {
    const char* v[32][2];
};

const char* formathelper(const char* base, struct fmtargs f = {}) {
    string s = "";
    int l = strlen(base);
    for (int i = 0; i < l; i++)
    {
        if(base[i] != '{')
            s += base[i];
        else {
            i++;
            char bf[128] = "";
            while(base[i] != '}') {
                strcat_c(bf, base[i++]);
            }
            int j = 0;
            while(f.v[j][0])
            {
                if(strcmp(f.v[j][0], bf) == 0) {
                    s += f.v[j][1];
                    break;
                }
                j++;
            }
            
        }
    }
    return s;
}