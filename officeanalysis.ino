// This #include statement was automatically added by the Spark IDE.
#include "HttpClient/HttpClient.h"

unsigned int interval = 1000; // send a request every 3000 ms

unsigned int nextTime = 0;

unsigned int requestNumber = 0;

HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //{ "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*" },
    { "Content-Type", "application/x-www-form-urlencoded" },
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    Serial.begin(9600);
    
    request.hostname = "oaaas.meteor.com";
    request.port = 80;
    request.path = "/api/sensordata";
}

void loop() {
    if (millis() < nextTime) {
        return;
    }
    
    requestNumber++;
    
    if (requestNumber % 2 == 0) {
        request.body = "value=18&integrationId=tQqJAmuokkbkbpuux";
    } else {
        request.body = "value=20&integrationId=tQqJAmuokkbkbpuux";
    }
    
    http.post(request, response, headers);
    
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);
    
    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
    
    nextTime += interval;
}
