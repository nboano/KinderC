#pragma once
#include "../JSON.Parser.hpp"

const char* Implementations::JSON::Parser::Helpers::GetFieldName(char*& chptr) {
    string fname = "";

    while (*chptr++ != '"')
        ;

    do
        fname += *chptr;
    while (*++chptr != '"');

    return fname;
}

const char* Implementations::JSON::Parser::Helpers::GetFieldValue(char*& chptr) {
    string fvalue = "";

    int n_apici = 0, n_quadre = 0, n_graffe = 0;

    do
    {
        switch (*chptr)
        {
            case '"':
                n_apici++;
                break;
            case '{':
            case '}':
                n_graffe++;
                break;
            case '[':
            case ']':
                n_graffe++;
                break;
        }
        fvalue += *chptr;
        chptr++;
    } while (
        *chptr != ',' ||
        n_apici % 2 != 0 ||
        n_quadre % 2 != 0 ||
        n_graffe % 2 != 0
    );
    
    chptr++;

    return fvalue;
}

void Implementations::JSON::Parser::Helpers::GetSeparator(char*& chptr) {
    while(*chptr++ != ':');
}

void Implementations::JSON::Parser::Helpers::TypiseObject(::JSON::Object flist) {
    for (int i = 0; i < flist.Count; i++)
    {
        char* cval = flist[i].Value;

        // Mi porto al primo carattere utile del campo.
        while(*cval == ' ' || *cval == '\n' || *cval == '\r' || *cval == '\t') cval++;

        char chid = *cval;

        switch (chid)
        {
        case '"':
            cval++;
            for (int i = 0; i < strlen(cval); i++)
                if(cval[i] == '"') {
                    cval[i] = 0;
                    break;
                }
            flist.SetValueAt(i, {flist[i].Key, cval});
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-': {
            bool f = false;
            for (int i = 0; i < strlen(cval); i++)
            {
                if(cval[i] == '.') {
                    f = true;
                    break;
                } else if(cval[i] == ' ' || cval[i] == '\n' || cval[i] == '\r' || cval[i] == '\t') {
                    cval[i] = 0;
                    break;
                }
            }

            if(f) flist.SetValueAt(i, {flist[i].Key, atof(cval)});
            else  flist.SetValueAt(i, {flist[i].Key, atoi(cval)});

            delete[] cval;
            break;
        }
        case 'n':
            flist.SetValueAt(i, {flist[i].Key, nullptr});

            delete[] cval;
            break;
        default:
            break;
        }
    }
}

void Implementations::JSON::Parser::Helpers::TypiseArray(::JSON::Array flist) {
    for (int i = 0; i < flist.Count; i++)
    {
        char* cval = flist[i];

        // Mi porto al primo carattere utile del campo.
        while(*cval == ' ' || *cval == '\n' || *cval == '\r' || *cval == '\t') cval++;

        char chid = *cval;
        switch (chid)
        {
        case '"':
            cval++;
            for (int i = 0; i < strlen(cval); i++)
                if(cval[i] == '"') {
                    cval[i] = 0;
                    break;
                }
            flist.SetValueAt(i, cval);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-': {
            bool f = false;
            for (int i = 0; i < strlen(cval); i++)
            {
                if(cval[i] == '.') {
                    f = true;
                    break;
                } else if(cval[i] == ' ' || cval[i] == '\n' || cval[i] == '\r' || cval[i] == '\t') {
                    cval[i] = 0;
                    break;
                }
            }

            if(f) flist.SetValueAt(i, atof(cval));
            else  flist.SetValueAt(i, atoi(cval));

            delete[] cval;
            break;
        }
        case 'n':
            flist.SetValueAt(i, nullptr);

            delete[] cval;
            break;
        default:
            break;
        }
    }
}