#pragma once
#include "../kinderc.hpp"

/// @brief This struct holds the geolocation informations after a Geolocation::GetPosition or Geolocation::WatchPosition successful call.
struct GeolocationData {

    /// @brief The latitude, as a double.
    double Latitude;

    /// @brief The longitude, as a double.
    double Longitude;

    /// @brief The altitude, expressed in meters. If not available, its value will always be 0.
    double Altitude;

    /// @brief The accuracy, expressed in meters, of the coordinates. If not available, its value will always be 0.
    double Accuracy;

    /// @brief The accuracy, expressed in meters, of the altitude. If not available, its value will always be 0.
    double AltitudeAccuracy;

    /// @brief The direction of the device (in degrees). If not available, its value will always be 0.
    double Heading;

    /// @brief The speed of the device (in meters per second). If not available, its value will always be 0.
    double Speed;
};

/// @brief Enum that represents the possible Geolocation errors.
enum GeolocationError {
    PERMISSION_DENIED = 1,
    POSITION_UNAVAILABLE = 2,
    TIMEOUT = 3,
};

/// @brief Use this class to get geolocation informations from the device.
class Geolocation {
    public:

    /// @brief If true, tells the device to get the most accurate results.
    static bool HighAccuracy;

    /// @brief Property that tells if the Geolocation API is supported or not.
    static Property<bool> IsSupported;

    /// @brief Retrieves the user current position.
    /// @param successhandler An handler, with a single param of type GeolocationData, that will be called when the informations are ready.
    /// @param errorhandler An handler called in case of error.
    static void GetPosition(void(*successhandler)(GeolocationData), void(*errorhandler)(GeolocationError) = [](GeolocationError){});

    /// @brief Calls the Handler every time the user position changes.
    /// @param successhandler An handler, with a single param of type GeolocationData.
    /// @param errorhandler An handler called in case of error.
    /// @return An integer, that will be used to clear the position watcher.
    static int WatchPosition(void(*successhandler)(GeolocationData), void(*errorhandler)(GeolocationError) = [](GeolocationError){});

    /// @brief Clears a watcher created using WatchPosition.
    /// @param watch_number The watcher identifier (returned by the WatchPosition call).
    static void ClearWatch(int watch_number);

    private:
    static int Request(void(*sh)(GeolocationData), void(*eh)(GeolocationError), bool watch);
};