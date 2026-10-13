
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2015-2024, Lantronix, Inc. All Rights Reserved.
** By using this software, you are agreeing to the terms of the Software
** Development Kit (SDK) License Agreement included in the distribution package
** for this software (the “License Agreement”).
** Under the License Agreement, this software may be used solely to create
** custom applications for use on the Lantronix xPico Wi-Fi, xPico 200 Series,
** and xPort® Edge products.
** THIS SOFTWARE AND ANY ACCOMPANYING DOCUMENTATION IS PROVIDED "AS IS".
** LANTRONIX SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS
** FOR A PARTICULAR PURPOSE.
** LANTRONIX HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
** ENHANCEMENTS, OR MODIFICATIONS TO THIS SOFTWARE.
** IN NO EVENT SHALL LANTRONIX BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
** SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
** ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
** LANTRONIX HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*****************************************************************************/
/*                             Includes                                      */
/*****************************************************************************/

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions for general use.
*/

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

/*!
** \brief Wait forever.
**
** Many macros or functions with a timeout parameter will accept this
** value to represent an indefinite period of time.
*/
#define TIME_WAIT_FOREVER 0xffffffff

/*!
** \brief Kilobyte.
**
** Typically a multiplier.
*/
#define KILOBYTE 0x400

/*!
** \brief Megabyte.
**
** Typically a multiplier.
*/
#define MEGABYTE 0x100000

/*****************************************************************************/
/*                              Macros                                       */
/*****************************************************************************/

/*!
** \ingroup utilities
** \brief Smaller of two numbers.
** \param [in] a First number.
** \param [in] b Second number.
** \returns The smaller value.
*/
#define MINIMUM(a, b) ((a) < (b) ? (a) : (b))

/*!
** \ingroup utilities
** \brief Larger of two numbers.
** \param [in] a First number.
** \param [in] b Second number.
** \returns The larger value.
*/
#define MAXIMUM(a, b) ((a) < (b) ? (b) : (a))

/*!
** \ingroup utilities
** \brief Size of array.
** \param [in] a Name of the array.
** \returns The dimension of the array.
*/
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/*!
** \ingroup utilities
** \brief Offset of member in struct.
** \param [in] st The struct declaration.
** \param [in] m The member name in the struct.
** \returns The offset in bytes from the beginning of the struct.
*/
#define MEMBER_OFFSET(st, m) ((size_t)(&(((st *)0)->m)))

/*!
** \ingroup utilities
** \brief Structure pointer from member pointer.
**
** You must first declare your struct pointer \a sp to receive the result.
** This macro will fill it in with the address of the structure that
** contains the designated member.
** If \a mp is \c NULL, then \a sp will be set to \c NULL.
** Note that if \a m is const, this will fail; use
** \c ASSIGN_CONST_STRUCT_POINTER_FROM_MEMBER_POINTER() instead.
** \param [out] sp The struct pointer name.
** \param [in] st The struct declaration.
** \param [in] m The member name in the struct.
** \param [in] mp The member pointer.
*/
#define ASSIGN_STRUCT_POINTER_FROM_MEMBER_POINTER(sp, st, m, mp) \
    _Pragma("GCC diagnostic push"); \
    _Pragma("GCC diagnostic ignored \"-Wcast-align\""); \
    (sp) = ((st *)((mp) ? ((char *)(mp) - MEMBER_OFFSET(st, m)) : NULL)); \
    _Pragma("GCC diagnostic pop");

/*!
** \ingroup utilities
** \brief Const structure pointer from member pointer.
**
** You must first declare your const struct pointer \a sp to receive the result.
** This macro will fill it in with the address of the structure that
** contains the designated member.
** If \a mp is \c NULL, then \a sp will be set to \c NULL.
** \param [out] sp The const struct pointer name.
** \param [in] st The struct declaration.
** \param [in] m The member name in the struct.
** \param [in] mp The member pointer.
*/
#define ASSIGN_CONST_STRUCT_POINTER_FROM_MEMBER_POINTER(sp, st, m, mp) \
    _Pragma("GCC diagnostic push"); \
    _Pragma("GCC diagnostic ignored \"-Wcast-align\""); \
    (sp) = ((const st *)((mp) ? ((const char *)(mp) - MEMBER_OFFSET(st, m)) : NULL)); \
    _Pragma("GCC diagnostic pop");

