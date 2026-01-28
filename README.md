# KinderC 🌎

### From now on, C and C++ can go far beyond console developement!

Build fast and usable web applications using nothing but the good, old, C and C++.

> ❓ **Are you a computer science teacher?**<br>
Teach your students C/C++ **low-level**, **typised** programming while building fantastic, **all-device web applications** that can run in every browser.

## What does KinderC offer?

KinderC has support for the following functionalities:
- 🟢 **DOM manipulation**: full support. Wrapper for the JavaScript API.
- 🟢 **Network requests**: full support. Wrapper for the `XMLHttpRequest` API, and a pseudo-`fetch` API. Both asyncronous and synchronous requests are supported.
- 🟢 **Geolocation and Motion** API wrappers.
- 🟢 **Custom screens** (for example `#home`, `#about`) using the `<screen>` tag.
- 🟢 **Custom controls**: create your own custom controls (HTML tags) that execute code on creation or on particular, custom events.
- 🟢 **In-browser text-file reading** using the File API.
- 🟡 **JSON parsing**: supported. KinderC features a custom JSON serializer/deserializer that supports all kinds of objects. Your C++ struct/classes can become JSON and vice-versa! KinderC offers a basic implementation of object reflection. It still has to be improved.
- 🟡 **Threads**: Threads are partially supported, and use the JavaScript `Worker` API.
- 🟡 Built-in **Date-Time handling**.
- 🟡 Some **Math functions**, like `abs`, `sin`...

## Get started!

The library has NO external dependencies, but first you will need a compiler to transform your C/C++ code into a `.wasm` file.

So, let's start installing the ```clang```/```llvm``` compiler:

- **Windows**: click [there](https://releases.llvm.org/download.html), and download the latest version.

- **Linux**:
    ```bash
    sudo apt-get install llvm
    ```

- **MacOS** (with Brew):
    ```bash
    brew install llvm
    ```

Then, clone this repository in your new project folder:
```bash
git clone https://github.com/nboano/kinderc.git
```

Create a new C++ file, for example ```main.cpp```:

```cpp
#include "/path/to/kinderc.hpp"

int main() {
    printf("<h1>Hello World!</h1>");
}
```

Compile it into a new ```wasm``` file:
```bash
clang --target=wasm32 -std=c++17 -Wl,--no-entry -Wl,--export-dynamic -Wl,--allow-undefined -Wl,--lto-O3 -Wl,--import-memory -O3 -s -flto -nostdlib -fdeclspec -o main.wasm main.cpp
```

Create a new HTML file, that will be your webpage:
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>KinderC Hello World</title>

    <script src="https://cdn.jsdelivr.net/gh/nboano/kinderc/kinderc.js"></script>
    <assembly src="main.wasm"></assembly>
</head>
<body>
    
</body>
</html>
```

> **Note**: the `<assembly>` tag is not part of the HTML standard. The glue code (`kinderc.js`) will look for the file in the `<assembly>` tag, instantiate it and execute his `main()`.

Open your webpage (that should be hosted on an HTTP server):
![](guides/images/03-hello-world.png)

**And... That's it!**

## Documentation

- [English 🇬🇧](./guides/en/README.md), still has to be written.
- [Italiano 🇮🇹](./guides/it/README.md), documentazione originale in fase di completamento.