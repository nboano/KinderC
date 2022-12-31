#pragma once
#include "../kinderc.hpp"

class FilePicker {
    public:

    /// @brief Shows a dialog where the user can select one or more files. This method will work only if called by an action of the user.
    static void Show();

    /// @brief Resets all the dialog options.
    static void Reset();

    /// @brief The dialog file filer, ex "text/*", ".txt,.c,.cs"
    static Property<const char*> Filter;

    /// @brief A boolean that indicates if the user is allowed to select more files.
    static Property<bool> Multiple;

    /// @brief A boolean that indicates if the user is allowed to select an entire directory.
    static Property<bool> PickDirectory;

    /// @brief An array of files containing the selected ones.
    static Property<File*> Files;

    /// @brief An integer indicating the selected files number.
    static Property<int> FilesNumber;

    /// @brief An event triggered when the user changes his selection.
    static Property<void(*)(void*)> OnChange;

    private:

    static void assert_ofd();
    static const char* ID;
};