const expanded = [`40vh`, `60vh`];
const shrunk = [`10vh`, `90vh`];

let barCentral;

// Updates two menus concurrecntly, but only displays one of them (hopefully menu operations aren't expensive)


const refreshTime = 500;

function statsTable(data) {
    // Clear existing content

    // Create a table element
    const table = document.createElement('table');
    table.className = 'styled-table'; // Add class for styling

    // Create a table header
    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');

    // Define headers based on your data
    const headers = ['Current Length', 'Swaps/second', 'Users Online', 'Work Remaining', 'Total Swaps', 'Your work done', 'Your swaps performed'];

    // Append headers to the table
    headers.forEach(header => {
        const th = document.createElement('th');
        th.textContent = header;
        headerRow.appendChild(th);
    });

    thead.appendChild(headerRow);
    table.appendChild(thead);

    // Create a table body
    const tbody = document.createElement('tbody');
    const row = document.createElement('tr');

    // Populate the row with data
    const values = [
        data["length"],
        data["swap_statistic"],
        data["num_connected_users"],
        data["work_remaining"],
        data["total_swaps_so_far"],
        data["work_done"],
        data["swaps_performed"]
    ];

    values.forEach(value => {
        const td = document.createElement('td');
        td.textContent = value;
        row.appendChild(td);
    });

    tbody.appendChild(row);
    table.appendChild(tbody);

    // Append the table to the div
    return table;
}


class TopMenu {
    #menuOpen = false;

    // This is rushed
    // All of shrunkDiv elements go here 
    #shrunkDiv;

    // all of expandedDiv elements go here 
    #expandedDiv;   

    // Probably need a different class for mobile eh? 

    constructor(menuDiv, enemyDiv) {
        // Initially false 
        menuDiv.style.height = shrunk[0];
        enemyDiv.style.height = shrunk[1];

        this.#shrunkDiv = document.getElementById("shrunkMenu");
        this.#expandedDiv = document.getElementById("expandedMenu");

        this.#shrunkDiv.style.display = "block";
        this.#expandedDiv.style.display = "none";

        const button = document.getElementById('dropdown');

        button.addEventListener('click', () => {
            if (this.#menuOpen) {
                // -> shrunk
                this.#shrunkDiv.style.display = "block";
                this.#expandedDiv.style.display = "none";
                menuDiv.style.height = shrunk[0];
                enemyDiv.style.height = shrunk[1];
                button.style.transform = 'rotate(0deg)';
            } else {
                // -> expanded
                this.#expandedDiv.style.display = "block";
                this.#shrunkDiv.style.display = "none";
                menuDiv.style.height = expanded[0];
                enemyDiv.style.height = expanded[1];
                button.style.transform = 'rotate(180deg)';
            }
            this.#menuOpen = !this.#menuOpen;
        });

        // TODO: Make this stats table good and not bad 
        this.#expandedDiv.append(statsTable({}));// dummy table last


        // Set controls div to invisible if on mobile
        if (window.isMobile()) document.getElementById("controls-div").style.display = "none";
    }

    // refer to PermutationServerHandler

    // Might be annoying bug where because we're trying to constantly refresh we can't actually click on stuff...
    // Stats, settings, credits?


    #lastRequest = Date.now() - refreshTime;

    update(data) {
        if (Date.now() - this.#lastRequest >= refreshTime) {
            this.#lastRequest = Date.now();

            this.#shrunkDiv.innerHTML = '';
            this.#shrunkDiv.append(statsTable(data));
            
            this.#expandedDiv.removeChild(this.#expandedDiv.lastChild);
            this.#expandedDiv.append(statsTable(data));
        }
    }
}

const barSpacing = 1; // in "px"

// Because the scrolling functionality is so integrated and core w/ the window tracking logic, this class 
// simply handles the tracking of deltas, whereas the renderer actually does graphics

// The only rendering thing this manages is the full height of the innerDiv.
// This also handles the sliding window cache with their own divs & stuff. 
// ^ the above promise was broken but too lazy to refactor CachedBar to its own class

// Shuffles DOM elements around, recreating the effect of React-Window 

const barListener = document.getElementById("bars-per-screen-slider");

function barsOnScreen() {
    return barListener.value;
}

function barHeight() {
    return 100 / barsOnScreen(); // in "vh"
}

class CachedBar {
    clickableAreaDiv;
    barDiv; // the bar itself
    selectDiv; // if selected, display and render this div

