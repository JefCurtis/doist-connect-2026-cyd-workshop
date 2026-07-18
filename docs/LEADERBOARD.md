# Stretch goal: shared leaderboard

Do not add networking to the core workshop path. The offline game should remain playable when WiFi or the API is unavailable.

## Suggested architecture

```text
UI
  asks for leaderboard data
Data layer
  validates scores and converts JSON
Network layer
  owns WiFi and HTTP requests
Leaderboard API
  stores and ranks scores
```

Do not put WiFi connection loops or HTTP requests directly in an LVGL event callback.

## Minimal API contract

### Submit a score

```http
POST /api/scores
Content-Type: application/json

{
  "player": "Jef",
  "score": 24,
  "game": "tap-quest",
  "device_id": "cyd-a1b2"
}
```

Successful response:

```json
{
  "accepted": true,
  "rank": 3
}
```

### Fetch leaders

```http
GET /api/scores?game=tap-quest&limit=10
```

```json
{
  "scores": [
    { "player": "Rosa", "score": 31 },
    { "player": "Jef", "score": 24 }
  ]
}
```

## Practical constraints

| Concern | Recommended approach |
|---|---|
| Hotel WiFi | Test with a dedicated 2.4 GHz hotspot or travel router. Do not assume captive-portal WiFi will work. |
| TLS memory | Reuse or release HTTP clients carefully. Keep JSON documents small. |
| Frozen UI | Queue requests from UI events and process them from the main loop or a worker task. |
| Offline scores | Save one pending score in NVS and retry with a limit. The game must not block waiting for upload. |
| API abuse | Validate score ranges server-side and rate-limit device submissions. This is a friendly leaderboard, not secure anti-cheat. |
| Secrets | Never commit WiFi passwords or API tokens. Use a gitignored `include/secrets.h` for local development. |
| Device identity | Generate or derive a short anonymous ID. Do not send a full WiFi MAC address unless the use case requires it. |
| Time | Let the server timestamp submissions. Device clocks may be wrong before NTP sync. |

## Implementation sequence

1. Add `src/network/wifi_client.*` with connection state and timeout handling.
2. Add `src/data/leaderboard_client.*` with request and response models.
3. Add ArduinoJson to `platformio.ini`.
4. Show connection state without preventing offline play.
5. Submit a score after the results screen appears.
6. Fetch and display the top five scores on a separate screen.
7. Add one pending offline submission and bounded retries.
8. Measure firmware and RAM use after each step.