/*!
** \ingroup utilities
** \brief String from defined number.
**
** Turns a defined number into a string constant.
** Allows the same define to be used numerically and in a string message.
** See also \c INTEGERIFY().
** \param [in] v The defined number.
*/
#ifndef STRINGIFY
#define STRINGIFY(v) STRINGIFY_DO_NOT_CALL_DIRECTLY(v)
#define STRINGIFY_DO_NOT_CALL_DIRECTLY(v) #v
#endif

/*!
** \ingroup utilities
** \brief Unsigned long from defined number.
**
** Turns a defined number into an unsigned long constant.
** Allows the same define to be used numerically and in a string message.
** See also \c STRINGIFY().
** \param [in] v The defined number.
*/
#define INTEGERIFY(v) INTEGERIFY_DO_NOT_CALL_DIRECTLY(v)
#define INTEGERIFY_DO_NOT_CALL_DIRECTLY(a) a##UL

#define OPAQUE_STRUCT(n) uint32_t opaque[(n+3)/4]

/*!
** \ingroup memory_mgmt
** \brief Allocate memory.
**
** This macro allocates \a size bytes.
** <i>The memory is not initialized.</i>
** \param [in] size Desired size in bytes.
** \returns Pointer to allocated memory.
** \retval NULL \c MALLOC failed.
*/
#define MALLOC(size) \
ltrx_malloc_do_not_call_directly( \
    size, __FILE__, __LINE__ \
)

/*!
** \ingroup memory_mgmt
** \brief Allocate memory and clear it to zeroes.
**
** This function allocates \a size bytes.
** <i>The memory is initialized to zeroes.</i>
** \param [in] size Desired size in bytes.
** \returns Pointer to allocated memory.
** \retval NULL \c MALLOC_ZEROED failed.
*/
#define MALLOC_ZEROED(size) \
ltrx_malloc_zeroed_do_not_call_directly( \
    size, __FILE__, __LINE__ \
)

/*!
** \ingroup memory_mgmt
** \brief Allocate memory and copy a string into it.
**
** This function returns a pointer to a new string which is a duplicate of the
** input \a string.
** \param [in] string String to be duplicated.
** \returns Pointer to allocated memory.
** \retval NULL \c STRDUP failed.
*/
#define STRDUP(string) \
ltrx_strdup_do_not_call_directly( \
    string, __FILE__, __LINE__ \
)

/*!
** \ingroup memory_mgmt
** \brief Allocate memory and copy a string into it, up to a limit.
**
** This function is similar to \c STRDUP(),
** but only copies at most \a n bytes.
** If \a string is longer than \a n,
** only \a n bytes are copied, and a terminating zero byte is added.
** \param [in] string String to be duplicated.
** \param [in] n Maximum bytes to duplicate.
** \returns Pointer to allocated memory.
** \retval NULL \c STRNDUP failed.
*/
#define STRNDUP(string, n) \
ltrx_strndup_do_not_call_directly( \
    string, n, __FILE__, __LINE__ \
)

/*!
** \ingroup memory_mgmt
** \brief Re-allocate memory and copy original into it.
**
** This function changes the size of the memory block pointed to by
** \a addr to \a newSize bytes.
** The contents will be unchanged in the range from the start of the region up
** to the minimum of the old and new sizes.
** If the new size is larger, the added memory will \e not be initialized.
** If \a addr is \c NULL,
** then the call is equivalent to <code>MALLOC(newSize)</code>,
** for all values of \a newSize;
** if \a newSize is equal to zero and \a addr is not
** \c NULL, then the call is equivalent to <code>ltrx_free(addr)</code>.
** Unless \a addr is \c NULL,
** it must have been returned by an earlier call to
** \c MALLOC(),
** \c MALLOC_ZEROED(),
** \c STRDUP(),
** \c STRNDUP(),
** or \c REALLOC().
** If the area pointed to was moved, an <code>ltrx_free(addr)</code> is done.
** \param [in] addr Pointer to old allocated memory.
** \param [in] newSize Desired new size in bytes.
** \returns Pointer to allocated memory.
** \retval NULL \c REALLOC failed.
*/
#define REALLOC(addr, newSize) \
ltrx_realloc_do_not_call_directly( \
    addr, newSize, __FILE__, __LINE__ \
)

