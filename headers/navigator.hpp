#pragma once
#include "../kinderc.hpp"

class Navigator : public object {
public:
    Navigator() : object("navigator") {}
    prop(appCodeName);
    prop(appName);
    prop(appVersion);
    prop(language);
    prop(platform);
    prop(product);
    prop(productSub);
    prop(userAgent);
    prop(vendor);
    prop(vendorSub);
};

#define navigator Navigator()