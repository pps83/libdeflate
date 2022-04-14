#define BUILDING_LIBDEFLATE
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused"
#elif defined(_MSC_VER)
#pragma warning(push, 1)
#pragma warning(disable:4146 4701 4703)
#endif

#include "lib/adler32.c"
#include "lib/crc32.c"
#include "lib/deflate_compress.c"
#undef BITBUF_NBITS
#include "lib/deflate_decompress.c"
#include "lib/gzip_compress.c"
#include "lib/gzip_decompress.c"
#include "lib/utils.c"
#include "lib/zlib_compress.c"
#include "lib/zlib_decompress.c"

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#include "lib/arm/cpu_features.c"
#else
#include "lib/x86/cpu_features.c"
#endif
