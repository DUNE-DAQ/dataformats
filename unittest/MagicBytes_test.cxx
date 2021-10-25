/**
 * @file MagicBytes_test.cxx MagicBytes class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dataformats/Fragment.hpp"
#include "dataformats/MagicBytes.hpp"
#include "dataformats/TriggerRecordHeader.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE MagicBytes_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dataformats;

BOOST_AUTO_TEST_SUITE(MagicBytes_test)

BOOST_AUTO_TEST_CASE(IsAFragment)
{

  auto buf1 = malloc(10);
  Fragment frag(buf1, size_t(10));

  BOOST_REQUIRE(MagicBytes::s_is_fragment(frag.get_storage_location()));
  BOOST_REQUIRE(!MagicBytes::s_is_trigger_record_header(frag.get_storage_location()));
  BOOST_REQUIRE_EQUAL(MagicBytes::s_get_version(frag.get_storage_location()), FragmentHeader::s_fragment_header_version);
}

BOOST_AUTO_TEST_CASE(IsATriggerRecordHeader)
{
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.system_type = GeoID::SystemType::kTPC;
  components.back().component.region_id = 1;
  components.back().component.element_id = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.system_type = GeoID::SystemType::kTPC;
  components.back().component.region_id = 5;
  components.back().component.element_id = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  TriggerRecordHeader header(components);
  header.set_run_number(9);
  header.set_trigger_number(10);
  header.set_trigger_timestamp(11);
  header.set_trigger_type(12);
  header.set_sequence_number(13);
  header.set_max_sequence_number(14);
  header.set_error_bit(TriggerRecordErrorBits::kMismatch, true);
  header.set_error_bit(TriggerRecordErrorBits::kUnassigned3, true);

  BOOST_REQUIRE(MagicBytes::s_is_trigger_record_header(header.get_storage_location()));
  BOOST_REQUIRE(!MagicBytes::s_is_fragment(header.get_storage_location()));
  BOOST_REQUIRE_EQUAL(MagicBytes::s_get_version(header.get_storage_location()),
                                                TriggerRecordHeaderData::s_trigger_record_header_version);
}

BOOST_AUTO_TEST_CASE(BadMagic) {
  uint64_t bad_words = 0x1234123456785678;
  BOOST_REQUIRE(!MagicBytes::s_is_trigger_record_header(static_cast<void*>(&bad_words)));
  BOOST_REQUIRE(!MagicBytes::s_is_fragment(static_cast<void*>(&bad_words)));
}

BOOST_AUTO_TEST_SUITE_END()