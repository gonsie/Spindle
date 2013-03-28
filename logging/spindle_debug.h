#if !defined(SPINDLE_DEBUG_H_)
#define SPINDLE_DEBUG_H_

#define LOGD_DEBUG

#if defined(LOGD_DEBUG)
#define LDCSDEBUG 1
#if defined(__cplusplus)
extern "C" {
#endif
#include "spindle_logc.h"
#if defined(__cplusplus)
}
#endif
#elif defined(DEBUG)
#define LDCSDEBUG 1
#define debug_printf(format, ...) \
  do { \
     fprintf(stderr, "[%s:%u@%d] - " format, __FILE__, __LINE__, getpid(), ## __VA_ARGS__); \
  } while (0)
#elif defined(SIONDEBUG)
#define LDCSDEBUG 1
#include "sion_debug.h"
#define debug_printf(format, ...) \
  do { \
    sion_dprintfp(32, __FILE__, getpid(), "[L%04u, %12.2f] - " format, __LINE__,_sion_get_time(), ## __VA_ARGS__); \
  } while (0)
#else
#define debug_printf(format, ...)
#endif

#if defined(LOGD_DEBUG)
#define LOGGING_INIT(S) init_spindle_debugging(S, 0)
#define LOGGING_INIT_PREEXEC(S) init_spindle_debugging(S, 1)
#define LOGGING_FINI fini_spindle_debugging()
#else
#define LOGGING_INIT(S)
#define LOGGING_INIT_PREEXEC(S)
#define LOGGING_FINI
#define debug_printf2(S, ...) debug_printf(S, ## __VA_ARGS__)
#define debug_printf3(S, ...) debug_printf(S, ## __VA_ARGS__)

#define bare_printf(S, ...) debug_printf(S, ## __VA_ARGS__)
#define bare_printf2(S, ...) debug_printf(S, ## __VA_ARGS__)
#define bare_printf3(S, ...) debug_printf(S, ## __VA_ARGS__)

#define err_printf(S, ...) debug_printf(S, ## __VA_ARGS__)
#endif

#endif