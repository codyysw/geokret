#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "Engine.hpp"
#include  "Mole.hpp"

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
        float getAcc() const { return Engine::ACCELERATION_RATE; }
        float getDec() const { return Engine::DECELERATION_RATE; }
        void setAcc(float newAcc) { Engine::ACCELERATION_RATE = newAcc; }
        void setDec(float newDec) { Engine::DECELERATION_RATE = newDec; }

        float getTurnFac() const { return Mole::TURN_FACTOR; }
        float getPowFac() const { return Mole::POWER_FACTOR; }
        void setTurnFac(float newTurn) { Mole::TURN_FACTOR = newTurn; }
        void setPowFac(float newPow) { Mole::POWER_FACTOR = newPow; }

        void print() const;
    private:
        void handleRoot();
        void handleGet();
        void handleSet();

        static constexpr const char* SSID = "KRET";
        static constexpr const char* PASS = "12345678";
        WebServer server;
        volatile float acc = 5.0f;    // same defaults as Engine for now
        volatile float dec = 20.0f;
    };

#endif

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP Tuner</title>
<style>
  body { font-family: sans-serif; max-width: 480px; margin: 20px auto; padding: 0 16px; }
  .row { margin: 24px 0; }
  input[type=range] { width: 100%; }
  #status { color: #666; margin-top: 12px; }
</style>
</head>
<body>
  <h2>Motor tuning</h2>
  <div id="sliders"></div>
  <div id="status"></div>
 
<script>
// min/max/step are placeholders for turn and pow, set them to your real ranges
const params = [
  { key: 'acc',  label: 'Acceleration rate', min: 0.1, max: 50, step: 0.1  },
  { key: 'dec',  label: 'Deceleration rate', min: 0.1, max: 50, step: 0.1  },
  { key: 'turn', label: 'Turn factor',       min: 0,   max: 1,  step: 0.01 },
  { key: 'pow',  label: 'Power factor',      min: 0,   max: 1,  step: 0.01 },
];
 
const statusEl  = document.getElementById('status');
const container = document.getElementById('sliders');
const inputs = {};
const valEls = {};
const timers = {};
 
// sends only the slider that changed, so other values are never overwritten
function send(key) {
  fetch(`/set?${key}=${inputs[key].value}`)
    .then(() => statusEl.textContent = 'Applied')
    .catch(() => statusEl.textContent = 'Connection error');
}
 
params.forEach(p => {
  const row = document.createElement('div');
  row.className = 'row';
  row.innerHTML =
    `<label>${p.label}: <b></b></label>
     <input type="range" min="${p.min}" max="${p.max}" step="${p.step}">`;
  container.appendChild(row);
 
  inputs[p.key] = row.querySelector('input');
  valEls[p.key] = row.querySelector('b');
 
  // throttle so we don't flood the ESP while dragging
  inputs[p.key].oninput = () => {
    valEls[p.key].textContent = inputs[p.key].value;
    clearTimeout(timers[p.key]);
    timers[p.key] = setTimeout(() => send(p.key), 80);
  };
});
 
// load current values from the ESP on page open
fetch('/get').then(r => r.json()).then(d => {
  params.forEach(p => {
    inputs[p.key].value = d[p.key];
    valEls[p.key].textContent = inputs[p.key].value;
  });
});
</script>
</body>
</html>
)rawliteral";
