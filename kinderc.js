const env = {};
const dp = [null];

let __debug = false;

class IO {
    static decode(pt, len) {
        return (new TextDecoder()).decode(new Uint8Array(memory.buffer, pt, len));
    }
    static encode(txt) {
        var encoded;
        if (typeof txt == "number") return txt;
        if (typeof txt == "undefined") return 0;
        if (typeof txt != "object") {
            encoded = (new TextEncoder()).encode(txt + '\0');
        } else encoded = new Uint8Array(txt);
        var pos = malloc(encoded.length);
        var bf = new Uint8Array(memory.buffer);
        bf.set(encoded, pos);
        return pos;
    }
    static ceval(pt, len, allocate_response) {
        const command = IO.decode(pt , len);
        var result = eval(command);
        const encoded = allocate_response == 1 ? IO.encode(result) : 0;
        if(__debug) {
            console.log("[" + pt + "," + len + "] RETURNED " + encoded + "\n%c" + command + "\n%c> %c" + result, "color: red; font-style: italic;", "color: green;", "color: lightblue;");
        }
        return encoded;
    }
}

env._eval = IO.ceval;
env.get_memory_size = () => memory.buffer.byteLength;
env.memory_grow = (q) => memory.grow(q);
env.time = () => Date.now() / 1000;
env.microtime = () => performance.now();
env.__cxa_atexit = function() {};

onload = async () => {
    var assemblyel = document.querySelector("assembly[src]");
    if (!assemblyel) return;
    window.memory = new WebAssembly.Memory({
        initial: 16,
    })
    env.memory = memory;
    var r = await WebAssembly.instantiateStreaming(fetch(assemblyel.getAttribute("src")), { env });
    for (var e in r.instance.exports) {
        if (!window[e]) window[e] = r.instance.exports[e];
    }
    __main();
}