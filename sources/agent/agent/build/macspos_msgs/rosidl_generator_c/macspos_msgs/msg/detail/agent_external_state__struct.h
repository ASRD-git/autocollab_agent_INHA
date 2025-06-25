// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_H_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AgentExternalState in the package macspos_msgs.
typedef struct macspos_msgs__msg__AgentExternalState
{
  int16_t id;
  float position[3];
  float velocity[3];
  int16_t ongoing;
  float timestamp;
} macspos_msgs__msg__AgentExternalState;

// Struct for a sequence of macspos_msgs__msg__AgentExternalState.
typedef struct macspos_msgs__msg__AgentExternalState__Sequence
{
  macspos_msgs__msg__AgentExternalState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} macspos_msgs__msg__AgentExternalState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_H_