    index; 
    value;

    lastEventListner = null;

    constructor() {
        this.clickableAreaDiv = document.createElement('div');
        this.clickableAreaDiv.className = 'barClick';

        this.barDiv = document.createElement('div');
        this.selectDiv = document.createElement('div');
        this.barDiv.className = "bar";
        this.selectDiv.className = "barExtra";

        this.clickableAreaDiv.style.background = 'transparent';

        // invariants (do not put dynamic transforms here)
        this.clickableAreaDiv.style.margin = `${barSpacing}px 0`;

        this.clickableAreaDiv.appendChild(this.barDiv);
        this.clickableAreaDiv.appendChild(this.selectDiv);
    }

    setClick(f) {
        this.clickableAreaDiv.removeEventListener('click', this.lastEventListner);
        this.clickableAreaDiv.addEventListener('click', f);
        this.lastEventListner = f;
    }
}

class BarDivDataHandler { 
    #outerDiv; // the "portrait window"
    #innerDiv; // the actual meat

    #arraySize = 0;

    #cache = []; 

    #force_refresh() {
        for (let i = 0; i < this.#cache.length; ++i) if (this.#cache[i] !== null) {
            this.#cache[i].index = null;
            this.#cache[i].value = null;
            this.#cache[i].clickableAreaDiv.style.display = "none";
        }

        this.#innerDiv.style.height = this.#calcBarPosition(this.#arraySize);

