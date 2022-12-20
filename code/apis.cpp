#pragma once
#include "../kinderc.hpp"

Property<bool> Geolocation::IsSupported = Property<bool>(
    []() {
        return (int)JavaScript::Eval("!!navigator.geolocation?1:0") == 1;
    }
);

void Geolocation::GetPosition(void(*sh)(GeolocationData)) {
    static void(*onsuccess)(GeolocationData);
    onsuccess = sh;

    void(*hndl)(const char*) = [](const char* s) {
        string* spl = string(s).Split(';');
        GeolocationData gd = {
            atof(spl[0]),
            atof(spl[1]),
            atof(spl[2]),
            atof(spl[3]),
            atof(spl[4]),
            atof(spl[5]),
            atof(spl[6]),
        };
        delete[] spl;
        free((void*)s);
        onsuccess(gd);
    };

    Handler successhandler = EventHandler((void(*)(void*))hndl);

    navigator["geolocation"]["getCurrentPosition"]((string)"(e)=>__lambda_call(" + (string)successhandler.LambdaIndex +  ",IO.encode([e.coords.latitude,e.coords.longitude,e.coords.altitude,e.coords.accuracy,e.coords.altitudeAccuracy,e.coords.heading,e.coords.speed].join(';')))");
}