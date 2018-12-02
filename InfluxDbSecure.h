
/**
    ESP32 InfluxDbSecure: Influxdbsecure.h

    Purpose: Helps with sending measurements to an Influx database.

    @author Tobias Schürg
	
	20181201 - Updated by Anders Lantz, to support ESP32 and TLS
*/

#include <HTTPClient.h>
#include <list>
#include "Arduino.h"
#include <WiFiClientSecure.h>
#include "InfluxData.h"

class Influxdbsecure {
 public:
 Influxdbsecure(String url, const char *rootCA, String username, String password, String database, uint16_t port = 8086);


  void prepare(InfluxData data);
  boolean write();

  boolean write(InfluxData data);
  boolean write(String data);
 
 private:
  HTTPClient https;
  WiFiClientSecure *_host = new WiFiClientSecure;
  String _url;
  
  const char *_rootCA;
  
  uint16_t _port;
  String _db;
  String _user;
  String _pass;
  std::list<InfluxData> prepared;
  
  void begin();
};
