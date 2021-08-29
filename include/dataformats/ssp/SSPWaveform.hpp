/**
 * @file SSPWaveform.hpp
 *
 *  Contains declaration of SSPWaveform, a class for accessing SSP data from raw data files produced by artdaq. 
 *  This class is designed as a bridge to allow artdaq data to be visualised in the DUNE-DAQ DQM system.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_SSPADAPTOR_SSPWAVEFORM_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_SSPADAPTOR_SSPWAVEFORM_HPP_

//#include <algorithm> // For std::min
//#include <cassert>   // For assert()
#include <cstdio>
#include <cstdlib>
//#include <stdexcept> // For std::out_of_range
//#include <stdint.h>  // For uint32_t etc

namespace dunedaq::dataformats {

class SSPWaveform
{
public:

  // ===============================================================
  // Data members
  // ===============================================================
  int runnum;
  int subrunnum;
  int eventnum;
  int channel;
  time_t timestamp;
  short waveform[2000];

} // namespace dunedaq::dataformats

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_SSPADAPTOR_SSPWAVEFORM_HPP_

// Local Variables:
// c-basic-offset: 2
// End:
