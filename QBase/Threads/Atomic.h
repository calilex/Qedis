#ifndef BERT_ATOMIC_H
#define BERT_ATOMIC_H

#if !defined(__gnu_linux__)
#define TEMP_FAILURE_RETRY(x)  x
#endif

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <stdint.h>

#define AtomicChange(plAddEnd, delta) __sync_fetch_and_add((plAddEnd), (delta))
#define AtomicChange64                AtomicChange

#define AtomicSet(plTarget, value)    __sync_lock_test_and_set ((plTarget), (value))
#define AtomicSet64                   AtomicSet

#define AtomicTestAndSet(plDest, lComparand, lExchange)\
    __sync_val_compare_and_swap((plDest), (lComparand), (lExchange))

#define AtomicTestAndSet64            AtomicTestAndSet


#else
#include <Windows.h>
typedef  __int8   int8_t;
typedef  __int16  int16_t;
typedef  __int32  int32_t;
typedef  __int64  int64_t;

typedef  unsigned __int8   uint8_t;
typedef  unsigned __int16  uint16_t;
typedef  unsigned __int32  uint32_t;
typedef  unsigned __int64  uint64_t;

#define AtomicChange(plAddEnd, delta)    InterlockedExchangeAdd((long*)(plAddEnd), (long)(delta))
#define AtomicChange64(pllAddEnd, delta) InterlockedExchangeAdd64((long long*)(pllAddEnd), (long long)(delta))

#define AtomicSet(plTarget, value)       InterlockedExchange((long*)(plTarget), (long)(value))
#define AtomicSet64(pllTarget, value)    InterlockedExchange64((long long*)(pllTarget), (long long)(value))

#define AtomicTestAndSet(plDest, lComparand, lExchange)\
    InterlockedCompareExchange((long*)(plDest), (long)(lExchange), (long)(lComparand))

#define AtomicTestAndSet64(pllDest, llComparand, llExchange)\
    InterlockedCompareExchange64((long long*)(pllDest), (long long)(llExchange), (long long)(llComparand))

#endif

#define AtomicGet(plTarget)      AtomicChange(plTarget, 0)
#define AtomicGet64(plTarget)    AtomicChange64(plTarget, 0)



template <typename DummyType>
class IdCreator32
{
public:
    static unsigned int CreateID();
private:
    static unsigned int m_id;
};

template <typename DummyType>
unsigned int IdCreator32<DummyType>::m_id = 0;

template <typename DummyType>
unsigned int IdCreator32<DummyType>::CreateID()
{
    return AtomicChange(&m_id, 1);
}



template <typename DummyType>
class IdCreator64
{
public:
    static unsigned long long CreateID();
private:
    static unsigned long long m_id;
};

template <typename DummyType>
unsigned long long IdCreator64<DummyType>::m_id = 0;

template <typename DummyType>
unsigned long long IdCreator64<DummyType>::CreateID()
{
    return AtomicChange(&m_id, 1);
}

#endif