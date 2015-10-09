#include "WebPages.h"

#define MAX_PARAM_LENGTH 50

static void setupWebServer() {
    server.on("/cmd", handleCommand);
    server.on("/style.css", handleStylePage);
    server.on("/", handleMainPage);

    server.onNotFound(handleNotFound);

    server.begin();
}

static void handleStylePage() {
    server.send(200, F("text/css"), stylecssPage);
}

static void handleMainPage() {
    server.send(200, F("text/html"), mainhtmPage);
}

static void handleCommand()
{
  if (server.hasArg("action")) {
    // Parse args
    String cmd = server.arg("action");
    char arg[MAX_PARAM_LENGTH];
    char temp[MAX_PARAM_LENGTH];
    if (server.hasArg("p1")) {
      server.arg("p1").toCharArray(arg, MAX_PARAM_LENGTH);
      urldecode2(temp, arg);
      cmd += " " + String(temp);
    }
    if (server.hasArg("p2")) {
      server.arg("p2").toCharArray(arg, MAX_PARAM_LENGTH);
      urldecode2(temp, arg);
      cmd += " " + String(temp);
    }

    if (cmdQ.isFull()) {
        server.send(200, F("text/plain"), F("err"));
    } else {
        parseCommand(cmd);
        server.send(200, F("text/plain"), "OK:"+cmd);
    }
  } else {
    server.send(200, F("text/plain"), F("err"));
  }
}

static void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}

static void urldecode2(char *dst, const char *src)
{
  char a, b;
  while (*src) {
    if ((*src == '%') &&
      ((a = src[1]) && (b = src[2])) &&
      (isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
        a -= 'a' - 'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a' - 'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';
      *dst++ = 16 * a + b;
      src += 3;
    } else {
        *dst++ = *src++;
    }
  }
  *dst++ = '\0';
}
