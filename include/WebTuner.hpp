#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#define ENABLE_WEB_TUNER

# ifndef ENABLE_WEB_TUNER
    class WebTuner {
    public:
        WebTuner(int) {}
        void setup() {}
        void tick() {}
    };

#else

    class WebTuner
    {
    public:
        WebTuner(int port);
        void setup();
        void tick();
    private:
        void handleRoot();
        void handleGet();
        static constexpr char* SSID = "KRET";
        static constexpr char* PASS = "12345678";
        WebServer server;

    };

#endif

const char INDEX_HTML[] PROGMEM = R"rawliteral(
    <h1>Hello from ESP</h1>
    <p>Zwykły tekst.</p>
)rawliteral";
// const char INDEX_HTML[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html>
// <head>
// <meta name="viewport" content="width=device-width, initial-scale=1">
// <title>ESP Tuner</title>
// <style>
//   body { font-family: sans-serif; max-width: 480px; margin: 20px auto; padding: 0 16px; }
//   .row { margin: 24px 0; }
//   input[type=range] { width: 100%; }
//   button { padding: 10px 20px; font-size: 16px; }
//   #status { color: #666; margin-top: 12px; }
// </style>
// </head>
// <body>
//   <h2>Motor tuning</h2>

//   <div class="row">
//     <label>Acceleration rate: <b id="accVal"></b></label>
//     <input type="range" id="acc" min="0.1" max="50" step="0.1">
//   </div>

//   <div class="row">
//     <label>Deceleration rate: <b id="decVal"></b></label>
//     <input type="range" id="dec" min="0.1" max="50" step="0.1">
//   </div>

//   <button onclick="save()">Save to flash</button>
//   <div id="status"></div>

// <script>
// const acc = document.getElementById('acc');
// const dec = document.getElementById('dec');
// const accVal = document.getElementById('accVal');
// const decVal = document.getElementById('decVal');
// const statusEl = document.getElementById('status');
// let timer = null;

// function show() { accVal.textContent = acc.value; decVal.textContent = dec.value; }

// function send() {
//   fetch(`/set?acc=${acc.value}&dec=${dec.value}`)
//     .then(() => statusEl.textContent = 'Applied')
//     .catch(() => statusEl.textContent = 'Connection error');
// }

// // throttle so we don't flood the ESP while dragging
// function onChange() {
//   show();
//   clearTimeout(timer);
//   timer = setTimeout(send, 80);
// }

// function save() {
//   fetch('/save').then(() => statusEl.textContent = 'Saved to flash');
// }

// acc.oninput = onChange;
// dec.oninput = onChange;

// // load current values from the ESP on page open
// fetch('/get').then(r => r.json()).then(d => {
//   acc.value = d.acc; dec.value = d.dec; show();
// });
// </script>
// </body>
// </html>
// )rawliteral";