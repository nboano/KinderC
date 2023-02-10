#pragma once
#include "../kinderc.hpp"

DynamicObject JSON::Parse(string s) {
	int index = (int)DynamicObject("dp")["push"](String::Format("JSON.parse(`%s`)", s.CharArray)) - 1;
	return DynamicObject(String::Format("dp[%i]", index));
}

const char* JSON::Value::GetJSONValue(bool pretty, int tabnumber) {
	switch (type)
	{
		case STRING:
			return String::Format("\"%s\"", value_string);
		case INT:
			return String::Format("%i", value_int);
		case DOUBLE:
			return String::Format("%f", value_double);
		case BOOL:
			return value_bool ? "true" : "false";
		case ARRAY:
		{
			String s = "[";
			for (int i = 0; i < array_count; i++)
			{
				s += value_array[i].GetJSONValue(value_array[i].type == OBJECT ? false : pretty, tabnumber + 1);
				if(i != array_count - 1) s += pretty? ", " : ",";
			}
			s += "]";
			return s;
		}
		case OBJECT:
			return value_object->Serialize(pretty, tabnumber + 1);
		default:
			return "null";
	}
}

JSON::Value::operator int() {
	return value_int;
}
JSON::Value::operator const char*() {
	return value_string;
}
JSON::Value::operator char*() {
	return (char*)value_string;
}
JSON::Value::operator string() {
	return (string)value_string;
}
JSON::Value::operator double() {
	return value_double;
}
JSON::Value::operator Array() {
	// Array a { array_count };
	// for (int i = 0; i < array_count; i++)
	// {
	// 	a[i] = value_array[i];
	// }
	// return a;
	return JSON::Parser::DeserializeArray(value_string);
}
JSON::Value::operator JSON() {
	return *value_object;
}
JSON::Value::operator JSON::Object() {
	return JSON::Parser::DeserializeObject(value_string);
}

JSON::Value::Value(decltype(__nullptr) nul) {type = NULL_T;}
JSON::Value::Value(int n) {value_int = n; type = INT;}
JSON::Value::Value(unsigned int n) {value_int = n; type = INT;}
JSON::Value::Value(const char* s) {value_string = s; type = STRING;}
JSON::Value::Value(char* s) {value_string = s; type = STRING;}
JSON::Value::Value(string s) {value_string = s; type = STRING;}
JSON::Value::Value(double n) {value_double = n; type = DOUBLE;}
JSON::Value::Value(bool b) {value_bool = b; type = BOOL;}
JSON::Value::Value(Array lst) {
	array_count = lst.Count;
	value_array = lst.ToArray();
	type = ARRAY;
}

JSON::Value::Value(JSON* obj) {
	value_object = obj;
	type = OBJECT;
}

JSON::Value::Value(Object flist) {
	value_object = new JSON();
	for (int i = 0; i < flist.Count; i++)
	{
		value_object->Fields.Add(flist[i]);
	}
	type = OBJECT;
}

JSON::Value JSON::operator[](const char* key) {
	for (int i = 0; i < Fields.Count; i++)
		if(strcmp(Fields[i].Key, key) == 0)
			return Fields[i].Value;
	return nullptr;        
}

JSON::JSON(Field f) {
	Fields.Add(f);
}
JSON::JSON() {}

template<typename... Args>
JSON::JSON(Field f, Args... args) {
	Fields.Add(Field(f));
	Fields.Add(args...);
}

string JSON::Serialize(bool pretty, int tabnumber) {
	string s = "{";
	if(pretty) s += "\n";
	for (int i = 0; i < Fields.Count; i++)
	{
		if(pretty) s += String::Format("%s\"%s\" : %s%s", (char*)String("").PadRight(tabnumber, '\t'), Fields[i].Key, Fields[i].Value.GetJSONValue(pretty, tabnumber), i != Fields.Count - 1 ? ",\n" : "");
		else s += String::Format("\"%s\":%s%s", Fields[i].Key, Fields[i].Value.GetJSONValue(pretty, tabnumber), i != Fields.Count - 1 ? "," : "");
	}
	if(pretty)  {
		s += "\n";
		s += String("").PadRight(tabnumber - 1, '\t');
	}
	s += "}";
	return s;
}