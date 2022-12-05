#pragma once
#include "../kinderc.hpp"

DynamicObject JSON::Parse(string s) {
	int index = (int)DynamicObject("dp")["push"](String::Format("JSON.parse(`%s`)", s.CharArray)) - 1;
	return DynamicObject(String::Format("dp[%i]", index));
}
string JSON::Build(JSONBuilder bldr, bool pretty) {
	string json = "{";
	if(pretty) json += "\n";
	for(int i = 0; i < 32; i++) {
		if(pretty) json += "\t";
		json += (char*)string::Format("\"%s\" : \"%s\"", (char*)bldr.matrix[i][0], (char*)bldr.matrix[i][1]);
		if(bldr.matrix[i + 1][0] != "") {
			json += ",";
			if(pretty) json += "\n";
		} else break;
	}
	if(pretty) json += "\n";
	json += "}";
	return json;
}