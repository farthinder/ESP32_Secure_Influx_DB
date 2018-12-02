# ESP32_Secure_Influx_DB
Simple library for sending measurements securely via TLS from ESP32 to an InfluxDB with a single network request.

This is a dirty and quick rewrite of https://github.com/tobiasschuerg/ESP8266_Influx_DB to solve ESP32 and TLS support, it only verifies that the Certificate is signed by the correct Root CA, not CRL or Certificate dates. 
