#ifndef CIRCBUF_H
#define CIRCBUF_H

#ifdef CIRCBUF_EXPORTS
#define CIRCBUF_API __declspec(dllexport)
#else
#define CIRCBUF_API __declspec(dllimport)
#endif

typedef struct struct_circBuf
{
	size_t mask;
	size_t offset;
	double* content;
} circBuf;

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API char circBuf_init(circBuf*, size_t);
#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API double circBuf_get(circBuf*, size_t);
#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_set(circBuf*, size_t, double);
#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_roll(circBuf*, size_t);
#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_setContent(circBuf*, double*);
#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_getContent(circBuf*, double*);
#endif