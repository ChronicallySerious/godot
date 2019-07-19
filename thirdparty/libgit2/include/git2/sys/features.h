#ifndef INCLUDE_features_h__
#define INCLUDE_features_h__

/* #undef GIT_DEBUG_POOL */
/* #undef GIT_TRACE */
#define GIT_THREADS 1
/* #undef GIT_MSVC_CRTDBG */

#define GIT_ARCH_64 1
/* #undef GIT_ARCH_32 */

/* #undef GIT_USE_ICONV */
#undef GIT_USE_NSEC
/* #undef GIT_USE_STAT_MTIM */
/* #undef GIT_USE_STAT_MTIMESPEC */
/* #undef GIT_USE_STAT_MTIME_NSEC */
/* #undef GIT_USE_FUTIMENS */
/* #undef GIT_USE_REGCOMP_L */

/* #undef GIT_SSH */
/* #undef GIT_SSH_MEMORY_CREDENTIALS */

/* #undef GIT_GSSAPI */
#undef GIT_WINHTTP

#define GIT_HTTPS 1
/* #undef GIT_OPENSSL */
/* #undef GIT_SECURE_TRANSPORT */
/* #undef GIT_MBEDTLS */

// -- GODOT start
// Godot doesn't require CollisionDetection (the SHA1 backend)
/* #undef GIT_SHA1_COLLISIONDETECT */
// -- GODOT end
/* #undef GIT_SHA1_WIN32 */
/* #undef GIT_SHA1_COMMON_CRYPTO */
/* #undef GIT_SHA1_OPENSSL */
/* #undef GIT_SHA1_MBEDTLS */

#endif
