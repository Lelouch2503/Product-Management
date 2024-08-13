#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include "time.h"
#include "WiFiClientSecure.h"
// SSID and Password
const char *ssid = "Gg";
const char *password = "ggmedi123";

/**** NEED TO CHANGE THIS ACCORDING TO YOUR SETUP *****/
// The REST API endpoint - Change the IP Address
const char *base_rest_url = "http://192.168.191.83:5000/";
WiFiClient client;
HTTPClient http;

HardwareSerial UART(2);
// Thêm định nghĩa cho múi giờ GMT+7
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;
// Read interval
unsigned long previousMillis = 0;
const long readInterval = 5000;

// Struct to represent our Product  record
struct Product
{
  char ID[11];
  char location[20];
  bool status;
  char time[20];
};

// Size of the JSON document. Use the ArduinoJSON JSONAssistant
const int JSON_DOC_SIZE = 768;

/* After s32k144 reset, it use Uart protocol sending "Reload"
  Then esp32 fetch all data on mongodb and 
  send back necessary information to s32k144
*/
void fetchAllProducts() {
  char rest_api_url[200];
  sprintf(rest_api_url, "%sapi/ID", base_rest_url);
  
  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    String payload = http.getString();
    
    DynamicJsonDocument doc(4096);  
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    
    JsonArray array = doc.as<JsonArray>();
    
    for (JsonObject obj : array) {
      String ID;
      String location;
      String statusStr;
      
      if (obj.containsKey("ID")) {
        ID = obj["ID"].as<String>();
        location = obj["location"].as<String>();
        statusStr = obj["status"].as<String>();
      } else if (obj.containsKey("product")) {
        JsonObject product = obj["product"].as<JsonObject>();
        ID = product["ID"].as<String>();
        location = product["location"].as<String>();
        bool status = product["status"].as<bool>();
        statusStr = status ? "in" : "out";
      }
      
      // Construct the message
      String message = "s|" + ID + "|" + location + "|" + statusStr + "|e\n";
      Serial.print(message);
      // Send the message via UART
      UART.print(message);
      
      // Optional: Add a small delay to prevent overwhelming the S32K144
      delay(1000);
    }
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  Serial.print("eom");
  UART.print("eom");
}
// HTTP GET Call
StaticJsonDocument<JSON_DOC_SIZE> callHTTPGet(const char *sensor_id)
{
  char rest_api_url[200];
  // Calling our API server
  sprintf(rest_api_url, "%sapi/ID?ID=%s", base_rest_url, sensor_id);
  Serial.println(rest_api_url);

  http.useHTTP10(true);
  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.GET();
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  StaticJsonDocument<JSON_DOC_SIZE> doc;

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Received payload:");
    Serial.println(payload);

    if (payload.length() > 0) {
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
      }
    } else {
      Serial.println("Received empty payload");
    }
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return doc;
}
// Extract LED records
Product extractProductInfo(const char *ID)
{
  StaticJsonDocument<JSON_DOC_SIZE> doc = callHTTPGet(ID);
  if (doc.isNull() || doc.size() > 1)
    return {}; // or LED{}
  for (JsonObject item : doc.as<JsonArray>())
  {

    const char *ID = item["ID"];      // "led_1"
    const char *location = item["location"];       // "Inside the bedroom"
    bool status = item["status"];                // true
    const char *time = item["time"];               // "toggle"


    Product productTemp = {};
    strcpy(productTemp.ID, ID);
    strcpy(productTemp.time, time);
    strcpy(productTemp.location, location);
    productTemp.status = status;

    return productTemp;
  }
  return {}; // or LED{}
}

// Send product INFO using HTTP PUT
void sendProductInfo(const char *objectId, Product product)
{
  char rest_api_url[200];
  // Calling our API server
  sprintf(rest_api_url, "%sapi/ID/%s", base_rest_url, objectId);
  Serial.println(rest_api_url);

  // Prepare our JSON data
  String jsondata = "";
  StaticJsonDocument<JSON_DOC_SIZE> doc;
  JsonObject readings = doc.createNestedObject("product");
  readings["ID"] = product.ID;
  readings["location"] = product.location;
  readings["status"] = product.status;
  readings["time"] = product.time;

  serializeJson(doc, jsondata);
  Serial.println("JSON Data...");
  Serial.println(jsondata);

  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");

  // Send the PUT request
  int httpResponseCode = http.PUT(jsondata);
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    http.end();
  }
}

