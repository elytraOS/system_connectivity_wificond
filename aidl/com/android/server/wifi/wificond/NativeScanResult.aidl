/*
 * Copyright (C) 2019 The Android Open Source Project
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

package com.android.server.wifi.wificond;

import com.android.server.wifi.wificond.RadioChainInfo;

parcelable NativeScanResult {
    /** SSID of the BSS. */
    byte[] ssid;

    /** BSSID of the BSS. */
    byte[] bssid;

    /**
     * Binary array containing the raw information elements from the
     * probe response/beacon.
     */
    byte[] infoElement;

    /** Frequency in MHz. */
    int frequency;

    /** Signal strength of probe response/beacon in (100 * dBm). */
    int signalMbm;

    /** TSF of the received probe response/beacon. */
    long tsf;

    /**
     * This is a bit mask describing the capabilities of a BSS.
     * See IEEE Std 802.11: 8.4.1.4
     * Bit 0 - ESS
     * Bit 1 - IBSS
     * Bit 2 - CF Pollable
     * Bit 3 - CF-Poll Request
     * Bit 4 - Privacy
     * Bit 5 - Short Preamble
     * Bit 6 - PBCC
     * Bit 7 - Channel Agility
     * Bit 8 - Spectrum Mgmt
     * Bit 9 - QoS
     * Bit 10 - Short Slot Time
     * Bit 11 - APSD
     * Bit 12 - Radio Measurement
     * Bit 13 - DSSS-OFDM
     * Bit 14 - Delayed Block Ack
     * Bit 15 - Immediate Block Ack
     */
    int capability;

    boolean associated;

    RadioChainInfo[] radioChainInfos;
}