/*!
** \ingroup memory_mgmt
** \brief Free previously allocated memory.
**
** This function frees the memory space pointed to by \a addr,
** which must have been returned by a previous call to
** \c MALLOC(),
** \c MALLOC_ZEROED(),
** \c MEMALIGN(),
** \c STRDUP(),
** \c STRNDUP(),
** or \c REALLOC().
** Otherwise, or if <code>ltrx_free(addr)</code> has already been called
** before, undefined behavior occurs.
** If \a addr is \c NULL, no operation is performed.
** \param [in] addr Previously allocated memory.
*/
#define ltrx_free(addr) \
ltrx_free_do_not_call_directly( \
    addr, __FILE__, __LINE__ \
)

/*!
** \ingroup thread
** \brief Pause this thread.
**
** Allows other threads to run if they are ready.
** Otherwize the processor will idle, saving power.
** After the sleep time expires, this thread will be allowed to run in turn.
** \param [in] timeMsec Sleep time in milliseconds.
*/
#define ltrx_thread_sleep(timeMsec) \
ltrx_thread_sleep_do_not_call_directly(__FILE__, __LINE__, timeMsec)

/*!
** \ingroup thread
** \brief Yield control to other threads.
**
** Allows other threads to run if they are ready.
** Unlike ltrx_thread_sleep(), this thread will be allowed to run again
** without delay if no other threads are ready.
*/
#define ltrx_thread_yield() \
ltrx_thread_yield_do_not_call_directly(__FILE__, __LINE__)

/*!
** \ingroup trigger
** \brief Wait for a trigger.
**
** Block this thread up to the specified \a timeout_in_milliseconds while
** waiting for a \a trigger.
**
** Trigger events are produced when any thread calls ltrx_trigger_signal().
**
** \b Warning: Check the return value even if you specify #TIME_WAIT_FOREVER
** because your thread can return early if another thread calls
** ltrx_thread_wake().
** \param [in,out] trigger Pointer to the trigger.
** \param [in] timeout_in_milliseconds Time to wait for the trigger before giving up.
** To wait indefinitely, use #TIME_WAIT_FOREVER.
** \retval true Trigger was detected.
** \retval false Failed to detect the trigger.
*/
#define LTRX_TRIGGER_WAIT(trigger, timeout_in_milliseconds) \
ltrx_trigger_wait_do_not_call_directly( \
    __FILE__, __LINE__, trigger, timeout_in_milliseconds \
)

/*!
** \ingroup mutex
** \brief Wait for a mutex.
**
** Block this thread up to the specified \a timeout_in_milliseconds while
** waiting to acquire exclusive control of \a mutex.
**
** \b Warning: Check the return value even if you specify #TIME_WAIT_FOREVER
** because your thread can return early if another thread calls
** ltrx_thread_wake().
** \param [in,out] mutex Pointer to the mutex.
** \param [in] timeout_in_milliseconds Time to wait for the mutex before giving up.
** To wait indefinitely, use #TIME_WAIT_FOREVER.
** \retval true Mutex was successfully acquired.
** \retval false Failed to acquire the mutex.
*/
#define LTRX_MUTEX_WAIT(mutex, timeout_in_milliseconds) \
ltrx_mutex_wait_do_not_call_directly( \
    __FILE__, __LINE__, mutex, timeout_in_milliseconds \
)

