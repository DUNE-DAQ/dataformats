# Magic Bytes

All header structs written to file have two uint32_t words of magic bytes at the start of the struct. These serve as data type identifier (Fragment, TriggerRecordHeader, etc.) and version specifier (e.g. FragmentHeader v3).
The MagicBytes class also contains methods that can interrogate a buffer to determine whether it is a supported data type.

# MagicBytes Description

MagicBytes are currently two 32-bit words:

0. Type code (0x11112222 for FragmentHeader, 0x33334444 for TriggerRecordHeaderData)
1. Version number

# C++ Code for MagicBytes

```CPP
struct MagicBytes
{
  static constexpr uint32_t s_data_type_offset = 0;
  static constexpr uint32_t s_version_offset = sizeof(uint32_t);
  static constexpr uint32_t s_fragment_header_magic = 0x11112222;
  static constexpr uint32_t s_trigger_record_header_magic = 0x33334444;

  uint32_t type_marker;
  uint32_t version;

  static uint32_t s_get_type_marker(const void* blob);
  static uint32_t s_get_version(const void* blob);
  static bool s_is_fragment(const void* blob);
  static bool s_is_trigger_record_header(const void* blob);
};
```