/*
 * Copyright (C) 2011 The Android Open Source Project
 * Copyright (C) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright (C) 2018 Boundary Devices LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <linux/input.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "device.h"
#include "screen_ui.h"

const char* ITEMS[] = { "reboot system now",
                        "apply update from ADB",
                        "wipe data/factory reset",
                        "wipe cache partition",
                        NULL };

class ImxDevice : public Device {
  public:
    ImxDevice() :
        Device(new ScreenRecoveryUI) {
    }

    int HandleMenuKey(int key, bool visible) {
        if (!visible) {
            return kNoAction;
        }

        // If 3 buttons availables, use their values as expected
        if (GetUI()->HasThreeButtons()) {
            switch (key) {
            case KEY_DOWN:
            case KEY_VOLUMEDOWN:
                return kHighlightDown;

            case KEY_UP:
            case KEY_VOLUMEUP:
                return kHighlightUp;

            case KEY_ENTER:
            case KEY_POWER:
                return kInvokeItem;

            default:
                return kNoAction;
            }
        }

        // If only one button is available, any button == cycles the highlight
        // When long press, the key is changed to KEY_ENTER, so select item
        return (key == KEY_ENTER) ? kInvokeItem : kHighlightDown;
    }

    BuiltinAction InvokeMenuItem(int menu_position) {
        switch (menu_position) {
          case 0: return REBOOT;
          case 1: return APPLY_ADB_SIDELOAD;
          case 2: return WIPE_DATA;
          case 3: return WIPE_CACHE;
          default: return NO_ACTION;
        }
    }

    const char* const* GetMenuItems() { return ITEMS; }

};

Device* make_device() {
    return new ImxDevice;
}
