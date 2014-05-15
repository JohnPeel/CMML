#include "target.h"

void getTargetDimensions(Target *target, uint32_t *width, uint32_t *height) {
  if (target->clientAreaSet) {
    *width = target->clientArea.x2 - target->clientArea.x1;
    *height = target->clientArea.y2 - target->clientArea.y1;
    return;
  }

  switch (target->kind) {
    case RawKind:
      *width = target->rawData.width;
      *height = target->rawData.height;
      break;
    case EIOSKind:
      if (target->eiosData.client->getTargetDimensions != NULL) //Cache this...
        target->eiosData.client->getTargetDimensions(target->eiosData.target, width, height);
      break;
  }
}

void getTargetPosition(Target *target, uint32_t *left, uint32_t *top) {
  switch (target->kind) {
    case RawKind:
      *left = 0;
      *top = 0;
      break;
    case EIOSKind:
      if (target->eiosData.client->getTargetPosition != NULL)
        target->eiosData.client->getTargetPosition(target->eiosData.target, top, left);
      break;
  }
}

Color getTargetPixel(Target *target, uint32_t x, uint32_t y) {
  TargetData data = getTargetData(target, x, y, 1, 1);
  Color color = data.data[0].color;
  freeTargetData(target);
  return color;
}

TargetData getTargetData(Target *target, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  TargetData data = {0,};
  uint32_t _ = 0, _x = x, _y = y;

  if (target->clientAreaSet) {
    _x += target->clientArea.x1;
    _y += target->clientArea.y1;
  }

  switch (target->kind) {
    case RawKind:
      data.data = target->rawData.data;
    case EIOSKind:
      if (target->eiosData.client->updateImageBufferBox != NULL)
        target->eiosData.client->updateImageBufferBox(target->eiosData.target, x, y, x + width, y + height);
      else if (target->eiosData.client->updateImageBuffer != NULL)
        target->eiosData.client->updateImageBuffer(target->eiosData.target);

      data.data = target->eiosData.buffer;
      break;
  }

  getTargetDimensions(target, &data.rowWidth, &_);
  data.incData = data.rowWidth - width;

  data.data += _y * data.rowWidth + _x;

  if (target->clientAreaSet)
    data.incData += data.rowWidth - (target->clientArea.x2 - target->clientArea.x1);

  return data;
}

void freeTargetData(Target *target) {
  switch (target->kind) {
    case RawKind:
    case EIOSKind:
      break;
  }
}

void getTargetMousePos(Target *target, uint32_t *x, uint32_t *y) {
  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      if (target->eiosData.client->getMousePosition != NULL)
        target->eiosData.client->getMousePosition(target->eiosData.target, x, y);
      break;
  }
}

void setTargetMousePos(Target *target, uint32_t x, uint32_t y) {
  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      if (target->eiosData.client->moveMouse != NULL)
        target->eiosData.client->moveMouse(target->eiosData.target, x, y);
      break;
  }
}

MouseAction getTargetMouseAction(Target *target, MouseButton button) {
  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      if (target->eiosData.client->isMouseButtonHeld != NULL) {
        if (target->eiosData.client->isMouseButtonHeld(target->eiosData.target, button))
          return PressMouse;
        return ReleaseMouse;
      }
      break;
  }
  return UnknownMouse;
}

void setTargetMouseAction(Target *target, MouseAction action, MouseButton button) {
  uint32_t x = 0, y = 0;

  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      getTargetMousePos(target, &x, &y);

      switch (action) {
        case UnknownMouse:
          break;
        case PressMouse:
          if (target->eiosData.client->holdMouse != NULL)
            target->eiosData.client->holdMouse(target->eiosData.target, x, y, button);
          break;
        case ReleaseMouse:
          if (target->eiosData.client->releaseMouse != NULL)
            target->eiosData.client->releaseMouse(target->eiosData.target, x, y, button);
          break;
      }
      break;
  }
}

KeyAction getTargetKeyAction(Target *target, uint32_t key) {
  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      if (target->eiosData.client->isKeyHeld != NULL) {
        if (target->eiosData.client->isKeyHeld(target->eiosData.target, key))
          return PressKey;
        return ReleaseKey;
      }
      break;
  }
  return UnknownKey;
}

void setTargetKeyAction(Target *target, KeyAction action, uint32_t key) {
  switch (target->kind) {
    case RawKind:
      break;
    case EIOSKind:
      switch (action) {
        case UnknownKey:
          break;
        case PressKey:
          if (target->eiosData.client->holdKey != NULL)
            target->eiosData.client->holdKey(target->eiosData.target, key);
          break;
        case ReleaseKey:
          if (target->eiosData.client->releaseKey != NULL)
            target->eiosData.client->releaseKey(target->eiosData.target, key);
          break;
      }
      break;
  }
}

bool setTargetClientArea(Target *target, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
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

void resetTargetClientArea(Target *target) {
  target->clientAreaSet = false;
  memset(&(target->clientArea), 0, sizeof(ClientArea));
}
