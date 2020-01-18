/*
 * Copyright (C) 2020 The Android Open Source Project
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

#include "device_wiphy_capabilities.h"

#include <android-base/logging.h>

#include "wificond/parcelable_utils.h"

using android::status_t;

namespace android {
namespace net {
namespace wifi {
namespace wificond {

DeviceWiphyCapabilities::DeviceWiphyCapabilities() {
     is80211nSupported_ = false;
     is80211acSupported_ = false;
     is80211axSupported_ = false;
 }

status_t DeviceWiphyCapabilities::writeToParcel(::android::Parcel* parcel) const {
  RETURN_IF_FAILED(parcel->writeInt32(is80211nSupported_ ? 1 : 0));
  RETURN_IF_FAILED(parcel->writeInt32(is80211acSupported_ ? 1 : 0));
  RETURN_IF_FAILED(parcel->writeInt32(is80211axSupported_ ? 1 : 0));

  return ::android::OK;
}

status_t DeviceWiphyCapabilities::readFromParcel(const ::android::Parcel* parcel) {
  int data;
  RETURN_IF_FAILED(parcel->readInt32(&data));
  is80211nSupported_ = data != 0;

  RETURN_IF_FAILED(parcel->readInt32(&data));
  is80211acSupported_ = data != 0;

  RETURN_IF_FAILED(parcel->readInt32(&data));
  is80211axSupported_ = data != 0;

  return ::android::OK;
}

}  // namespace wificond
}  // namespace wifi
}  // namespace net
}  // namespace android