        // console.log(this.#innerDiv.style.height, this.#extractAndCalculate(this.#innerDiv.style.height), this.#outerDiv.scrollTop);
        // Force scroll to reset as well in case of out of bounds 
        this.#outerDiv.scrollTop = Math.min(this.#extractAndCalculate(this.#innerDiv.style.height), this.#outerDiv.scrollTop);
    }

    constructor(innerDiv) {
        this.#innerDiv = innerDiv;
        this.#outerDiv = innerDiv.parentNode;
         
        for (let i = 0; i < 3 * barListener.max + 10; ++i) {
            this.#cache.push(null);
        }

        // On slider reset, force a refresh of graphics. Only way I can think of to properly deal with the bug. 
        barListener.addEventListener('input', () => {
            setTimeout(() => {this.#force_refresh() }, 0); // run this *after* input is done updating  
        });

        this.#force_refresh();
    }

    #getAbsolutePosition() { // returns an integer between [0, lastUpdatedSize)
        const rect = this.#innerDiv.getBoundingClientRect();
        const height = Math.max(rect.height, 1);
        const top = this.#outerDiv.scrollTop;
        const frac = top / height;

        return Math.floor(Math.max(0, Math.min(this.#arraySize - 1, frac * this.#arraySize)));
    }


    // for BarRenderer
    requestBar(index) { 
        let cur = this.#cache[index % this.#cache.length];
        if (cur === null) {
            cur = new CachedBar();
            this.#cache[index % this.#cache.length] = cur;
            this.#innerDiv.appendChild(cur.clickableAreaDiv);
        }

        cur.clickableAreaDiv.style.height = `${barHeight()}vh`;
        cur.clickableAreaDiv.style.display = "initial";
        
        cur.clickableAreaDiv.style.top = this.#calcBarPosition(index);
        return cur;
    }

    setArraySize(n) {
        if (this.#arraySize == n) return; 
        /// TODO: Perhaps send a new victory message here!

        this.#arraySize = n;

        this.#force_refresh();
    }

    getInnerDiv() {
        return this.#innerDiv;
    }

    getSettings() {
        let idx = this.#getAbsolutePosition();
        return {
            "index": idx,
            "windowSize": Math.min(barsOnScreen(), this.#arraySize - idx),
            "n": this.#arraySize,
            "barHeight": barHeight(),
            "barSpacing": barSpacing,
        };
    }

    #calcBarPosition(i) {
        return `calc(${i * (barSpacing)}px + ${i * barHeight()}vh)`;
    }

    #extractAndCalculate(str) {
        // Adjusted regular expression to handle floating-point numbers and optional spaces
        const match = str.match(/calc\(\s*([+-]?\d*\.?\d+)px\s*\+\s*([+-]?\d*\.?\d+)vh\s*\)/);
        
        if (!match) return null;  // Handle invalid format

        const x = parseFloat(match[1]);  // Extract and convert x to a float
        const y = parseFloat(match[2]);  // Extract and convert y to a float

        // Calculate the result: x + (y as percentage of viewport height)
        const viewportHeight = window.innerHeight;
        return x + (y / 100) * viewportHeight;
    }

    reset(x) { // request X to be at the center of the page 
        this.#outerDiv.scrollTop = this.#extractAndCalculate(this.#calcBarPosition(Math.max(x - Math.floor(barsOnScreen() / 2) , 0)));
    }

}

const refreshMs = 1000 / 30; 

const hsl_sat_listener = document.getElementById("HSL-saturation-slider");
const hsl_light_listener = document.getElementById("HSL-lightness-slider");



class BarRenderer {
    #selectedBar = null;

    #innerDivHandler = null;

    // Okay so barRenderer is the only sender to permutationContext
    // but the backend slowly but surely is adding more aux features
    // so this is why we have this coupling here but have BarCentral to propogate messages properly
    #permutationContext = null;

    #swapDirection = null; 

    // Could be cleaner UI w/ broadcasting
    
    #selectedIndex; 

    getSelectedIndex() {
        return this.#selectedIndex;
    }

    getSelected() {
        return this.#selectedBar;
    }

    #select(x, index) {
        this.#selectedBar = x;
        this.#selectedIndex = index;
    }

    deselect() {
        this.#selectedBar = null;
        this.#selectedIndex = null;
        this.setDirection(null);
    }

    setDirection(dir) {
        this.#swapDirection = dir;
    }

    getInnerDivHandler() {
        return this.#innerDivHandler;
    }

    constructor(innerDivHandler, permutationContext) {
        this.#innerDivHandler = innerDivHandler;
        this.#permutationContext = permutationContext;

        setInterval(() => {
            let result = this.#innerDivHandler.getSettings();
            
            // ask for a little buffer before 
            permutationContext.sendIndex(Math.max(result["index"] - 5, 0));
        }, refreshMs);
    }

    redrawPermutation(currentIndex, permutation) {     
        const bar_frac = 0.90;
        // bad, normal, good 
        const min_width = [2, 5, 8];

        let result = this.#innerDivHandler.getSettings();

        const fullLength = result["n"];
        const viewIndex = result["index"];
	    const windowSize = result["windowSize"];

        for (let iter = 0; iter < permutation.length; iter++) {
            let index = currentIndex + iter;
            let x = permutation[iter];

            if (!(viewIndex <= index && index < viewIndex + windowSize)) continue; // take intersection, immportant for async refreshes
            
            // selectedBar logic is scuffed
            if (x === this.#selectedBar && this.#selectedIndex != index) {
                this.#selectedIndex = index; 
                this.#innerDivHandler.reset(this.#selectedIndex);
            } 

            let mybar = this.#innerDivHandler.requestBar(index, x);
            
            if (mybar.index !== index || mybar.value !== x) {
                // reset bar info, because it is stale (mainly so that setClick isn't reset 1e9/s)

                mybar.index = index;
                mybar.value = x;
                mybar.setClick(() => {
                    const myValue = x;
                    const myIndex = index;
                    if (this.#selectedBar === null) {
                        this.#select(myValue, myIndex);
                    } else if (this.#selectedBar === myValue) {
                        this.deselect();
                    } else {
                        this.#permutationContext.sendSwap(this.#selectedBar, myValue);
                        this.deselect();
                    }


                });
            }
            
            // TODO: Why does Arrow swapping go through this.... 
            if (x == this.#selectedBar && this.#swapDirection !== null) {
                // Apply swap
                if (iter + this.#swapDirection >= 0 && iter + this.#swapDirection < permutation.length) {
                    this.#permutationContext.sendSwap(this.#selectedBar, permutation[iter + this.#swapDirection]);
                    this.setDirection(null); 
                }
            }

            let clickablePart = mybar.clickableAreaDiv;

            // invariants here 

            let defbg = `hsl(${x / fullLength * 300}, ${hsl_sat_listener.value}%, ${hsl_light_listener.value}%)`;

            let barWidthPercentage = (x) => {
                return (bar_frac * (x / fullLength)) * 100;
            };

            clickablePart.style.background = 'transparent';
            
            // to help people gauge fixed points
            if (x === index) {
                clickablePart.style.background = 'rgba(255, 255, 0, 0.2)'; // yellow
            }
            
            clickablePart.style.zIndex = 0;
            
            // If there's an local inversion, subtly highlight this 
            if (iter + 1 < permutation.length && permutation[iter] > permutation[iter + 1]) {
                clickablePart.style.border = '1px solid rgba(255, 99, 71, 0.5)' ; // red
            } else {
                clickablePart.style.border = '';
            }

            // If our selected value is on the screen, make it easy and clear for them to see
            if (this.#selectedBar === index) {
                clickablePart.style.background = 'rgba(0, 255, 0, 1)'; // solid green
            } 
            
            // reset selection
            mybar.barDiv.style.border = '1px solid black'; // selection flair
            mybar.barDiv.style.background = defbg;
            mybar.selectDiv.style.width = "0%";

            mybar.selectDiv.style.border = '';

            let fill2 = `rgba(0, 0, 0, 0.5)`;

            if (!(this.#selectedBar === null || this.#selectedBar === x)) {
                let fill;
                if (this.#selectedBar > x) { // we are smaller 
                    fill = `rgba(0, 255, 0, 1)`;

                    mybar.barDiv.style.width =  `${min_width[0] + barWidthPercentage(Math.min(this.#selectedBar, x) + 1)}%`;
                    mybar.selectDiv.style.width = `${barWidthPercentage(this.#selectedBar - x)}%`;
                } else {  // we are larger
                    fill = `rgba(255, 0, 0, 1)`;

                    mybar.barDiv.style.width =  `${min_width[2] + barWidthPercentage(Math.min(this.#selectedBar, x) + 1)}%`;
                    mybar.selectDiv.style.width = `${barWidthPercentage(x - this.#selectedBar)}%`;
                }

                mybar.selectDiv.style.background = `
                    repeating-linear-gradient(
                        45deg,
                        transparent,
                        transparent 10px,
                        ${fill2} 10px,
                        ${fill2} 20px
                    ),                    
                    ${fill}
                `;

                mybar.selectDiv.style.border = '1px solid black'; // selection flair
                
            } else {
                // just normal

                mybar.barDiv.style.width =  `${min_width[1] + barWidthPercentage(x + 1)}%`;
                mybar.selectDiv.style.width = "0%";

                if (this.#selectedBar === x) {
                    clickablePart.style.zIndex = 10; // above others
                    mybar.barDiv.style.border = '3px solid white'; // selection flair
                } 
            }

        }

   }
}
class ExtraSwapFunctionalities {
    constructor(main, renderer) {
        // Attaches event listeners to the main div node, so they get deleted etc. 

        main.addEventListener('keydown', function(event) {
            switch (event.key) {
                case 'Escape':
                    renderer.deselect();
                    break;
                case 'w':
                    // console.log("SETTING DIR");
                    renderer.setDirection(-1);
                    break;
                case 's':
                    renderer.setDirection(1);
                    break;
                case 'a':
                    renderer.setDirection(-5);
                    break;
                case 'd':
                    renderer.setDirection(+5);
                    break;
                case ' ':
                    let x = renderer.getSelectedIndex();
                    if (x !== null) {
                        event.preventDefault();
                        event.stopPropagation();
                        renderer.getInnerDivHandler().reset(x);
                    }
                    break;
                default:
                    break;
            }
        });
        
        // Handle keyup events
        main.addEventListener('keyup', function(event) {
            switch (event.key) {
                case 'w':
                case 's':
                case 'a':
                case 'd':
                    renderer.setDirection(null);
                default:
                    break;
            }
        });

        // Timeout is ugly, but I really don't want to make BarRenderer more coupled just yet 
       	
        if (window.isMobile()
            // || true
        ) {
            let mobileDiv = document.createElement('div');
            main.prepend(mobileDiv);

            mobileDiv.id = 'deselect-mobile-popup';
            mobileDiv.style.display = "none";

            mobileDiv.addEventListener('click', () => {
                renderer.deselect();
                mobileDiv.style.display = "none";
            });

            setInterval(
                () => {
                    let sel = renderer.getSelected();
                    if (sel !== null) {
                        mobileDiv.innerText = `deselect bar ${sel}`;
                        mobileDiv.style.display = "flex";
                    } else {
                        mobileDiv.style.display = "none";
                    }
                }
                ,100
            )
        }
        
        
    }
}



class BarCentral {
    #renderer = null;
    #divHandler = null;
    #permutationContext = null;
    #extraSwapFunctions = null;
    #menu = null;

    constructor(innerDiv, permutationContext, statsHandler) {
        this.#divHandler = new BarDivDataHandler(innerDiv);
        this.#permutationContext = permutationContext;
        this.#permutationContext.receiver = this;
        this.#renderer = new BarRenderer(this.#divHandler, this.#permutationContext);
        this.#menu = statsHandler;
        this.#extraSwapFunctions = new ExtraSwapFunctionalities(innerDiv.parentNode, this.#renderer);        
    }
    
    sendAux(data) {
        if ('length' in data) {
            this.#divHandler.setArraySize(data['length']);
        }
        this.#menu.update(data);
    }

    handleNewPermutationWindow(index, array) {
        this.#renderer.redrawPermutation(index, array);
    }
} 

class PermutationContext {
    
    // Should be a protected variable... but... js...
    receiver // barCentral

    constructor() {}

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
	this.#connect();
    }

    #connect() {
        this.ws = new WebSocket(this.#url);

        this.ws.onopen = () => {
            console.log("WebSocket connection opened.");

            let id = localStorage.getItem('id');
            if (!id) {
                id = self.crypto.randomUUID();
                console.log("Created uuid ", id);
                localStorage.setItem('id', id);
            }
            
            const message = JSON.stringify({
                type: "unauthenticated_id",
                id: id
            });
            this.ws.send(message);
        };

        this.ws.onmessage = (event) => {
            const message = JSON.parse(event.data);
            this.handleMessage(message);
        };

        this.ws.onclose = () => {
            console.log("WebSocket connection closed.");
            // Attempt to reconnect
            setTimeout(() => {
                console.log('Attempting to reconnect...');
                this.#connect(); // Reconnect
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
        })    ;
        this.ws.send(message);
        this.#lastRequested = i;   
    }

    handleMessage(message) {
        switch (message.type) {
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

                this.receiver.sendAux(message);
                this.receiver.handleNewPermutationWindow(message["index"], base64ToUint32Array(message["window"]));
                break;
            default:
                console.warn("Unknown message type:", message.type);
        }
    }
}

// function fadeOutAndRemove(element) {
//     let opacity = 1;  // Initial opacity

//     const death = 0.02;

//     const fadeOut = setInterval(() => {
//         if (opacity <= death) {
//             clearInterval(fadeOut);
//             element.style.display = 'none';  // Completely hide the element
//             element.remove();  // Remove the element from the DOM
//         } else {
//             opacity -= death;
//             element.style.opacity = opacity;
//         }
//     }, 100);  // Fade out speed
// }

const innerDiv = document.getElementById('scroll-content');
    const outerDiv = document.getElementById('scroll-container');

    // assign gradient
    let gradstr = "";
    let len = 60;
    for (let i = 0; i <= len; i+=1) {
        gradstr += `hsl(${i/len * 300}, 25%, 75%) ${i/len * 100}%`;
        if (i != len) gradstr += ',';
    }

    innerDiv.style.background = `linear-gradient(to bottom, ${gradstr})`;
    
    // const ctx = new PermutationMockStatic(500);
    // const ctx = new PermutationMockDoubler();
     const ctx = new PermutationServerHandler("wss://" + document.location.host + "/ws");
    // const ctx = new PermutationServerHandler("ws://" + document.location.host + "/ws");

    const menu = document.getElementById('menu-container');

    barCentral = new BarCentral(innerDiv, ctx, new TopMenu(menu, outerDiv));
    // const element = document.getElementById('fade-out-after-5-seconds');
    // fadeOutAndRemove(element);

// barCentral.#divHandler.requestBar(4094)

// function getVal(idx) {
//     return barCentral.#divHandler.requestBar(idx).value;
// }

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}


async function sortPerm(handler, L, R) {
    let seen = new Set();
    for(let i = L; i < R; i++) {
        let iv = handler.requestBar(i).value;
        if (seen.has(i) || seen.has(iv)) continue;
        if(iv != i) {
            // handler.requestBar(iv).barDiv.scrollIntoView()
            handler.requestBar(Math.max(0, i - 5)).barDiv.scrollIntoView()
            seen.add(i);
            seen.add(iv);
            ctx.sendSwap(i, iv);
            await sleep(1100);
        }
        // let minidx = i+1;
        // for(let j = i + 1; j < R; j++) {
        //     if (handler.requestBar(j) < handler.requestBar(minidx)) minidx = j;
        // }
        // let jv = handler.requestBar(minidx).value;
        // if(iv > jv) {
        //     ctx.sendSwap(iv, jv);
        // }
    }
}