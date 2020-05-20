// Copyright 2018 Silicon Laboratories, Inc.
//
//

/// @file rail_config.c
/// @brief RAIL Configuration
/// @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
// =============================================================================
//
//  WARNING: Auto-Generated Radio Config  -  DO NOT EDIT
//  Radio Configurator Version: 2.12.8
//  RAIL Adapter Version: 2.0.7
//  RAIL Compatibility: 2.x
//
// =============================================================================
#include "em_common.h"
#include "rail_config.h"

static const uint8_t generated_irCalConfig[] = {
  24, 63, 1, 6, 4, 16, 1, 0, 0, 1, 1, 6, 0, 16, 39, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0
};

static const uint32_t generated_phyInfo[] = {
  2UL,
  0x00666666UL, // 102.4
  (uint32_t) NULL,
  (uint32_t) generated_irCalConfig,
#ifdef RADIO_CONFIG_ENABLE_TIMING
  (uint32_t) &generated_timing,
#else
  (uint32_t) NULL,
#endif
  0x00000000UL,
};

const uint32_t generated[] = {
  0x01040FF0UL, (uint32_t) generated_phyInfo,
  /* 0FF4 */ 0x00000000UL,
  /* 0FF8 */ 0x0003C000UL,
  /* 0FFC */ 0x0003C00FUL,
  0x00020004UL, 0x00000000UL,
  /* 0008 */ 0x00000000UL,
  0x00020018UL, 0x0000000FUL,
  /* 001C */ 0x00000000UL,
  0x00070028UL, 0x00000000UL,
  /* 002C */ 0x00000000UL,
  /* 0030 */ 0x00000000UL,
  /* 0034 */ 0x00000000UL,
  /* 0038 */ 0x00000000UL,
  /* 003C */ 0x00000000UL,
  /* 0040 */ 0x00000700UL,
  0x00010048UL, 0x00000000UL,
  0x00020054UL, 0x00000000UL,
  /* 0058 */ 0x00000000UL,
  0x000400A0UL, 0x00004CFFUL,
  /* 00A4 */ 0x00000000UL,
  /* 00A8 */ 0x00004DFFUL,
  /* 00AC */ 0x00000000UL,
  0x00012000UL, 0x00000744UL,
  0x00012010UL, 0x00000000UL,
  0x00012018UL, 0x0000A001UL,
  0x00013008UL, 0x0000AC3FUL,
  0x00023030UL, 0x00104924UL,
  /* 3034 */ 0x00000001UL,
  0x00013040UL, 0x00000000UL,
  0x000140A0UL, 0x0F00277AUL,
  0x000140F4UL, 0x00001020UL,
  0x00024134UL, 0x00000880UL,
  /* 4138 */ 0x000087E6UL,
  0x00024140UL, 0x0088006DUL,
  /* 4144 */ 0x1153E6C0UL,
  0x00156014UL, 0x00000010UL,
  /* 6018 */ 0x04000000UL,
  /* 601C */ 0x0002000FUL,
  /* 6020 */ 0x000030C8UL,
  /* 6024 */ 0x000C5000UL,
  /* 6028 */ 0x03000000UL,
  /* 602C */ 0x00000000UL,
  /* 6030 */ 0x00FF04C8UL,
  /* 6034 */ 0x000008A2UL,
  /* 6038 */ 0x00020001UL,
  /* 603C */ 0x00140012UL,
  /* 6040 */ 0x0000B16FUL,
  /* 6044 */ 0x00000000UL,
  /* 6048 */ 0x1DE00714UL,
  /* 604C */ 0x00000000UL,
  /* 6050 */ 0x002B03F1UL,
  /* 6054 */ 0x008E905AUL,
  /* 6058 */ 0x000004CDUL,
  /* 605C */ 0x22140A04UL,
  /* 6060 */ 0x504B4133UL,
  /* 6064 */ 0x00000000UL,
  0x00037014UL, 0x000270F8UL,
  /* 7018 */ 0x00000300UL,
  /* 701C */ 0x82730060UL,
  0x00017028UL, 0x01800000UL,
  0x00027048UL, 0x00003D3CUL,
  /* 704C */ 0x000019BCUL,
  0x00037070UL, 0x00020105UL,
  /* 7074 */ 0x00000433UL,
  /* 7078 */ 0x00552300UL,

  0xFFFFFFFFUL,
};

RAIL_ChannelConfigEntryAttr_t generated_entryAttr = {
  { 0xFFFFFFFFUL }
};

const RAIL_ChannelConfigEntry_t generated_channels[] = {
  {
    .phyConfigDeltaAdd = NULL,
    .baseFrequency = 2450000000,
    .channelSpacing = 1000000,
    .physicalChannelOffset = 0,
    .channelNumberStart = 0,
    .channelNumberEnd = 20,
    .maxPower = RAIL_TX_POWER_MAX,
    .attr = &generated_entryAttr
  },
};

const RAIL_ChannelConfig_t generated_channelConfig = {
  generated,
  NULL,
  generated_channels,
  1
};
const RAIL_ChannelConfig_t *channelConfigs[] = {
  &generated_channelConfig,
};

//        _  _
//       | )/ )         Wireless
//    \\ |//,' __       Application
//    (")(_)-"()))=-    Software
//       (\\            Platform
