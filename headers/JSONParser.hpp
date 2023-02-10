#pragma once
#include "../kinderc.hpp"

class JSON::Parser {
static const char* getfieldname(char*& chptr) {
    string fname = "";

    while (*chptr++ != '"')
        ;

    do
        fname += *chptr;
    while (*++chptr != '"');

    return fname;
}

static const char* getfieldvalue(char*& chptr) {
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

static void getseparator(char*& chptr) {
    while(*chptr++ != ':');
}

static void json_fcorrect(JSON::Object flist) {
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

static void json_fcorrect(JSON::Array flist) {
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

public:

static JSON::Object DeserializeObject(const char* str) {
    char* aptr = new char[strlen(str) + 1];
    strcpy(aptr, str);

    // Rimozione } alla fine.
    char* tptr = aptr + strlen(str);
    while(*--tptr != '}');
    *tptr = ',';
    *++tptr = '\0';

    char* chptr = aptr;

    // Rimozione { all'inizio.
    while(*chptr++ != '{');
    *(chptr - 1) = ' ';

    JSON::Object flist;

    do
    {
        const char* t_key = getfieldname(chptr);
        char* key = new char[strlen(t_key) + 1];
        strcpy(key, t_key);

        getseparator(chptr);

        const char* t_val = getfieldvalue(chptr);
        char* val = new char[strlen(t_val) + 1];
        strcpy(val, t_val);

        flist.Add({key, val});

    } while (*chptr != '\0');
    
    delete[] aptr;

    json_fcorrect(flist);


    return flist;
}

static JSON::Array DeserializeArray(const char* str) {
    char* aptr = new char[strlen(str) + 1];
    strcpy(aptr, str);

    // Rimozione ] alla fine.
    char* tptr = aptr + strlen(str);
    while(*--tptr != ']');
    *tptr = ',';
    *++tptr = '\0';

    char* chptr = aptr;

    // Rimozione [ all'inizio.
    while(*chptr++ != '[');
    *(chptr - 1) = ' ';

    JSON::Array flist;

    do
    {
        const char* t_val = getfieldvalue(chptr);
        char* val = new char[strlen(t_val) + 1];
        strcpy(val, t_val);

        flist.Add(val);

    } while (*chptr != '\0');
    
    delete[] aptr;

    json_fcorrect(flist);


    return flist;
}
};




void objdump(JSON::Object flist) {
    printf("<br>");
    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].Value.GetType())
        {
        case JSON::Value::DataType::STRING:
            printf("[%s] => <i>(string)</i> <b>%s</b><br>", flist[i].Key, (const char*)flist[i].Value);
            break;
        case JSON::Value::DataType::INT:
            printf("[%s] => <i>(int)</i> <b>%i</b><br>", flist[i].Key, (int)flist[i].Value);
            break;
        case JSON::Value::DataType::DOUBLE:
            printf("[%s] => <i>(double)</i> <b>%f</b><br>", flist[i].Key, (double)flist[i].Value);
            break;
        case JSON::Value::DataType::OBJECT:
            printf("[%s] => <i>(object)</i><br>", flist[i].Key);
            break;
        case JSON::Value::DataType::ARRAY:
            printf("[%s] => <i>(array)</i><br>", flist[i].Key);
            break;
        case JSON::Value::DataType::NULL_T:
            printf("[%s] => <i>(null)</i><br>", flist[i].Key);
        default:
            break;
        }
    }
    printf("<br>");
}

void objdump(JSON::Array flist) {
    printf("<br>");
    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].GetType())
        {
        case JSON::Value::DataType::STRING:
            printf("[%i] => <i>(string)</i> <b>%s</b><br>", i, (const char*)flist[i]);
            break;
        case JSON::Value::DataType::INT:
            printf("[%i] => <i>(int)</i> <b>%i</b><br>", i, (int)flist[i]);
            break;
        case JSON::Value::DataType::DOUBLE:
            printf("[%i] => <i>(double)</i> <b>%f</b><br>", i, (double)flist[i]);
            break;
        case JSON::Value::DataType::OBJECT:
            printf("[%i] => <i>(object)</i><br>", i);
            break;
        case JSON::Value::DataType::ARRAY:
            printf("[%i] => <i>(array)</i><br>", i);
            break;
        case JSON::Value::DataType::NULL_T:
            printf("[%s] => <i>(null)</i><br>", i);
        default:
            break;
        }
    }
    printf("<br>");
}