/*!
** \ingroup thread
** \brief Block preemption.
**
** Prevents other threads from preempting this one.
** Interrupts are still allowed.
**
** Paired with ltrx_preemption_unblock(), this is useful for protecting data
** or resource being shared with another thread to restrict when the other
** thread can access or change it.
**
** Nesting of ltrx_preemption_block() and ltrx_preemption_unblock() is
** allowed.
*/
#define ltrx_preemption_block() \
    ltrx_preemption_block_do_not_call_directly(__FILE__, __LINE__)

/*!
** \ingroup thread
** \brief Unblock preemption.
**
** Ends blocking of preemption from previous call to ltrx_preemption_block().
*/
#define ltrx_preemption_unblock() \
    ltrx_preemption_unblock_do_not_call_directly(__FILE__, __LINE__)

/*!
** \ingroup utilities
** \brief Compute stack size based on observation.
**
** This macro takes the maximum observed "Stack size" from the
** Diagnostics Threads status, and pads it so the status will read "green".
** "Green" status is up to 80% stack utilization.
** \param [in] used Observed stack usage in bytes.
** \returns Padded size.
*/
#define STACK_SIZE_GREEN_FROM_MAX_OBSERVED_STACK_USED(used) \
    ((used + 3) * 100 / 80)

/*****************************************************************************/
/*                               Enums                                       */
/*****************************************************************************/

enum ltrx_interrupt_vector
{
    LTRX_INTERRUPT_VECTOR__USB_OTG_HS = 0,
    LTRX_INTERRUPT_VECTOR__USB_OTG_HS_WKUP = 1,
    LTRX_INTERRUPT_VECTOR__USB_OTG_HS_EP1OUT = 2,
    LTRX_INTERRUPT_VECTOR__USB_OTG_HS_EP1IN = 3,
    LTRX_INTERRUPT_VECTOR__USB_XPICO240 = 4,
    LTRX_INTERRUPT_VECTOR__UART_SLOW = 5,
    LTRX_INTERRUPT_VECTOR__LAST_DO_NOT_USE
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct ltrx_mutex;

struct ltrx_trigger;

/*!
** \ingroup power
** \brief Represents a power level application for registration.
**
** It it used with ltrx_power_level_application_register().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_power_level_application
{
    const char *applicationName; /*!< [in] Name of the application. */
    const char *helpHtml; /*!< HTML help for this application. */
};

/*****************************************************************************/
/*                             Globals                                       */
/*****************************************************************************/

extern void (*ltrx_active_USB_IRQHandler)(void);

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_cfgvar_lock(void);

void ltrx_cfgvar_unlock(void);

/*!
** \ingroup platform
** \brief Get the product type name.
*/
const char *ltrx_platform_get_product_type(void);

const char *ltrx_platform_get_registered_product_type(void);

void ltrx_platform_get_firmware_version(
    char *buffer, size_t length
);

void ltrx_platform_get_sdk_version(
    char *buffer, size_t size
);

void ltrx_platform_get_serial_number(
    char *buffer, size_t size
);

const char *ltrx_platform_get_product_id(void);

uint8_t ltrx_platform_get_sku(void);

uint32_t ltrx_elapsed_time_current_ms(
    uint32_t time_mark
);

uint32_t ltrx_get_uptime_ms(void);

void ltrx_free_do_not_call_directly(
    void *addr,
    const char *fileName,
    uint32_t lineNumber
);

void ltrx_interrupt_disable(void);

void ltrx_interrupt_enable(void);

void ltrx_interrupt_vector_handler(
    uint32_t vectorNumber
);

void ltrx_interrupt_vector_set(
    enum ltrx_interrupt_vector liv,
    void (*optInterruptRoutine)(void)
);

void *ltrx_malloc_do_not_call_directly(
    size_t size,
    const char *fileName,
    uint32_t lineNumber
);

/*!
** \ingroup memory_mgmt
** \brief Determine if any memory allocation has yet failed.
**
** \retval true One or more allocation attempts have failed since bootup.
** \retval false Memory allocation has not yet failed.
*/
bool ltrx_malloc_has_ever_failed(void);

