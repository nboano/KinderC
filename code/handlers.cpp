#pragma once

#define LAMBDA_MAX_LEN 128

static void(*__lambda_list[LAMBDA_MAX_LEN])(void*);

int __lambda_add(void(*lb)(void*)) {
	static int ctr = -1;
	ctr++;
	if (ctr == LAMBDA_MAX_LEN) ctr = 0;
	__lambda_list[ctr] = lb;
	return ctr;
}

exported void __lambda_call(int index, void* param = 0) {
	__lambda_list[index](param);
}

Handler::Handler(const char* fnname) {
	HandlerFunctionName = fnname;
	LambdaIndex = -1;
}
Handler::Handler(void(*handler)(void*)) {
	LambdaIndex = __lambda_add(handler);
}
Handler::Handler(void(*handler)(HTMLElement&)) {
	LambdaIndex = __lambda_add((void(*)(void*))handler);
}
Handler::Handler(void(*handler)(XMLHttpRequest&)) {
	LambdaIndex = __lambda_add((void(*)(void*))handler);
}
Handler::Handler(void(*handler)(Response&)) {
	LambdaIndex = __lambda_add((void(*)(void*))handler);
}
string Handler::GetWithPointer(void* ptr, bool function) {
	if (LambdaIndex < 0)
		return String::Format(function ? "()=>%s(%i)" : "%s(%i)", HandlerFunctionName.CharArray, (int)ptr);
	else return String::Format(function ? "()=>__lambda_call(%i,%i)" : "__lambda_call(%i,%i)", LambdaIndex, ptr);
}

void screen_handle_change(void* = 0) {
	$$("screen").style["display"] = "none";
    if((string)location.hash != "" && $((string)"screen" + location.hash).Exists) {
        $((string)"screen" + location.hash).style["display"] = "block";
    }
    else {
        $("screen[main]").style["display"] = "block";
        location.hash = "#";
    }
}
void use_screens() {
	screen_handle_change();
    document.body.onhashchange = new EventHandler(screen_handle_change);
}