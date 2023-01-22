#pragma once
#include "../kinderc.hpp"

/// @brief This struct incapsulates all the possible fetch options.
typedef struct s_FetchOptions {

    /// @brief The request method (GET, POST, ...)
    string Method;

    /// @brief The request body (not available in GET)
    string Body;

    /// @brief The request headers (key/value pairs)
    string Headers[16][2];

} FetchOptions;

/// @brief Class used to handle the fetch network responses.
class Response : public Request {

};

/// @brief Default fetch options (GET request with empty body)
#define FETCH_DEFAULTS {"GET", ""}

/// @brief Use the fetch API to perform async network requests.
class Fetch {
public:

    /// @brief Makes a network request.
    /// @param _url The request URL.
    /// @param _options The request options. Defaults to GET with empty body.
    Fetch(string _url, FetchOptions _options = FETCH_DEFAULTS);

    /// @brief Makes a sync network request. NOTE: This request will block the main thread until it's completed.
    /// @param URL The request URL.
    /// @param options The request options. Defaults to GET with empty body.
    /// @return The request object.
    static Response sync(string URL, FetchOptions options = FETCH_DEFAULTS);

    /// @brief Specifies an handler for when the request has completed.
    /// @param handler The handler.
    Fetch then(void(*)(Response&));

    /// @brief Specifies an handler for when a network error occurs
    /// @param handler The handler.
    Fetch error(void(*)(Response&));

private:
    Response r;
};

typedef Fetch fetch;