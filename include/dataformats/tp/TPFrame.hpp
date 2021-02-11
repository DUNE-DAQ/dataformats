/**
 * @file TPFrame.hpp Trigger Primitive bit fields and accessors
 *
 * This is part of the DUNE DAQ , copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_TP_TPFRAME_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_TP_TPFRAME_HPP_

#include <bitset>
#include <iostream>
#include <vector>

namespace dunedaq {
namespace dataformats {

typedef uint32_t word_t;
typedef uint16_t adc_t;
typedef std::vector<uint16_t> adc_v;

//===================
// TP header struct
//===================
struct TPHeader
{
  word_t flags: 13, slot_no: 3, wire_no : 8, fiber_no : 3, crate_no : 5;
  word_t timestamp_1;
  word_t timestamp_2;

  uint64_t timestamp() const
  {
    uint64_t timestamp = timestamp_1 | (timestamp_2 << 32);
    return timestamp;
  }

  void set_timestamp(const uint64_t new_timestamp)
  {
    timestamp_1 = new_timestamp;
    timestamp_2 = new_timestamp >> 32;
  }

  // Print functions for debugging.
  void print() const
  {
    std::cout << "flags:" << unsigned(flags) << " slot:" << unsigned(slot_no) << " wire:" << unsigned(wire_no) 
              << " fiber:" << unsigned(fiber_no) << " crate:" << unsigned(crate_no)
              << " timestamp:" << timestamp()
              << '\n';
  }

  void printHex() const
  {
    std::cout << "Printing TP header:\n";
    std::cout << std::hex << "flags:" << flags << " slot:" << slot_no << " wire:" << wire_no
              << " fiber:" << fiber_no << " crate:" << crate_no << " timestamp:" << timestamp() << std::dec << '\n';
  }

  void printBits() const
  {
    std::cout << "flags:" << std::bitset<13>(flags)
              << " slot:" << std::bitset<3>(slot_no) << " wire:" << std::bitset<8>(wire_no)
              << " fiber:" << std::bitset<3>(fiber_no) << " crate:" << std::bitset<5>(crate_no) 
              << " timestamp: " << timestamp() << '\n';
  }
};

//========================
// TP data struct
//========================
struct TPData
{
  // This struct contains three words of TP values that form the main repeating
  // pattern in the TP block.
  word_t end_time: 16, start_time: 16;
  word_t peak_time: 16, peak_adc: 16;
  word_t hit_continue: 1, flags: 15, sum_adc: 16;

  void print() const
  {
    std::cout << "end_time:" << unsigned(end_time) << " start_time:" << unsigned(start_time)
              << " peak_time:" << unsigned(peak_time) << " peak_adc:" << unsigned(peak_adc)
              << " hit_continue:" << unsigned(hit_continue) << " flags:" << unsigned(flags) 
              << " sum_adc:" << unsigned(sum_adc) 
              << '\n';
  }

  void printHex() const
  {
    std::cout << std::hex << "end_time:" << end_time << " start_time:" << start_time 
              << " peak_time:" << peak_time << " peak_adc:" << peak_adc 
              << " hit_continue:" << hit_continue << " flags:" << flags 
              << " sum_adc:" << sum_adc << std::dec << '\n';
  }
};

//========================
// TP pedestal information struct
//========================
struct TPPedinfo
{
  // This struct contains three words: one carrying median and accumulator and two padding words
  word_t accumulator: 16, median: 16;
  word_t padding_2: 16, padding_1: 16;
  word_t padding_4: 16, padding_3: 16;

  void print() const 
  {
    std::cout << "median:" << unsigned(median) << " accumulator:" << unsigned(accumulator)
              << '\n';
  }

  void printHex() const
  {
    std::cout << "Printing TP pedinfo:\n";
    std::cout << std::hex << "median:" << median << " accumulator:" << accumulator 
              << " padding_1:" << padding_1 << " padding_2:" << padding_2 
              << " padding_3: "<< padding_3 << " padding_4:" << padding_4 << std::dec << '\n';
  }
};

//========================
// TPData block
//========================
struct TPDataBlock
{  
  std::vector<TPData> block;

  void add_tp(const TPData& data) 
  {
    block.push_back(data);
  }

  unsigned int num_tp_per_block()
  {
    return block.size();
  }

  void print() const 
  {
    for (auto b : block) {
      b.print();
    }
  }

  void printHex() const
  {
    for (auto b: block) {
      b.printHex();
    }
  }
};

//=============
// FELIX frame
//=============
class TPFrame
{
public:
  // Constant expressions
  static constexpr size_t num_frame_hdr_words = 3;
  static constexpr size_t num_tp_words = 3;
  static constexpr size_t num_pedinfo_words = 3;

private:
  TPHeader head;
  TPDataBlock data;
  TPPedinfo pedinfo;

public:
  // TP header accessors
  uint8_t slot_no() const { return head.slot_no; }
  uint8_t wire_no() const { return head.wire_no; }
  uint8_t fiber_no() const { return head.fiber_no; }
  uint8_t crate_no() const { return head.crate_no; }
  uint64_t timestamp() const { return head.timestamp(); }
  // TP header mutators
  void set_slot_no(const uint8_t new_slot_no) { head.slot_no = new_slot_no; }
  void set_wire_no(const uint8_t new_wire_no) { head.wire_no = new_wire_no; }
  void set_fiber_no(const uint8_t new_fiber_no) { head.fiber_no = new_fiber_no; }
  void set_crate_no(const uint8_t new_crate_no) { head.crate_no = new_crate_no; }
  void set_timestamp(uint64_t new_timestamp) { head.set_timestamp(new_timestamp); }

  // TP data accessors
  uint8_t num_tp_per_block() { return data.num_tp_per_block(); }
  // TP data mutators
  void add_tp(const TPData& tpdata) { data.add_tp(tpdata); }

  // Const struct accessors
  const TPHeader*     tp_header() const { return &head; }
  const TPDataBlock*  tp_data() const { return &data; }
  const TPPedinfo*    tp_pedinfo() const { return &pedinfo; }
  // Const struct mutators
  void set_tp_header(const TPHeader& hdr) { head = hdr; }
  void set_tp_data(const TPDataBlock& dat) {data = dat; }
  void set_tp_pedinfo(const TPPedinfo& ped) { pedinfo = ped; }

  // Utility functions
  void print() const
  {
    std::cout << "Printing frame:\n";
    head.print();
    data.print();
    pedinfo.print();  
  }

  void printHex() const 
  {
    std::cout << "Printing frame:\n";
    head.printHex();
    data.printHex();
    pedinfo.printHex();
  }
};


} // namespace dataformats
} // namespace dunedaq

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_WIB_WIBFRAME_HPP_
