# Network and API safety

## Workshop network

The event network has been tested with a CYD:

| Setting | Value |
|---|---|
| SSID | `Hotelnet` |
| Password | Empty |
| Band | 2.4 GHz available |
| Captive portal | None detected |
| Verified | DHCP, DNS, NTP, and HTTPS to Todoist |

Signal strength varied during testing. Use bounded connection attempts, show connection state, and keep a useful offline screen.

Store the SSID and empty password in a gitignored local configuration such as `include/secrets.h`. Do not hardcode even public event configuration into reusable application code.

## HTTPS rules

- Verify the server certificate and hostname before sending credentials or private data.
- Never use `WiFiClientSecure::setInsecure()` with an API token, password, personal data, or private endpoint.
- Use the root CA for the actual API host. Do not assume every API uses Amazon Root CA 1.
- Synchronize time before certificate validation when the TLS library requires a valid clock.
- Use request and connection timeouts.
- Keep response documents bounded and validate fields before using them.
- Release TLS clients and large JSON documents as soon as possible because this board has no PSRAM.

ChoreQuest already verifies Todoist through Amazon Root CA 1. That certificate is specific to Todoist's current certificate chain, not to Hotelnet.

## Runtime design

- Keep WiFi and HTTP lifecycle code in `src/network/` when the project uses that layout.
- Keep API request and response models in the data layer.
- Do not connect or make HTTP requests directly inside an LVGL event callback.
- Queue work and process it from the main loop or a worker task.
- Preserve the offline path and retry with a limit.
- Never print tokens or passwords to serial output.
