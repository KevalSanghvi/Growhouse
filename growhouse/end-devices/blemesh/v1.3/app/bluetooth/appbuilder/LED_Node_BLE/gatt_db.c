// Copyright 2019 Silicon Laboratories, Inc.
//
//

/********************************************************************
 * Autogenerated file, do not edit.
 *******************************************************************/

#include <stdint.h>
#include "bg_gattdb_def.h"

#ifdef __GNUC__
#define GATT_HEADER(F) F __attribute__ ((section (".gatt_header"))) 
#define GATT_DATA(F) F __attribute__ ((section (".gatt_data"))) 
#else
#ifdef __ICCARM__
#define GATT_HEADER(F) _Pragma("location=\".gatt_header\"") F 
#define GATT_DATA(F) _Pragma("location=\".gatt_data\"") F 
#else
#define GATT_HEADER(F) F 
#define GATT_DATA(F) F 
#endif
#endif

GATT_DATA(const uint16_t bg_gattdb_data_uuidtable_16_map [])=
{
    0x2800,
    0x2801,
    0x2803,
    0x1800,
    0x2a00,
    0x2a01,
    0x180a,
    0x2a29,
    0x1827,
    0x2adb,
    0x2adc,
    0x1828,
    0x2add,
    0x2ade,
    0x1801,
    0x2a05,
    0x2902,
};

GATT_DATA(const uint8_t bg_gattdb_data_uuidtable_128_map [])=
{
0x9b, 0x61, 0x94, 0x5d, 0xc0, 0x68, 0x18, 0xac, 0x0a, 0x4d, 0x6b, 0xfb, 0xeb, 0xda, 0x4e, 0x6c, 
0xd8, 0x55, 0x1c, 0x36, 0x13, 0xbc, 0xa0, 0xae, 0x8b, 0x4d, 0x62, 0xf0, 0x39, 0x5a, 0x79, 0x05, 
0xf0, 0x19, 0x21, 0xb4, 0x47, 0x8f, 0xa4, 0xbf, 0xa1, 0x4f, 0x63, 0xfd, 0xee, 0xd6, 0x14, 0x1d, 
0x63, 0x60, 0x32, 0xe0, 0x37, 0x5e, 0xa4, 0x88, 0x53, 0x4e, 0x6d, 0xfb, 0x64, 0x35, 0xbf, 0xf7, 
};




GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_32 ) = {
	.properties=0x08,
	.index=8,
	.max_len=0,
	.data=NULL,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_31 ) = {
	.len=19,
	.data={0x08,0x21,0x00,0x63,0x60,0x32,0xe0,0x37,0x5e,0xa4,0x88,0x53,0x4e,0x6d,0xfb,0x64,0x35,0xbf,0xf7,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_30 ) = {
	.len=16,
	.data={0xf0,0x19,0x21,0xb4,0x47,0x8f,0xa4,0xbf,0xa1,0x4f,0x63,0xfd,0xee,0xd6,0x14,0x1d,}
};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_28 ) = {
	.properties=0x10,
	.index=7,
	.max_len=0,
	.data=NULL,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_27 ) = {
	.len=5,
	.data={0x10,0x1d,0x00,0xde,0x2a,}
};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_26 ) = {
	.properties=0x04,
	.index=6,
	.max_len=0,
	.data=NULL,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_25 ) = {
	.len=5,
	.data={0x04,0x1b,0x00,0xdd,0x2a,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_24 ) = {
	.len=2,
	.data={0x28,0x18,}
};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_22 ) = {
	.properties=0x10,
	.index=5,
	.max_len=0,
	.data=NULL,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_21 ) = {
	.len=5,
	.data={0x10,0x17,0x00,0xdc,0x2a,}
};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_20 ) = {
	.properties=0x04,
	.index=4,
	.max_len=0,
	.data=NULL,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_19 ) = {
	.len=5,
	.data={0x04,0x15,0x00,0xdb,0x2a,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_18 ) = {
	.len=2,
	.data={0x27,0x18,}
};
uint8_t bg_gattdb_data_attribute_field_16_data[6]={0x00,0x00,0x00,0x00,0x00,0x00,};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_16 ) = {
	.properties=0x1a,
	.index=3,
	.max_len=6,
	.data=bg_gattdb_data_attribute_field_16_data,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_15 ) = {
	.len=19,
	.data={0x1a,0x11,0x00,0xd8,0x55,0x1c,0x36,0x13,0xbc,0xa0,0xae,0x8b,0x4d,0x62,0xf0,0x39,0x5a,0x79,0x05,}
};
uint8_t bg_gattdb_data_attribute_field_13_data[7]={0x4e,0x4e,0x4e,0x4e,0x4e,0x4e,0x00,};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_13 ) = {
	.properties=0x1a,
	.index=2,
	.max_len=7,
	.data=bg_gattdb_data_attribute_field_13_data,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_12 ) = {
	.len=19,
	.data={0x1a,0x0e,0x00,0x9b,0x61,0x94,0x5d,0xc0,0x68,0x18,0xac,0x0a,0x4d,0x6b,0xfb,0xeb,0xda,0x4e,0x6c,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_11 ) = {
	.len=12,
	.data={0x53,0x69,0x6c,0x69,0x63,0x6f,0x6e,0x20,0x4c,0x61,0x62,0x73,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_10 ) = {
	.len=5,
	.data={0x02,0x0c,0x00,0x29,0x2a,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_9 ) = {
	.len=2,
	.data={0x0a,0x18,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_8 ) = {
	.len=2,
	.data={0x40,0x03,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_7 ) = {
	.len=5,
	.data={0x02,0x09,0x00,0x01,0x2a,}
};
struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_6_data = {
	.len=20,
	.data={0x42,0x6c,0x75,0x65,0x47,0x65,0x63,0x6b,0x6f,0x20,0x4d,0x65,0x73,0x68,0x20,0x44,0x65,0x6d,0x6f,0x20,}
};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_6 ) = {
	.properties=0x02,
	.index=1,
	.max_len=20,
	.data_varlen=&bg_gattdb_data_attribute_field_6_data,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_5 ) = {
	.len=5,
	.data={0x02,0x07,0x00,0x00,0x2a,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_4 ) = {
	.len=2,
	.data={0x00,0x18,}
};
uint8_t bg_gattdb_data_attribute_field_2_data[4]={0x00,0x00,0x00,0x00,};
GATT_DATA(const struct bg_gattdb_attribute_chrvalue	bg_gattdb_data_attribute_field_2 ) = {
	.properties=0x20,
	.index=0,
	.max_len=4,
	.data=bg_gattdb_data_attribute_field_2_data,
};

GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_1 ) = {
	.len=5,
	.data={0x20,0x03,0x00,0x05,0x2a,}
};
GATT_DATA(const struct bg_gattdb_buffer_with_len	bg_gattdb_data_attribute_field_0 ) = {
	.len=2,
	.data={0x01,0x18,}
};
GATT_DATA(const struct bg_gattdb_attribute bg_gattdb_data_attributes_map[])={
    {.uuid=0x0000,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_0},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_1},
    {.uuid=0x000f,.permissions=0x800,.caps=0x03,.datatype=0x01,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_2},
    {.uuid=0x0010,.permissions=0x807,.caps=0x03,.datatype=0x03,.min_key_size=0x00,.configdata={.flags=0x02,.index=0x00,.clientconfig_index=0x00}},
    {.uuid=0x0000,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_4},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_5},
    {.uuid=0x0004,.permissions=0x801,.caps=0x03,.datatype=0x02,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_6},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_7},
    {.uuid=0x0005,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_8},
    {.uuid=0x0000,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_9},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_10},
    {.uuid=0x0007,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_11},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_12},
    {.uuid=0x8000,.permissions=0x803,.caps=0x03,.datatype=0x01,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_13},
    {.uuid=0x0010,.permissions=0x807,.caps=0x03,.datatype=0x03,.min_key_size=0x00,.configdata={.flags=0x01,.index=0x02,.clientconfig_index=0x01}},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_15},
    {.uuid=0x8001,.permissions=0x803,.caps=0x03,.datatype=0x01,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_16},
    {.uuid=0x0010,.permissions=0x807,.caps=0x03,.datatype=0x03,.min_key_size=0x00,.configdata={.flags=0x01,.index=0x03,.clientconfig_index=0x02}},
    {.uuid=0x0000,.permissions=0x801,.caps=0x01,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_18},
    {.uuid=0x0002,.permissions=0x801,.caps=0x01,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_19},
    {.uuid=0x0009,.permissions=0x804,.caps=0x01,.datatype=0x07,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_20},
    {.uuid=0x0002,.permissions=0x801,.caps=0x01,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_21},
    {.uuid=0x000a,.permissions=0x800,.caps=0x01,.datatype=0x07,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_22},
    {.uuid=0x0010,.permissions=0x807,.caps=0x01,.datatype=0x03,.min_key_size=0x00,.configdata={.flags=0x01,.index=0x05,.clientconfig_index=0x03}},
    {.uuid=0x0000,.permissions=0x801,.caps=0x02,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_24},
    {.uuid=0x0002,.permissions=0x801,.caps=0x02,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_25},
    {.uuid=0x000c,.permissions=0x804,.caps=0x02,.datatype=0x07,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_26},
    {.uuid=0x0002,.permissions=0x801,.caps=0x02,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_27},
    {.uuid=0x000d,.permissions=0x800,.caps=0x02,.datatype=0x07,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_28},
    {.uuid=0x0010,.permissions=0x807,.caps=0x02,.datatype=0x03,.min_key_size=0x00,.configdata={.flags=0x01,.index=0x07,.clientconfig_index=0x04}},
    {.uuid=0x0000,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_30},
    {.uuid=0x0002,.permissions=0x801,.caps=0x03,.datatype=0x00,.min_key_size=0x00,.constdata=&bg_gattdb_data_attribute_field_31},
    {.uuid=0x8003,.permissions=0x802,.caps=0x03,.datatype=0x07,.min_key_size=0x00,.dynamicdata=&bg_gattdb_data_attribute_field_32},
};

