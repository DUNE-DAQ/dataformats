/**
 * @file Exceptions.hpp  Exception definitions
 *
 * This file contains either std::exception or ERS_ISSUE definitions for all error types encountered in the dataformats
 * library
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_EXCEPTIONS_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_EXCEPTIONS_HPP_

#include <sstream>
#include <string>

#ifndef USE_ERS
#define DATAFORMATS_HERE __FILE__, __LINE__, __PRETTY_FUNCTION__
/**
 * @brief The DUNE-DAQ namespace
 */
namespace dunedaq {

/**
 * @brief Dataformats code
 */
namespace dataformats {

/**
 * @brief Base class for dataformats exceptions, inheriting from std::exception
 */
class DataformatException : public std::exception
{
public:
  DataformatException(std::string file, int line, std::string function)
    : m_file(file)
    , m_line(line)
    , m_function(function)
  {
    m_what = preamble() + "UNKNOWN DATAFORMATS EXCEPTION";
  }

  std::string get_file() const { return m_file; }
  int get_line() const { return m_line; }
  std::string get_function() const { return m_function; }
  std::string get_package() const { return "dataformats"; }

  std::string preamble() const { return m_file + ":" + std::to_string(m_line) + ": " + m_function + ": "; }

  const char* what() const noexcept override { return m_what.c_str(); }

protected:
  std::string m_what;

private:
  std::string m_file;
  int m_line;
  std::string m_function;
};

/**
 * @brief A std::exception class indicating that a malloc failed
 */
class MemoryAllocationFailed : public DataformatException
{
public:
  MemoryAllocationFailed(std::string file, int line, std::string function, size_t bytes)
    : DataformatException(file, line, function)
    , m_bytes(bytes)
  {
    m_what = preamble() + "Malloc of " + std::to_string(m_bytes) + " bytes failed";
  }

  size_t get_bytes() const { return m_bytes; }

private:
  size_t m_bytes;
};

/**
 * @brief A std::exception indicating that the requested index is out of range
 */
class WibFrameRelatedIndexError : public DataformatException
{
public:
  WibFrameRelatedIndexError(std::string file,
                            int line,
                            std::string function,
                            int wib_index_supplied,
                            int wib_index_min,
                            int wib_index_max)
    : DataformatException(file, line, function)
    , m_wib_index_supplied(wib_index_supplied)
    , m_wib_index_min(wib_index_min)
    , m_wib_index_max(wib_index_max)
  {
    m_what = preamble() + "Supplied index " + std::to_string(m_wib_index_supplied) +
             " is outside the allowed range of " + std::to_string(wib_index_min) + " to " +
             std::to_string(wib_index_max);
  }

  int get_wib_index_supplied() const { return m_wib_index_supplied; }
  int get_wib_index_min() const { return m_wib_index_min; }
  int get_wib_index_max() const { return m_wib_index_max; }

private:
  int m_wib_index_supplied;
  int m_wib_index_min;
  int m_wib_index_max;
};

/**
 * @brief A std::exception indicating that the requested index is out of range
 */
class ComponentRequestIndexError : public DataformatException
{
public:
  ComponentRequestIndexError(std::string file, int line, std::string function, int index_supplied, int index_max)
    : DataformatException(file, line, function)
    , m_index_supplied(index_supplied)
    , m_index_max(index_max)
  {
    m_what = preamble() + "Supplied ComponentRequest index " + std::to_string(index_supplied) +
             " is greater than the maximum index " + std::to_string(index_max);
  }

  int get_index_supplied() const { return m_index_supplied; }
  int get_index_max() const { return m_index_max; }

private:
  int m_index_supplied;
  int m_index_max;
};

/**
 * @brief A std::exception that indicates that one the buffers given to the Fragment constructor is invalid
 */
class FragmentBufferError : public DataformatException
{
public:
  FragmentBufferError(std::string file, int line, std::string function, void* buffer_address, size_t buffer_size)
    : DataformatException(file, line, function)
    , m_buffer_address(buffer_address)
    , m_buffer_size(buffer_size)
  {
    std::stringstream oss;
    oss << preamble() << "Fragment Buffer " << buffer_address << " with size " << buffer_size << " is invalid";
    m_what = oss.str();
  }

