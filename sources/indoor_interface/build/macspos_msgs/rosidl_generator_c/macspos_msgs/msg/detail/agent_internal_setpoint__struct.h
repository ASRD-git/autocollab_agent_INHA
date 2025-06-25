// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_H_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AgentInternalSetpoint in the package macspos_msgs.
typedef struct macspos_msgs__msg__AgentInternalSetpoint
{
  int16_t control_mode;
  float position_setpoint[3];
  float velocity_setpoint[3];
} macspos_msgs__msg__AgentInternalSetpoint;

// Struct for a sequence of macspos_msgs__msg__AgentInternalSetpoint.
typedef struct macspos_msgs__msg__AgentInternalSetpoint__Sequence
{
  macspos_msgs__msg__AgentInternalSetpoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} macspos_msgs__msg__AgentInternalSetpoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_H_
