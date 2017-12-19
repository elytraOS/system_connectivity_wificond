/*
 * Copyright (C) 2016 The Android Open Source Project
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

#include "wificond/ap_interface_binder.h"

#include <android-base/logging.h>
#include <wifi_system/hostapd_manager.h>

#include "wificond/ap_interface_impl.h"

using android::net::wifi::IApInterfaceEventCallback;
using android::wifi_system::HostapdManager;

namespace android {
namespace wificond {

ApInterfaceBinder::ApInterfaceBinder(ApInterfaceImpl* impl)
    : impl_{impl}, ap_interface_event_callback_(nullptr) {}

ApInterfaceBinder::~ApInterfaceBinder() {
}

void ApInterfaceBinder::NotifyNumAssociatedStationsChanged(int num_stations) {
  if (ap_interface_event_callback_ != nullptr) {
    ap_interface_event_callback_->onNumAssociatedStationsChanged(num_stations);
  }
}

binder::Status ApInterfaceBinder::startHostapd(
    const sp<IApInterfaceEventCallback>& callback, bool* out_success) {
  *out_success = false;
  if (!impl_) {
    LOG(WARNING) << "Cannot start hostapd on dead ApInterface.";
    return binder::Status::ok();
  }
  *out_success = impl_->StartHostapd();
  if (*out_success) {
    ap_interface_event_callback_ = callback;
  }
  return binder::Status::ok();
}

binder::Status ApInterfaceBinder::stopHostapd(bool* out_success) {
  *out_success = false;
  if (!impl_) {
    LOG(WARNING) << "Cannot stop hostapd on dead ApInterface.";
    return binder::Status::ok();
  }
  *out_success = impl_->StopHostapd();
  ap_interface_event_callback_.clear();
  return binder::Status::ok();
}

binder::Status ApInterfaceBinder::writeHostapdConfig(
    const std::vector<uint8_t>& ssid,
    bool is_hidden,
    int32_t binder_band_type,
    int32_t binder_encryption_type,
    const std::vector<uint8_t>& passphrase,
    bool* out_success) {
  *out_success = false;
  if (!impl_) {
    LOG(WARNING) << "Cannot set config on dead ApInterface.";
    return binder::Status::ok();
  }

  HostapdManager::EncryptionType encryption_type;
  switch (binder_encryption_type) {
    case IApInterface::ENCRYPTION_TYPE_NONE:
      encryption_type = HostapdManager::EncryptionType::kOpen;
      break;
    case IApInterface::ENCRYPTION_TYPE_WPA:
      encryption_type = HostapdManager::EncryptionType::kWpa;
      break;
    case IApInterface::ENCRYPTION_TYPE_WPA2:
      encryption_type = HostapdManager::EncryptionType::kWpa2;
      break;
    default:
      LOG(ERROR) << "Unknown encryption type: " << binder_encryption_type;
      return binder::Status::ok();
  }


  HostapdManager::BandType band_type;
  switch (binder_band_type) {
    case IApInterface::BAND_2G:
      band_type = HostapdManager::BandType::kBand2G;
      break;
    case IApInterface::BAND_5G:
      band_type = HostapdManager::BandType::kBand5G;
      break;
    case IApInterface::BAND_ANY:
      band_type = HostapdManager::BandType::kBandAny;
      break;
    default:
      LOG(ERROR) << "Unknown band type: " << binder_band_type;
      return binder::Status::ok();
  }

  *out_success = impl_->WriteHostapdConfig(
      ssid, is_hidden, band_type, encryption_type, passphrase);

  return binder::Status::ok();
}

binder::Status ApInterfaceBinder::getInterfaceName(std::string* out_name) {
  if (!impl_) {
    LOG(WARNING) << "Cannot get interface name from dead ApInterface";
    return binder::Status::ok();
  }
  *out_name = impl_->GetInterfaceName();
  return binder::Status::ok();
}

binder::Status ApInterfaceBinder::getNumberOfAssociatedStations(
    int* out_num_of_stations) {
  if (!impl_) {
    LOG(WARNING) << "Cannot get number of associated stations "
                 << "from dead ApInterface";
    *out_num_of_stations = -1;
    return binder::Status::ok();
  }
  *out_num_of_stations = impl_->GetNumberOfAssociatedStations();
  return binder::Status::ok();
}

}  // namespace wificond
}  // namespace android
