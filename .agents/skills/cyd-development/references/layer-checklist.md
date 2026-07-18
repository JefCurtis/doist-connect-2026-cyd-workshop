# Layer review checklist

Use this when a change crosses more than one layer.

| Layer | Review question |
|---|---|
| Hardware | Did pins, bus ownership, rotation, inversion, or active-low behavior change? |
| UI | Are controls large enough for resistive touch, and are LVGL objects valid for the active screen? |
| Game | Can rules be tested without knowing about LVGL objects? |
| Local data | Is stored data small, versionable, and written only when needed? |
| Network | Are connection and request timeouts bounded? Does offline mode still work? |
| API data | Are payload sizes bounded and server responses validated? |
| Runtime | Does the main loop remain responsive without long delays? |
| Memory | Did RAM and flash remain within safe measured limits? |
| Security | Are credentials excluded from Git and logs? |
