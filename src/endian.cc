#include <endian.h>

#include <boost/endian/conversion.hpp>

uint64_t htobe64(uint64_t host_64bits) {
    return boost::endian::native_to_big(host_64bits);
}
