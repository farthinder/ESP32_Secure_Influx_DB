/**
    ESP32 InfluxDbSecure: Influxdbsecure.h

    Purpose: Helps with sending measurements to an Influx database.

    @author Tobias Schürg
	
	20181201 -  Updated by Anders Lantz, to support ESP32 and TLS
				Known limitations: CRL and Cert Dates are not checked.
*/
#include "InfluxdbSecure.h"
#include "Arduino.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
/**
 * Construct an InfluxDbSecure instance.
 * @param url - String to influxdb host
 * @param rootCA - const char pointer to trusted Root CA in PEM format
 * @param port - uint16_t the InfluxDb port
 * @param username - String
 * @param password - String
 * @param database - String
 * @param port - uint16_t TCP port used for InfluxDb
 */

Influxdbsecure::Influxdbsecure(String url, const char *rootCA, String username, String password, String database,uint16_t port ) {

 _url = url;
 _port = port;
 _user = username;
 _pass = password;
 _db = database;
 _rootCA = rootCA;
 _host -> setCACert(rootCA);
 
https.begin(*_host, _url,  _port, "/write?u=" + _user + "&p=" + _pass + "&db=" + _db, true);
https.addHeader("Content-Type", "text/plain");

}



/**
 * Prepare a measurement to be sent.
 */
void Influxdbsecure::prepare(InfluxData data) { prepared.push_back(data); }

/**
 * Write all prepared measurements into the db.
 */
boolean Influxdbsecure::write() {
  String data = "";
  for (auto const& i : prepared) {
    data = (data == "") ? (i.toString()) : (data + "\n" + i.toString());
  }
  prepared.clear();
  return write(data);
}

/**
 * Write a single measurement into the db.
 */
boolean Influxdbsecure::write(InfluxData data) { return write(data.toString()); }

/**
 * Send raw data to Influxdbsecure.
 *
 * @see
 * https://github.com/esp8266/Arduino/blob/cc0bfa04d401810ed3f5d7d01be6e88b9011997f/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h#L44-L55
 * for a list of error codes.
 */
boolean Influxdbsecure::write(String data) {
  Serial.print(" --> writing to " + _db + ":\n");
  Serial.println(data);

  int httpResponseCode = https.POST(data);
  Serial.print(" <-- Response: ");
  Serial.print(httpResponseCode);

  String response = https.getString();
  Serial.println(" \"" + response + "\"");

  boolean success;
  if (httpResponseCode == 204) {
    success = true;
  } else {
    Serial.println("#####\nPOST FAILED\n#####");
    success = false;
  }

  https.end();
  return success;
}