  void* get_buffer_address() const { return m_buffer_address; }
  size_t get_buffer_size() const { return m_buffer_size; }

private:
  void* m_buffer_address;
  size_t m_buffer_size;
};

/**
 * @brief A std::exception that indicates that an issue was detected with the requested Fragment Size
 */
class FragmentSizeError : public DataformatException
{
public:
  FragmentSizeError(std::string file,
                    int line,
                    std::string function,
                    size_t fragment_size,
                    size_t size_min,
                    size_t size_max)
    : DataformatException(file, line, function)
    , m_fragment_size(fragment_size)
    , m_size_min(size_min)
    , m_size_max(size_max)
  {
    m_what = preamble() + "Fragment has a requested size of " + std::to_string(fragment_size) +
             ", which is outside the allowable range of " + std::to_string(size_min) + "-" + std::to_string(size_max);
  }

  size_t get_fragment_size() const { return m_fragment_size; }
  size_t get_size_min() const { return m_size_min; }
  size_t get_size_max() const { return m_size_max; }

private:
  size_t m_fragment_size;
  size_t m_size_min;
  size_t m_size_max;
};
}
}

#else // USE_ERS
#include "ers/Issue.hpp"

#define DATAFORMATS_HERE ERS_HERE

namespace dunedaq {
/**
 * @brief An ERS Error that indicates that one the buffers given to the Fragment constructor is invalid
 * @param fb_addr Address of invalid buffer
 * @param fb_size Size of invalid buffer
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  FragmentBufferError,
                  "Fragment Buffer " << fb_addr << " with size " << fb_size << " is invalid",
                  ((void*)fb_addr)((size_t)fb_size)) // NOLINT
                                                     /// @endcond

/**
 * @brief An ERS Error that indicates that an issue was detected with the requested Fragment Size
 * @param fs_size Fragment size that caused issue
 * @param fs_min Minimum allowable Fragment size
 * @param fs_max Maximum allowable Fragment size
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  FragmentSizeError,
                  "Fragment has a requested size of " << fs_size << ", which is outside the allowable range of "
                                                      << fs_min << "-" << fs_max,
                  ((size_t)fs_size)((size_t)fs_min)((size_t)fs_max)) // NOLINT
                                                                     /// @endcond

/**
 * @brief An ERS Issue indicating that an attempted FragmentType conversion failed
 * @param fragment_type_input Input that failed conversion
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  FragmentTypeConversionError,
                  "Supplied input " << fragment_type_input << " did not match any in s_fragment_type_names",
                  ((std::string)fragment_type_input)) // NOLINT
                                                      /// @endcond

/**
 * @brief An ERS Error indicating that the requested index is out of range
 * @param cri_index_supplied Index that caused the error
 * @param cri_index_max Maximum valid index for this function
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  ComponentRequestIndexError,
                  "Supplied ComponentRequest index " << cri_index_supplied << " is greater than the maximum index "
                                                     << cri_index_max,
                  ((int)cri_index_supplied)((int)cri_index_max)) // NOLINT
                                                                 /// @endcond

/**
 * @brief An ERS Error indicating that a malloc failed
 * @param maf_bytes Bytes requested from malloc
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  MemoryAllocationFailed,
                  "Malloc of " << maf_bytes << " bytes failed",
                  ((size_t)maf_bytes)) // NOLINT
                                       /// @endcond

/**
 * @brief An ERS Error indicating that the requested index is out of range
 * @param wib_index_supplied Index that caused the error
 * @param wib_index_min Minium valid index for this function
 * @param wib_index_max Maximum valid index for this function
 * @cond Doxygen doesn't like ERS macros
 */
ERS_DECLARE_ISSUE(dataformats,
                  WibFrameRelatedIndexError,
                  "Supplied index " << wib_index_supplied << " is outside the allowed range of " << wib_index_min
                                    << " to " << wib_index_max,
                  ((int)wib_index_supplied)((int)wib_index_min)((int)wib_index_max)) // NOLINT
                                                                                     /// @endcond
}
#endif // USE_ERS

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_EXCEPTIONS_HPP_