GATT_DATA(const uint16_t bg_gattdb_data_attributes_dynamic_mapping_map[])={
	0x0003,
	0x0007,
	0x000e,
	0x0011,
	0x0015,
	0x0017,
	0x001b,
	0x001d,
	0x0021,
};

GATT_DATA(const uint8_t bg_gattdb_data_adv_uuid16_map[])={0x27, 0x18, 0x28, 0x18, };
GATT_DATA(const uint8_t bg_gattdb_data_adv_uuid128_map[])={0x0};
GATT_HEADER(const struct bg_gattdb_def bg_gattdb_data)={
    .attributes=bg_gattdb_data_attributes_map,
    .attributes_max=33,
    .uuidtable_16_size=17,
    .uuidtable_16=bg_gattdb_data_uuidtable_16_map,
    .uuidtable_128_size=4,
    .uuidtable_128=bg_gattdb_data_uuidtable_128_map,
    .attributes_dynamic_max=9,
    .attributes_dynamic_mapping=bg_gattdb_data_attributes_dynamic_mapping_map,
    .adv_uuid16=bg_gattdb_data_adv_uuid16_map,
    .adv_uuid16_num=2,
    .adv_uuid128=bg_gattdb_data_adv_uuid128_map,
    .adv_uuid128_num=0,
    .caps_mask=0x03,
    .enabled_caps=0x00,
};

const struct bg_gattdb_def *bg_gattdb=&bg_gattdb_data;
