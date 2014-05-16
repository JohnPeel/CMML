#include <stdio.h>
#include "target.h"
#include "eios.h"

typedef void *(*SpawnClient)(char *java_exec, char *remote_path, char *root, char *params, int width, int height, char *initseq, char *useragent, char *javaargs, char *plugins);

int main(int argc, char **argv) {
  EIOSClient client;

#if defined _WIN32 || defined _WIN64
  if (loadEIOSClient(&client, "libsmartremote64.dll")) {
#else
  if (loadEIOSClient(&client, "./libsmartremote64.so")) {
#endif
    printf("Client: %p\n", client.libHandle);

    Target target;
    target.kind = EIOSKind;
    target.eiosData.client = &client;

    SpawnClient spawnClient = getFuncAddress(client.libHandle, "exp_spawnClient");

    target.eiosData.target = spawnClient("java", ".", "http://world37.runescape.com/", ",f681985954784915908", 765, 553, "s", NULL, NULL, NULL);

    uint32_t width = 0, height = 0;
    getTargetDimensions(&target, &width, &height);
    printf("%ux%u\n", width, height);

    unloadEIOSClient(&client);
  } else
    printf("Failed to load libsmartremote64...\n");
  return 0;
}
