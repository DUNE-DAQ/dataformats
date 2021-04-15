cmake_minimum_required(VERSION 3.12)
project(dataformats VERSION 2.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(Boost 1.70.0 COMPONENTS unit_test_framework REQUIRED)

# 3 cases: USE_ERS = true: Always try and use ERS
#          USE_ERS = false: Never try and use ERS
#          USE_ERS unset: See if ERS is available and use it if it is

if(NOT DEFINED USE_ERS)
  find_package(ers)
  set(USE_ERS ${ers_FOUND})
else()
  if(${USE_ERS})
    find_package(ers REQUIRED)
  endif()
endif()

if(${USE_ERS})
  set(ERS_LIB ers::ers)
  add_definitions("-DUSE_ERS=1")
endif()

set(RAWDATA_DEPENDENCIES ${ERS_LIB})

##############################################################################
# Main library

daq_add_library(*.cpp LINK_LIBRARIES ${RAWDATA_DEPENDENCIES})

##############################################################################
# Plugins

#daq_add_plugin(... ... LINK_LIBRARIES daq-rawdata)

##############################################################################
# Integration tests



##############################################################################
# Unit Tests

daq_add_unit_test(ComponentRequest_test        LINK_LIBRARIES dataformats)
daq_add_unit_test(Fragment_test                LINK_LIBRARIES dataformats)
daq_add_unit_test(FragmentHeader_test          LINK_LIBRARIES dataformats)
daq_add_unit_test(GeoID_test                   LINK_LIBRARIES dataformats)
daq_add_unit_test(TriggerRecord_test           LINK_LIBRARIES dataformats)
daq_add_unit_test(TriggerRecordHeader_test     LINK_LIBRARIES dataformats)
daq_add_unit_test(TriggerRecordHeaderData_test LINK_LIBRARIES dataformats)
daq_add_unit_test(WIBFrame_test                LINK_LIBRARIES dataformats)
daq_add_unit_test(WIB2Frame_test                LINK_LIBRARIES dataformats)

##############################################################################

daq_install()
