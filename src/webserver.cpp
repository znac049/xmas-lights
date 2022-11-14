#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPmDNS.h>
#include <Preferences.h>

#include "defs.h"
#include "Settings.h"
#include "html.html"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String decodeAction(const char *args) {
    String res = args;
    int query = res.indexOf('?');

    if (query != -1) {
        res = res.substring(0, query);
    }

    //Serial.println("Decoded action: " + res);
    return res;
}

String getArg(const char *args, const char *arg, const char *def) {
    String str = args;
    int sep = str.indexOf('?');

    if (sep == -1) {
        return def;
    }

    while (sep != -1) {
        String elem;
        int eq;
        String key, val;

        str = str.substring(sep+1);
        sep = str.indexOf('&');
        if (sep != -1) {
            elem = str.substring(0, sep);
        }
        else {
            elem = str;
        }

        eq = elem.indexOf('=');
        if (eq != -1) {
            key = elem.substring(0, eq);
            val = elem.substring(eq+1);

            if (key.equals(arg)) {
                return val;
            }
        }
        else {
            key = elem;
            if (key.equals(arg)) {
                return def;
            }
        }
    }

    return def;
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    String action;

    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        action = decodeAction((const char *) data);

        if (action.equals("action")) {
            ws.textAll(String(42));
        }
        else {
            Serial.println("Unknown command on websocket: " + action);
        }
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
    
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
    
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
    
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
        default:
            break;
    }
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

String lookupMacro(const String& macroName)
{
    String res = "";

    Serial.println(macroName);
    if (macroName == "SOMENAME") {
    }
    else {
        res = "????";
    }

    return res;
}

void setupWebserver()
{
    initWebSocket();

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, lookupMacro);
    });

    AsyncElegantOTA.begin(&server);
    server.begin();
}

void cleanupWebsocketClients()
{
    ws.cleanupClients();
}