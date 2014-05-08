#include "target.h"

void getTargetDimensions(Target *target, uint32_t *width, uint32_t *height)
{
  if (target->clientAreaSet) {
    *width = target->clientArea.x2 - target->clientArea.x1;
    *height = target->clientArea.y2 - target->clientArea.y1;
    return;
  }
  
  switch (target->kind) {
    case WindowKind:
      break; //FIXME: OS-Specific Window...
    case RawKind:
      *width = target->rawData.width;
      *height = target->rawData.height;
      break;
    case BitmapKind:
      break; //FIXME: Bitmap type...
    case EIOSKind:
      *width = target->eiosData.width;
      *height = target->eiosData.height;
      break;
  }
}

bool setClientArea(Target *target, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
  uint32_t width = 0, height = 0;
  getTargetDimensions(target, &width, &height);
  
  if (((x2 - x1) > width) || ((y2 - y1) > height))
    return false;
  
  target->clientArea.x1 = x1;
  target->clientArea.y1 = y1;
  target->clientArea.x2 = x2;
  target->clientArea.y2 = y2;
  target->clientAreaSet = true;
  return true;
}

void resetClientArea(Target *target)
{
  target->clientAreaSet = false;
  memset(&(target->clientArea), 0, sizeof(ClientArea));
}
