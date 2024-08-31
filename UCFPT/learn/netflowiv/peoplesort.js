
let globalPerm = [];

/*
    N                   int    `json:"n"`
    Index               int    `json:"index"`
    Window_size         int    `json:"window_size"`
    Window              string `json:"window"`
    Swap_statistic      int    `json:"swap_statistic"`
    Num_connected_users int    `json:"num_connected_users"`
    Work_remaining      uint64 `json:"work_remaining"`
    Total_swaps_so_far  uint64 `json:"total_swaps_so_far"`
    Work_done           int64  `json:"work_done"`
    Swaps_performed     uint64 `json:"swaps_performed"`
*/
function handleNewPermutationWindow(message) {
    // console.log("globalperm, receive window starting at " + message["index"] + " and length " + message["window_size"]);
    let conv = base64ToUint32Array(message["window"]);
    while (globalPerm.length < message["n"]) globalPerm.push(-1);
    let start = message["index"];
    for (let i = 0; i < message["window_size"]; i++) {
        globalPerm[i + start] = conv[i];
    }
    // console.log("from handlePerm", globalPerm.slice(0, 100));
}

class PermutationContext {

    // Should be a protected variable... but... js...
    receiver // barCentral

    constructor() { }

    setReceiver(receiver) {
        this.receiver = receiver;
    }

    sendSwap(u, v) {
        throw new Error("Method 'swapSwap(u, v)' must be implemented.");
    }
    sendIndex(i) {
        throw new Error("Method 'sendIndex(i)' must be implmeneted. Sets the requested subarray window to [i, i + ?)");
    }
};

// Big endian
function base64ToUint32Array(encoded) {
    // Decode Base64 string to a byte array
    const byteString = atob(encoded);
    const byteArray = new Uint8Array(byteString.length);

    for (let i = 0; i < byteString.length; i++) {
        byteArray[i] = byteString.charCodeAt(i);
    }

    // Convert byte array to uint32 array
    const uint32Array = [];
    for (let i = 0; i < byteArray.length; i += 4) {
        const uint32 = (byteArray[i] << 24) |
            (byteArray[i + 1] << 16) |
            (byteArray[i + 2] << 8) |
            byteArray[i + 3];
        uint32Array.push(uint32);
    }

    return uint32Array;
}


class PermutationServerHandler extends PermutationContext {
    #lastRequested = null;
    #currentSize = 0;
    #lastRequestedTime = Date.now();
    #url;

    constructor(url) {
        super();
        this.#url = url;
        this.pconnect();
    }

