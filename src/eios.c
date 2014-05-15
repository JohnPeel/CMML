#include "eios.h"

bool loadEIOSClient(EIOSClient *client, char *path)
{
  memset(client, 0, sizeof(EIOSClient));
  client->libHandle = dlopen(path, RTLD_LAZY);
  
  if (client->libHandle == NULL)
    return false;
  
  client->requestTarget = dlsym(client->libHandle, "EIOS_RequestTarget");
  client->releaseTarget = dlsym(client->libHandle, "EIOS_ReleaseTarget");
  
  client->getTargetDimensions = dlsym(client->libHandle, "EIOS_GetTargetDimensions");
  client->getTargetPosition = dlsym(client->libHandle, "EIOS_GetTargetPosition");
  
  client->getImageBuffer = dlsym(client->libHandle, "EIOS_GetImageBuffer");
  client->updateImageBuffer = dlsym(client->libHandle, "EIOS_UpdateImageBuffer");
  client->updateImageBufferBox = dlsym(client->libHandle, "EIOS_UpdateImageBufferBounds");
  
  client->getMousePosition = dlsym(client->libHandle, "EIOS_GetMousePosition");
  client->moveMouse = dlsym(client->libHandle, "EIOS_MoveMouse");
  client->scrollMouse = dlsym(client->libHandle, "EIOS_ScrollMouse");
  client->holdMouse = dlsym(client->libHandle, "EIOS_HoldMouse");
  client->releaseMouse = dlsym(client->libHandle, "EIOS_ReleaseMouse");
  client->isMouseButtonHeld = dlsym(client->libHandle, "EIOS_IsMouseButtonHeld");
  
  client->sendString = dlsym(client->libHandle, "EIOS_SendString");
  client->holdKey = dlsym(client->libHandle, "EIOS_HoldKey");
  client->releaseKey = dlsym(client->libHandle, "EIOS_ReleaseKey");
  client->isKeyHeld = dlsym(client->libHandle, "EIOS_IsKeyHeld");
  client->getKeyCode = dlsym(client->libHandle, "EIOS_GetKeyCode");
  
  return true;
}

void unloadEIOSClient(EIOSClient *client)
{
  dlclose(client->libHandle);
  memset(client, 0, sizeof(EIOSClient));
}