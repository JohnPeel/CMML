#include "eios.h"

bool loadEIOSClient(EIOSClient *client, char *path)
{
    memset(client, 0, sizeof(EIOSClient));
    client->libHandle = loadModule(path);

    if (client->libHandle == NULL)
        return false;

    client->requestTarget = getModuleFunc(client->libHandle, "EIOS_RequestTarget");
    client->releaseTarget = getModuleFunc(client->libHandle, "EIOS_ReleaseTarget");

    client->getTargetDimensions = getModuleFunc(client->libHandle, "EIOS_GetTargetDimensions");
    client->getTargetPosition = getModuleFunc(client->libHandle, "EIOS_GetTargetPosition");

    client->getImageBuffer = getModuleFunc(client->libHandle, "EIOS_GetImageBuffer");
    client->updateImageBuffer = getModuleFunc(client->libHandle, "EIOS_UpdateImageBuffer");
    client->updateImageBufferBox = getModuleFunc(client->libHandle, "EIOS_UpdateImageBufferBounds");

    client->getMousePosition = getModuleFunc(client->libHandle, "EIOS_GetMousePosition");
    client->moveMouse = getModuleFunc(client->libHandle, "EIOS_MoveMouse");
    client->scrollMouse = getModuleFunc(client->libHandle, "EIOS_ScrollMouse");
    client->holdMouse = getModuleFunc(client->libHandle, "EIOS_HoldMouse");
    client->releaseMouse = getModuleFunc(client->libHandle, "EIOS_ReleaseMouse");
    client->isMouseButtonHeld = getModuleFunc(client->libHandle, "EIOS_IsMouseButtonHeld");

    client->sendString = getModuleFunc(client->libHandle, "EIOS_SendString");
    client->holdKey = getModuleFunc(client->libHandle, "EIOS_HoldKey");
    client->releaseKey = getModuleFunc(client->libHandle, "EIOS_ReleaseKey");
    client->isKeyHeld = getModuleFunc(client->libHandle, "EIOS_IsKeyHeld");
    client->getKeyCode = getModuleFunc(client->libHandle, "EIOS_GetKeyCode");

    return true;
}

void unloadEIOSClient(EIOSClient *client)
{
    freeModule(client->libHandle);
    memset(client, 0, sizeof(EIOSClient));
}
