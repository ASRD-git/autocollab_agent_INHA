// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from macspos_msgs:msg/AgentInternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__STRUCT_H_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AgentInternalState in the package macspos_msgs.
typedef struct macspos_msgs__msg__AgentInternalState
{
  float position[3];
  float velocity[3];
} macspos_msgs__msg__AgentInternalState;

// Struct for a sequence of macspos_msgs__msg__AgentInternalState.
typedef struct macspos_msgs__msg__AgentInternalState__Sequence
{
  macspos_msgs__msg__AgentInternalState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} macspos_msgs__msg__AgentInternalState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__STRUCT_H_
