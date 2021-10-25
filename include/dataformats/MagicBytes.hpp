/**
 * @file MagicBytes.hpp  Magic Byte definitions for DUNE-DAQ data formats
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_MAGICBYTES_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_MAGICBYTES_HPP_

#include <cstdint>

namespace dunedaq {
namespace dataformats {

/**
 * @brief The header for a DUNE Fragment
 */
struct MagicBytes
{
  static constexpr uint32_t s_data_type_offset = 0;
  static constexpr uint32_t s_version_offset = sizeof(uint32_t);

  /**
   * @brief Magic bytes to identify a FragmentHeader entry in a raw data stream
   */
  static constexpr uint32_t s_fragment_header_magic = 0x11112222; // NOLINT(build/unsigned)

  /**
   * @brief Magic bytes to identify a TriggerRecordHeader entry in a raw data stream
   */
  static constexpr uint32_t s_trigger_record_header_magic = 0x33334444; // NOLINT(build/unsigned)

  /**
   * @brief Magic Bytes used to identify FragmentHeaders in a raw data stream
   */
  uint32_t type_marker; // NOLINT(build/unsigned)

  /**
   * @brief Version of the FragmentHeader
   */
  uint32_t version; // NOLINT(build/unsigned)

  static uint32_t s_get_type_marker(const void* blob) { return static_cast<const uint32_t*>(blob)[s_data_type_offset]; }
  static uint32_t s_get_version(const void* blob) { return static_cast<const uint32_t*>(blob)[s_version_offset / sizeof(uint32_t)]; }
  static bool s_is_fragment(const void* blob) { return s_get_type_marker(blob) == s_fragment_header_magic; }
  static bool s_is_trigger_record_header(const void* blob)
  {
    return s_get_type_marker(blob) == s_trigger_record_header_magic;
  }
};
} // namespace dataformats
} // namespace dunedaq

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_MAGICBYTES_HPP_