    pconnect() {
        this.ws = new WebSocket(this.#url);

        this.ws.onopen = () => {
            console.log("WebSocket connection opened to " + this.#url);

            let id = self.crypto.randomUUID();
            console.log("Created uuid ", id);

            const message = JSON.stringify({
                type: "unauthenticated_id",
                id: id
            });
            this.ws.send(message);
        };

        this.ws.onmessage = (event) => {
            const message = JSON.parse(event.data);
            this.handleMessage(message, this.ws);
        };

        this.ws.onclose = () => {
            console.log("WebSocket connection closed.");
            // Attempt to reconnect
            setTimeout(() => {
                console.log('Attempting to reconnect...');
                this.pconnect(); // Reconnect
            }, 2000);
        };

        this.ws.onerror = (error) => {
            console.error("WebSocket error:", error);
            // Optionally handle specific error scenarios if needed
        };
    }

    sendSwap(u, v) {
        if (Math.min(u, v) < 0 || Math.max(u, v) >= this.#currentSize) return false;

        const message = JSON.stringify({
            type: "swap_vals",
            u: u,
            v: v
        });

        console.log("SWAPPING", u, v);
        this.ws.send(message);
        return true;
    }

    sendIndex(i) {
        if (this.ws.readyState === WebSocket.OPEN) {

        } else {
            return;
        }

        // Do not spam the server, but allow a little bit of refreshing in case we get rate limited and a request doesn't go through 
        // if (this.#lastRequested === i && Date.now() - this.#lastRequestedTime < 1000) return;

        const message = JSON.stringify({
            type: "set_index",
            index: i
        });
        this.ws.send(message);
        this.#lastRequested = i;
    }

    handleMessage(message, ws) {
        switch (message.type) {
            case "verification_request":
                console.log("Got a request for verification");
                // Clear any previous Turnstile widget if needed
                document.getElementById('turnstile-container').innerHTML = '';

                // Render the Turnstile widget
                turnstile.render('#turnstile-container', {
                    //REALLY need a way to set config for local/prod
                    sitekey: '0x4AAAAAAAiMy1aFZQeiyrgZ',
                    callback: function (token) {
                        console.log('Verification successful, token:', token);
                        const message = JSON.stringify({
                            type: "verification_response",
                            response: token
                        });
                        ws.send(message);
                        document.getElementById('turnstile-container').innerHTML = '';
                    },
                    'error-callback': function () {
                        console.log('Verification failed');
                    }
                });
                break;
            case "permutation_window":
                /*
                    N                   int    `json:"n"`
                    Index               int    `json:"index"`
                    Window_size         int    `json:"window_size"`
                    Window              string `json:"window"`
                    Swap_statistic      int    `json:"swap_statistic"`
                    Num_connected_users int    `json:"num_connected_users"`
                    Work_remaining      uint64 `json:"work_remaining"`
                    Total_swaps_so_far  uint64 `json:"total_swaps_so_far"`
                    Work_done           int64  `json:"work_done"`
                    Swaps_performed     uint64 `json:"swaps_performed"`
                */

                this.#currentSize = message["n"]
                message["length"] = this.#currentSize;
                // console.log(message);
                // let conv = base64ToUint32Array(message["window"]);
                // console.log(message["index"], conv);

                // this.receiver.sendAux(message);
                handleNewPermutationWindow(message);
                // this.receiver.handleNewPermutationWindow(message["index"], conv);
                break;
            default:
                console.warn("Unknown message type:", message.type);
        }
    }
}





function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

let ctxs = [];
let prevSwapTimes = [];
async function createConnections(connections, spacing) {
    while (ctxs.length < connections) {
        console.log("creating connection " + ctxs.length);
        ctxs.push(new PermutationServerHandler("wss://" + document.location.host + "/ws"));
        prevSwapTimes.push(Date.now() - 2 * spacing);
        await sleep(10000);
    }
    console.log("there are now " + ctxs.length + " connections");
}

async function sortPerm(L, R, spacing, connections, accuracy) {
    await createConnections(connections, spacing);
    let conIdx = 0;
    await sleep(1000);
    for (let i = L; i < R; i++) {
        if(i % 50 == L % 50) {
            ctxs[conIdx].sendIndex(Math.max(0, i - 5));
            console.log("refreshing at " + i);
            await sleep(1000);
        }
        while (prevSwapTimes[conIdx] + spacing > Date.now()) {
            await sleep(prevSwapTimes[conIdx] + spacing - Date.now());
        }
        let iv = globalPerm[i];
        while (iv == undefined || iv == -1) {
            console.log(i, iv, "retrying");
            console.log("from sortperm", globalPerm.slice(0, 100));
            ctxs[conIdx].sendIndex(Math.max(0, i - 5));
            await sleep(1000);
            iv = globalPerm[i];
        }
        let rand = Math.floor(Math.random() * (2 * accuracy + 1));
        let targval = i;
        targval += rand - accuracy;
        targval = Math.max(targval, L);
        targval = Math.min(targval, R - 1);
        if (iv != targval) {
            ctxs[conIdx].sendSwap(targval, iv);
            prevSwapTimes[conIdx] = Date.now();
            conIdx = (conIdx + 1) % connections;
        }
    }
}

// await createConnections(10);
// await sortPerm(0, 3000, 1100, 10, 0);