// Send product INFO using HTTP PUT
void addProductInfo(const char *objectId, Product product)
{
  char rest_api_url[200];
  // Calling our API server
  sprintf(rest_api_url, "%sapi/ID", base_rest_url);
  Serial.println(rest_api_url);

  // Prepare our JSON data
  String jsondata = "";
  StaticJsonDocument<JSON_DOC_SIZE> doc;
  JsonObject readings = doc.createNestedObject("product");
  readings["ID"] = product.ID;
  readings["location"] = product.location;
  readings["status"] = product.status;
  readings["time"] = product.time;

  serializeJson(doc, jsondata);
  Serial.println("JSON Data...");
  Serial.println(jsondata);

  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");

  // Send the PUT request
  int httpResponseCode = http.POST(jsondata);
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    http.end();
  }
}

void deleteProductFromMongoDB(String cardID) {
  char rest_api_url[200];
  sprintf(rest_api_url, "%sapi/ID/%s", base_rest_url, cardID.c_str());
  
  http.begin(client, rest_api_url);
  
  int httpResponseCode = http.sendRequest("DELETE");
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error on sending DELETE request: " + String(httpResponseCode));
  }
  
  http.end();
}

Product handlerMess(String data)
{
    Product product;
    
    // Kiểm tra định dạng gói tin
    if (data.charAt(0) != 's' || data.charAt(data.length() - 1) != 'e') {
        Serial.println("I"); // "I" stand for invalid format
        return product;
    }
    else
    {
        Serial.println("V"); // "V" stand for valid format
    }
    
    // Tách các phần của gói tin
    int firstDelimiter = data.indexOf('|');
    int secondDelimiter = data.indexOf('|', firstDelimiter + 1);
    int thirdDelimiter = data.indexOf('|', secondDelimiter + 1);
    
    // Trích xuất ID - ensure capturing all characters
    String id = data.substring(firstDelimiter + 1, secondDelimiter);
    strncpy(product.ID, id.c_str(), sizeof(product.ID));
    product.ID[sizeof(product.ID)-1] = '\0';
    
    // Trích xuất location
    String loc = data.substring(secondDelimiter + 1, thirdDelimiter);
    strncpy(product.location, loc.c_str(), sizeof(product.location) - 1);
    product.location[sizeof(product.location) - 1] = '\0';
    
    // Trích xuất status
    String status = data.substring(thirdDelimiter + 1, data.length() - 2);
    product.status = (status == "1");
    
    // Get current time
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
    }

    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
    
    // Assign time to newProduct
    strcpy(product.time, timeString);
    
    return product;
}

void handleUARTInput() {
  if (UART.available()) {
    String input = UART.readStringUntil('\n');
    input.trim();
    Serial.println(input);
    if (input == "Reload") {
      Serial.println("Received Reload command. Fetching all products...");
      fetchAllProducts();
    } 
    else if (input.startsWith("d|") && input.endsWith("|e")) {
      // Handle delete packet
      String cardID = input.substring(2, input.length() - 2);
      deleteProductFromMongoDB(cardID);
    }
    else if (input.startsWith("s|") && input.endsWith("|e")) {
      // Handle other UART inputs as before
      Product newProduct = handlerMess(input);
      Serial.println(input);
      Serial.println(newProduct.ID);
      Serial.println(newProduct.location);
      Serial.println(newProduct.status);
      Serial.println(newProduct.time);  // Print the time

      // Kiểm tra sự tồn tại của sản phẩm
      StaticJsonDocument<JSON_DOC_SIZE> doc = callHTTPGet(newProduct.ID);
      
      if (doc.isNull() || doc.size() == 0) {
        // Sản phẩm chưa tồn tại, thêm mới
        Serial.println("Adding new product");
        addProductInfo(newProduct.ID, newProduct);
      } else {
        // Sản phẩm đã tồn tại, cập nhật
        Serial.println("Updating existing product");
        sendProductInfo(newProduct.ID, newProduct);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  UART.begin(9600, SERIAL_8N1, 16, 17); // UART1: TX trên GPIO16, RX trên GPIO17
  for (uint8_t t = 2; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.begin(ssid, password);

  // Cập nhật cấu hình thời gian cho GMT+7
  configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  unsigned long currentMillis = millis();

  if(UART.available() > 0)
  {
    handleUARTInput();
  }
}