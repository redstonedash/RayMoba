#pragma once
static bool isServer = false;
const int KILOBYTE = 1024;
void instantiateServer();
void instantiateClient();
bool readNetwork();
void writeNetwork();
void disconnect();
char* getBuffer();