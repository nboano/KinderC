#pragma once

unsigned long strlen(const char* str) {
	const char* s;
	for (s = str; *s; ++s) {}
	return(s - str);
}
char* strcat(char* s1, const char* s2)
{
	char* start = s1;
	while (*start != '\0')
		start++;
	while (*s2 != '\0')
		*start++ = *s2++;
	*start = '\0';
	return s1;
}
void strrev(char* str)
{
	int i;
	int j;
	unsigned char a;
	unsigned long len = strlen((const char*)str);
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}
int strcmp(const char* X, const char* Y)
{
	while (*X)
	{
		if (*X != *Y) {
			break;
		}
		X++;
		Y++;
	}
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}
char* strcpy(char* destination, const char* source)
{
	char* ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return ptr;
}
void strcat_c(char* str, char c)
{
	//for (; *str; str++);
	//*str++ = c;
	//*str++ = 0;
	str += strlen(str);
	*str++ = c;
	*str++ = 0;
}
char* strupr(char* string)
{
	for (char* p = string; *p != '\0'; p++)
	{
		if (*p >= 'a' && *p <= 'z')
			*p -= 32;
	}
	return string;
}
char* strlwr(char* string)
{
	for (char* p = string; *p != '\0'; p++)
	{
		if (*p >= 'A' && *p <= 'Z')
			*p += 32;
	}
	return string;
}

char* strtok(char* s, char d)
{
    static char* input = s;
	if(!*input) input = s;
    char* result = (char*)malloc(strlen(input) + 1);
    int i = 0;
    for (; input[i] != '\0'; i++) {
        if (input[i] != d)
            result[i] = input[i];
        else {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
    result[i] = '\0';
    return result;
}

String::String(const char* s) {
	CharArray = (char*)malloc(strlen(s));
	strcpy(CharArray, "");
	strcpy(CharArray, s);
}
String::String(int n) {
	CharArray = (char*)malloc(16);
	strcpy(CharArray, "");
	itoa(n, CharArray, 10);
}
String::~String() {
	free(CharArray);
}
void String::Concat(const char* str) {
	int l = strlen(CharArray) + strlen(str);

	char bf[l];
	strcpy(bf, "");
	strcat(bf, CharArray);
	strcat(bf, str);

	free(CharArray);
	CharArray = (char*)malloc(l);
	strcpy(CharArray, "");
	strcpy(CharArray, bf);
}
void String::Concat(char c) {
	char bf[2];
	strcpy(bf, "");
	strcat_c(bf, c);
	Concat(bf);
}
void String::Copy(const char* str) {
	free(CharArray);
	CharArray = (char*)malloc(strlen(str));
	strcpy(CharArray, "");
	strcpy(CharArray, str);
}
int String::CompareTo(const char* str) {
	return strcmp(CharArray, str);
}
bool String::operator == (const char* str) {
	return CompareTo(str) == 0;
}
bool String::operator!=(const char* str) {
	return CompareTo(str) != 0;
}
void String::operator = (const char* s) {
	Copy(s);
}
void String::operator=(String s) {
	Copy(s.CharArray);
}
String::operator char* () {
	return CharArray;
}
String::operator int() {
	return atoi(CharArray);
}
String::operator const char* () {
	return (const char*)CharArray;
}
String String::operator + (const char* s) {
	int len = strlen(s) + strlen(CharArray);
	char buf[len];
	strcpy(buf, "");
	strcat(buf, CharArray);
	strcat(buf, s);
	return String(buf);
}
String String::operator + (char* s) {
	return operator+((const char*)s);
}
String String::operator + (String s) {
	return operator+((char*)s);
}
void String::operator += (const char* s) { Concat(s); }
void String::operator += (char c) { Concat(c); }
void String::operator += (String s) {Concat((char*)s);}
char String::operator[] (int index) {
	return CharArray[index];
}
String String::Format(const char* fmt, ...) {
	int _sprintf(char* string, const char* fmt, va_list arg);
	va_list arg;
	int length;
	char buffer[strlen(fmt) + 8192];
	va_start(arg, fmt);
	strcpy(buffer, "");
	length = _sprintf(buffer, fmt, arg);
	va_end(arg);
	return String(buffer);
}
String String::ToUpper() {
	String n(CharArray);
	strupr(n);
	return n;
}
String String::ToLower() {
	String n(CharArray);
	strlwr(n);
	return n;
}
bool String::StartsWith(String s) {
	int l = s.Length;
	for(int i = 0; i < l; i++)
		if(CharArray[i] != s[i])
			return false;
	return true;
}
bool String::EndsWith(String s) {
	int sl = strlen(CharArray);
	int l = s.Length;
	for(int i = 0; i < l; i++)
		if(CharArray[sl - l + i] != s[i])
			return false;
	return true;
}
String String::PadLeft(int n, char c) {
	string s = CharArray;
	while (s.Length < n) s = string::Format("%c%s", c, (char*)s);
	return s;
}
String String::PadRight(int n, char c) {
	string s = CharArray;
	while (s.Length < n) s += c;
	return s;
}
String* String::Split(char separator) {
	String tmp = CharArray;
	if(tmp[tmp.Length - 1] != separator) tmp += separator;

	int al = 0;
	int l = strlen(tmp);

	for(int i = 0; i < l; i++)
		if(tmp[i] == separator) al++;
	
	auto result = new String[al + 1];

	char* tk;
	int cnt = 0;

	do
	{
		tk = strtok(tmp, separator);
		result[cnt++] = tk;
		free(tk);
	} while (cnt < al);

	return result;
}
unsigned long String::GetLength() {
	return strlen(CharArray);
}