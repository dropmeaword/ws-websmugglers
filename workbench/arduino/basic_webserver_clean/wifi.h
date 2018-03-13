#ifndef __WIFI_H__
#define __WIFI_H__

#include <DNSServer.h>

enum WifiMode {
    CLIENT = 10,        // station node
    HYBRID_AP = 15,     // station + ap
    ACCESS_POINT = 20,  // ap only
    MESH = 30           // mesh
};

#define DNS_PORT  53

extern IPAddress thisip;

void wifi_init();
bool wifi_connect_as_client(const char *ssid, const char *passw, int timeouts);
bool wifi_create_ap(const char *myssid);

#endif // __WIFI_H__
