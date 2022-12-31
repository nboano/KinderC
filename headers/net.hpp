#pragma once
#include "../kinderc.hpp"

/// @brief Given a clear URI, encodes it.
/// @param decodedURI A clear URI.
/// @return An encoded URI.
string encodeURIComponent(const char* decodedURI);

/// @brief Given an encoded URI, decodes it.
/// @param encodedURI An encoded URI.
/// @return A clear URI.
string decodeURIComponent(const char* encodedURI);

/// @brief Use this class to handle Network Requests
class XMLHttpRequest {
public:

    /// @brief Enumeration that represents the XHR different status.
    enum Status {
        // The request has not yet been opened nor sent. 
        UNSENT,
        // The request has been opened. 
        OPENED, 
        // The response headers are received and visible.
        HEADERS_RECEIVED, 
        // The request is loading body data.
        LOADING, 
        // The request has completed successfully.
        DONE 
    };

    /// @brief Creates a new request. Equal to the JS new XMLHttpREquest().
    XMLHttpRequest();

    XMLHttpRequest(int i);

    /// @brief Destroys a request.
    ~XMLHttpRequest();

    /// @brief Opens the communication channel.
    /// @param method A string literal containing the method (GET, POST, ...).
    /// @param url A string literal containing the URL to connect to.
    /// @param async A boolean. If it's true, the request will be async, otherwise it will be sync. In the second case the main thread will be blocked until the request finishes. 
    void open(const char* method, const char* url, const bool async = true);
    
    /// @brief Sends the request.
    void send();

    /// @brief Sends the request with a body (not available in GET).
    /// @param body The body text.
    void send(const char* body);

    /// @brief Sets an header of the request.
    /// @param headername The header key name.
    /// @param headervalue The header value.
    void setRequestHeader(const char* headername, const char* headervalue);

    /// @brief Retreives a response header value.
    /// @param headername The response header name.
    /// @return The value, if available.
    string getResponseHeader(const char* headername);

    /// @brief Parses the response into an object, if possible.
    /// @return An object pointer.
    object JSON();

    /// @brief Gets the response text.
    /// @return A string containing the response text.
    string Text();

    /// @brief Gets the raw response.
    /// @return A generic pointer to the response.
    void* RAW();

    // This event is triggered at the end of the request.
    ev_XMLHttpRequest(onload);

    // This event is triggered regularly when the data arrives.
    ev_XMLHttpRequest(onprogress);

    // This event is triggered when the readyState changes.
    ev_XMLHttpRequest(onreadystatechange);

    // This event is triggered in case of a network error
    ev_XMLHttpRequest(onerror);

    #ifndef __INTELLISENSE__
    void* get_response();
    Status get_readyState();
    int get_statusCode();
    int get_loaded();
    int get_total();
    string get_statusText();
    __declspec(property(get = get_response)) void* response;
    __declspec(property(get = get_readyState)) Status readyState;
    __declspec(property(get = get_statusCode)) int status;
    __declspec(property(get = get_loaded)) int loaded;
    __declspec(property(get = get_total)) int total;
    __declspec(property(get = get_statusText)) string statusText;
    #else
    /// @brief Raw response pointer.
    void* response;

    /// @brief The ready state of the request.
    Status readyState;

    /// @brief The HTTP status code (es. 200)
    int status;

    /// @brief The number of bytes loaded.
    int loaded;

    /// @brief The total number of bytes incoming.
    int total;

    /// @brief The HTTP status text (es. OK)
    string statusText;
    #endif

private:
    int index;
    string getJSHandler(EventHandler* h);
    void setAttribute(const char* name, const char* value);
    string getAttribute(const char* name);
};

typedef XMLHttpRequest Request;
typedef XMLHttpRequest NetRequest;