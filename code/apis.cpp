#pragma once
#include "../kinderc.hpp"

Property<bool> Geolocation::IsSupported = Property<bool>(
    []() {
        return (int)JavaScript::Eval("!!navigator.geolocation?1:0") == 1;
    }
);

bool Geolocation::HighAccuracy = false;

int Geolocation::Request(void(*sh)(GeolocationData), void(*eh)(GeolocationError), bool watch) {
    static void(*onsuccess)(GeolocationData);

    onsuccess = sh;

    void(*hndl)(char*) = [](char* s) {
        static string tmp;
        tmp = s;
        string* spl = tmp.Split(';');
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
    Handler errorhandler = EventHandler((void(*)(void*))eh);

    return (int)navigator["geolocation"][watch ? "watchPosition" : "getCurrentPosition"]((string)"(e)=>__lambda_call(" + (string)successhandler.LambdaIndex +  ",IO.encode([e.coords.latitude,e.coords.longitude,e.coords.altitude,e.coords.accuracy,e.coords.altitudeAccuracy,e.coords.heading,e.coords.speed].join(';')))", (string)"(e)=>__lambda_call(" + (string)errorhandler.LambdaIndex + ",e.code)", (string)"{enableHighAccuracy:" + (HighAccuracy ? "true" : "false") + "}");
}

void Geolocation::GetPosition(void(*sh)(GeolocationData), void(*eh)(GeolocationError)) {
    Geolocation::Request(sh, eh, false);
}

int Geolocation::WatchPosition(void(*sh)(GeolocationData), void(*eh)(GeolocationError)) {
    return Geolocation::Request(sh, eh, true);
}

void Geolocation::ClearWatch(int watch_number) {
    navigator["geolocation"]["clearWatch"]((string)watch_number);
}