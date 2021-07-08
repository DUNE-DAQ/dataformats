#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_TRIGGER_TRIGGERPRIMITIVESFRAGMENT_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_TRIGGER_TRIGGERPRIMITIVESFRAGMENT_HPP_

#include <cstdint>

namespace dunedaq {

namespace dataformats {

struct TriggerPrimitivesFragment
{
  static constexpr uint32_t s_tpf_header_magic = 0xcafecafe; // NOLINT(build/unsigned)
  static constexpr uint32_t s_tpf_version = 1;               // NOLINT(build/unsigned)

  struct TriggerPrimitive
  {
    uint64_t time_start;          // NOLINT(build/unsigned)
    uint64_t time_peak;           // NOLINT(build/unsigned)
    uint64_t time_over_threshold; // NOLINT(build/unsigned)
    uint32_t channel;             // NOLINT(build/unsigned)
    uint32_t adc_integral;        // NOLINT(build/unsigned)
    uint16_t adc_peak;            // NOLINT(build/unsigned)
    uint16_t detid;               // NOLINT(build/unsigned)
    uint32_t type;                // NOLINT(build/unsigned)
    uint32_t algorithm;           // NOLINT(build/unsigned)
    uint16_t version;             // NOLINT(build/unsigned)
    uint16_t flag;                // NOLINT(build/unsigned)
  };

  uint32_t magic = s_tpf_header_magic;
  uint32_t version = s_tpf_version; // NOLINT(build/unsigned)
  uint64_t n_trigger_primitives;    // NOLINT(build/unsigned)

  // This is a "flexible array member", which is strictly not part of
  // the C++ standard, although it happens to work. If we don't want
  // to use this, we can manually calculate offsets into the structure
  // to get pointers to the individual TriggerPrimitive structures
  TriggerPrimitive primitives[];
};

} // namespace dataformats
} // namespace dunedaq

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_TRIGGER_TRIGGERPRIMITIVEFRAGMENT_HPP_
