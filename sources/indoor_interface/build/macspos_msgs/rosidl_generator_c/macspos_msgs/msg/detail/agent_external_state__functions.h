// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__FUNCTIONS_H_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "macspos_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "macspos_msgs/msg/detail/agent_external_state__struct.h"

/// Initialize msg/AgentExternalState message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * macspos_msgs__msg__AgentExternalState
 * )) before or use
 * macspos_msgs__msg__AgentExternalState__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__init(macspos_msgs__msg__AgentExternalState * msg);

/// Finalize msg/AgentExternalState message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
void
macspos_msgs__msg__AgentExternalState__fini(macspos_msgs__msg__AgentExternalState * msg);

/// Create msg/AgentExternalState message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * macspos_msgs__msg__AgentExternalState__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
macspos_msgs__msg__AgentExternalState *
macspos_msgs__msg__AgentExternalState__create();

/// Destroy msg/AgentExternalState message.
/**
 * It calls
 * macspos_msgs__msg__AgentExternalState__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
void
macspos_msgs__msg__AgentExternalState__destroy(macspos_msgs__msg__AgentExternalState * msg);

/// Check for msg/AgentExternalState message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__are_equal(const macspos_msgs__msg__AgentExternalState * lhs, const macspos_msgs__msg__AgentExternalState * rhs);

/// Copy a msg/AgentExternalState message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__copy(
  const macspos_msgs__msg__AgentExternalState * input,
  macspos_msgs__msg__AgentExternalState * output);

/// Initialize array of msg/AgentExternalState messages.
/**
 * It allocates the memory for the number of elements and calls
 * macspos_msgs__msg__AgentExternalState__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__Sequence__init(macspos_msgs__msg__AgentExternalState__Sequence * array, size_t size);

/// Finalize array of msg/AgentExternalState messages.
/**
 * It calls
 * macspos_msgs__msg__AgentExternalState__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
void
macspos_msgs__msg__AgentExternalState__Sequence__fini(macspos_msgs__msg__AgentExternalState__Sequence * array);

/// Create array of msg/AgentExternalState messages.
/**
 * It allocates the memory for the array and calls
 * macspos_msgs__msg__AgentExternalState__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
macspos_msgs__msg__AgentExternalState__Sequence *
macspos_msgs__msg__AgentExternalState__Sequence__create(size_t size);

/// Destroy array of msg/AgentExternalState messages.
/**
 * It calls
 * macspos_msgs__msg__AgentExternalState__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
void
macspos_msgs__msg__AgentExternalState__Sequence__destroy(macspos_msgs__msg__AgentExternalState__Sequence * array);

/// Check for msg/AgentExternalState message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__Sequence__are_equal(const macspos_msgs__msg__AgentExternalState__Sequence * lhs, const macspos_msgs__msg__AgentExternalState__Sequence * rhs);

/// Copy an array of msg/AgentExternalState messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_macspos_msgs
bool
macspos_msgs__msg__AgentExternalState__Sequence__copy(
  const macspos_msgs__msg__AgentExternalState__Sequence * input,
  macspos_msgs__msg__AgentExternalState__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__FUNCTIONS_H_
