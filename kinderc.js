var env = {};
var dp = [null];

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
    static ceval(pt, len) {
        return IO.encode(eval(IO.decode(pt, len)));
    }
}

//#region EXPORTS
env._eval = IO.ceval;
env.get_memory_size = () => memory.buffer.byteLength;
env.memory_grow = (q) => memory.grow(q);
env._Znwm = function () { };
env._Znam = function () { };
env.__cxa_atexit = function () { };
//#endregion

onload = async () => {
    var e = document.querySelector("assembly[src]");
    if (!e) return;
    window.memory = new WebAssembly.Memory({
        initial: 2,
    })
    env.memory = memory;
    var r = await WebAssembly.instantiateStreaming(fetch(e.getAttribute("src")), { env });
    for (var e in r.instance.exports) {
        if (!window[e]) window[e] = r.instance.exports[e];
    }
    __main();
}