void *ltrx_malloc_zeroed_do_not_call_directly(
    size_t size,
    const char *fileName,
    uint32_t lineNumber
);


void *ltrx_memalign_do_not_call_directly(
    size_t align_size,
    size_t requested_size,
    const char *fileName,
    uint32_t lineNumber
);

bool ltrx_memory_address_is_in_ram(const void *address);

bool ltrx_mutex_create(
    struct ltrx_mutex *mutex,
    const char *name
);

bool ltrx_mutex_destroy(
    struct ltrx_mutex *mutex
);

struct ltrx_thread *ltrx_mutex_held_by(
    const struct ltrx_mutex *mutex
);

void ltrx_mutex_signal(
    struct ltrx_mutex *mutex
);

bool ltrx_mutex_wait_do_not_call_directly(
    const char *sourcePath,
    int sourceLine,
    struct ltrx_mutex *mutex,
    uint32_t ms
);

void ltrx_power_down_hold(void);

void ltrx_power_down_unhold(void);

void ltrx_power_down_idle_hold(void);

void ltrx_power_down_idle_unhold(void);

void ltrx_power_level_application_permit_shutdown(
    const char *applicationName,
    uint32_t durationSeconds
);

void ltrx_power_level_application_register(
    const struct ltrx_power_level_application *application
);

void ltrx_power_level_application_request_full_power(
    const char *applicationName
);

void ltrx_preemption_block_do_not_call_directly(
    const char *sourcePath,
    uint32_t sourceLine
);

void ltrx_preemption_unblock_do_not_call_directly(
    const char *sourcePath,
    uint32_t sourceLine
);

uint32_t ltrx_rand(void);

void *ltrx_realloc_do_not_call_directly(
    void *addr,
    size_t newSize,
    const char *fileName,
    uint32_t lineNumber
);

char *ltrx_sprintf_malloc(
    const char *fmt,
    ...
);

char *ltrx_strdup_do_not_call_directly(
    const char *string,
    const char *fileName,
    uint32_t lineNumber
);

char *ltrx_strndup_do_not_call_directly(
    const char *string,
    size_t n,
    const char *fileName,
    uint32_t lineNumber
);

void ltrx_system_shutdown_and_reboot(void);

void ltrx_system_reboot(void);

struct ltrx_thread *ltrx_thread_create(
    const char *name,
    void (*entry_function)(void *opaque),
    void *entry_opaque,
    uint32_t stack_size
);

void ltrx_thread_destroy(
    struct ltrx_thread *thread
);

struct ltrx_thread *ltrx_thread_id(void);

const char *ltrx_thread_name(struct ltrx_thread *lt);

void ltrx_thread_resume(
    struct ltrx_thread *thread
);

void ltrx_thread_sleep_do_not_call_directly(
    const char *sourcePath,
    int sourceLine,
    uint32_t milliSeconds
);

void ltrx_thread_suspend(void);

void ltrx_thread_wake(
    struct ltrx_thread *thread
);

void ltrx_thread_yield_do_not_call_directly(
    const char *sourcePath,
    int sourceLine
);

uint32_t ltrx_timemark(void);

void ltrx_trigger_clear(
    struct ltrx_trigger *trigger
);

bool ltrx_trigger_create(
    struct ltrx_trigger *trigger,
    const char *name
);

bool ltrx_trigger_destroy(
    struct ltrx_trigger *trigger
);

void ltrx_trigger_signal(
    struct ltrx_trigger *trigger
);

bool ltrx_trigger_wait_do_not_call_directly(
    const char *sourcePath,
    int sourceLine,
    struct ltrx_trigger *trigger,
    uint32_t ms
);

char *ltrx_vsprintf_malloc(
    const char *fmt,
    va_list args
);

bool ltrx_worker_callback_register(
    void (*function)(void),
    uint32_t recall_msec,
	bool execute_now
);

void ltrx_worker_callback_unregister(
	void (*function)(void)
);
