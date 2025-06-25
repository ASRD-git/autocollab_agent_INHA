// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "macspos_msgs/msg/detail/agent_internal_setpoint__rosidl_typesupport_introspection_c.h"
#include "macspos_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "macspos_msgs/msg/detail/agent_internal_setpoint__functions.h"
#include "macspos_msgs/msg/detail/agent_internal_setpoint__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  macspos_msgs__msg__AgentInternalSetpoint__init(message_memory);
}

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_fini_function(void * message_memory)
{
  macspos_msgs__msg__AgentInternalSetpoint__fini(message_memory);
}

size_t macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__size_function__AgentInternalSetpoint__position_setpoint(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__position_setpoint(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__position_setpoint(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__fetch_function__AgentInternalSetpoint__position_setpoint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__position_setpoint(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__assign_function__AgentInternalSetpoint__position_setpoint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__position_setpoint(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__size_function__AgentInternalSetpoint__velocity_setpoint(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__velocity_setpoint(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__velocity_setpoint(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__fetch_function__AgentInternalSetpoint__velocity_setpoint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__velocity_setpoint(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__assign_function__AgentInternalSetpoint__velocity_setpoint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__velocity_setpoint(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_member_array[3] = {
  {
    "control_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs__msg__AgentInternalSetpoint, control_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position_setpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs__msg__AgentInternalSetpoint, position_setpoint),  // bytes offset in struct
    NULL,  // default value
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__size_function__AgentInternalSetpoint__position_setpoint,  // size() function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__position_setpoint,  // get_const(index) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__position_setpoint,  // get(index) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__fetch_function__AgentInternalSetpoint__position_setpoint,  // fetch(index, &value) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__assign_function__AgentInternalSetpoint__position_setpoint,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity_setpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs__msg__AgentInternalSetpoint, velocity_setpoint),  // bytes offset in struct
    NULL,  // default value
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__size_function__AgentInternalSetpoint__velocity_setpoint,  // size() function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_const_function__AgentInternalSetpoint__velocity_setpoint,  // get_const(index) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__get_function__AgentInternalSetpoint__velocity_setpoint,  // get(index) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__fetch_function__AgentInternalSetpoint__velocity_setpoint,  // fetch(index, &value) function pointer
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__assign_function__AgentInternalSetpoint__velocity_setpoint,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_members = {
  "macspos_msgs__msg",  // message namespace
  "AgentInternalSetpoint",  // message name
  3,  // number of fields
  sizeof(macspos_msgs__msg__AgentInternalSetpoint),
  macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_member_array,  // message members
  macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_init_function,  // function to initialize message memory (memory has to be allocated)
  macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_type_support_handle = {
  0,
  &macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_macspos_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, macspos_msgs, msg, AgentInternalSetpoint)() {
  if (!macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_type_support_handle.typesupport_identifier) {
    macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &macspos_msgs__msg__AgentInternalSetpoint__rosidl_typesupport_introspection_c__AgentInternalSetpoint_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
