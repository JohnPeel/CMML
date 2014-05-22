#include "eios.h"

void *loadModule(const char *libname)
{
    #if defined _WIN32 || defined_WIN64
    return LoadLibrary(libname);
    #else
    return dlopen(libname, RTLD_LAZY);
    #endif
}

int freeModule(void *module)
{
    #if defined _WIN32 || defined _WIN64
    return FreeLibrary(module);
    #else
    return dlclose(module);
    #endif
}

void *getFuncAddress(void *module, const char *proc_name)
{
    #if defined _WIN32 || defined _WIN64
    return GetProcAddress(module, proc_name);
    #else
    return getFuncAddress(module, proc_name);
    #endif
}

bool loadEIOSClient(EIOSClient *client, char *path)
{
    memset(client, 0, sizeof(EIOSClient));
    client->libHandle = loadModule(path);

    if (client->libHandle == NULL)
        return false;

    client->requestTarget = getFuncAddress(client->libHandle, "EIOS_RequestTarget");
    client->releaseTarget = getFuncAddress(client->libHandle, "EIOS_ReleaseTarget");

    client->getTargetDimensions = getFuncAddress(client->libHandle, "EIOS_GetTargetDimensions");
    client->getTargetPosition = getFuncAddress(client->libHandle, "EIOS_GetTargetPosition");

    client->getImageBuffer = getFuncAddress(client->libHandle, "EIOS_GetImageBuffer");
    client->updateImageBuffer = getFuncAddress(client->libHandle, "EIOS_UpdateImageBuffer");
    client->updateImageBufferBox = getFuncAddress(client->libHandle, "EIOS_UpdateImageBufferBounds");

    client->getMousePosition = getFuncAddress(client->libHandle, "EIOS_GetMousePosition");
    client->moveMouse = getFuncAddress(client->libHandle, "EIOS_MoveMouse");
    client->scrollMouse = getFuncAddress(client->libHandle, "EIOS_ScrollMouse");
    client->holdMouse = getFuncAddress(client->libHandle, "EIOS_HoldMouse");
    client->releaseMouse = getFuncAddress(client->libHandle, "EIOS_ReleaseMouse");
    client->isMouseButtonHeld = getFuncAddress(client->libHandle, "EIOS_IsMouseButtonHeld");

    client->sendString = getFuncAddress(client->libHandle, "EIOS_SendString");
    client->holdKey = getFuncAddress(client->libHandle, "EIOS_HoldKey");
    client->releaseKey = getFuncAddress(client->libHandle, "EIOS_ReleaseKey");
    client->isKeyHeld = getFuncAddress(client->libHandle, "EIOS_IsKeyHeld");
    client->getKeyCode = getFuncAddress(client->libHandle, "EIOS_GetKeyCode");

    return true;
}

void unloadEIOSClient(EIOSClient *client)
{
    freeModule(client->libHandle);
    memset(client, 0, sizeof(EIOSClient));
}
