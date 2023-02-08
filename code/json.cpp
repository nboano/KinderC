#pragma once
#include "../kinderc.hpp"

DynamicObject JSON::Parse(string s) {
	int index = (int)DynamicObject("dp")["push"](String::Format("JSON.parse(`%s`)", s.CharArray)) - 1;
	return DynamicObject(String::Format("dp[%i]", index));
}