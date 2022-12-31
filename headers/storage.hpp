#pragma once
#include "../kinderc.hpp"

/// @brief Handles the localStorage and the sessionStorage objects.
class Storage {
    public:
        Storage(bool isLocalStorage);

        /// @brief Sets an item into the storage.
        /// @param key The item key.
        /// @param value The item value.
        void setItem(string key, string value);

        /// @brief Retrieves an item from the storage.
        /// @param key The item key.
        /// @return The item value.
        string getItem(string key);

        /// @brief Removes an item from the storage.
        /// @param key The item key.
        void removeItem(string key);

        /// @brief Clears the storage.
        void clear();

        #ifndef __INTELLISENSE__
        int get_length();
        __declspec(property(get = get_length)) int length;
        #else
        /// @brief Gets the number of elements into the storage.
        int length;
        #endif
    private:
        #ifdef __INTELLISENSE__
        int get_length();
        #endif
        bool ls;
};

/// @brief Local Storage API, to store key/value pairs.
Storage localStorage(true);

/// @brief Session Storage API, to store key/value pairs.
Storage sessionStorage(false);