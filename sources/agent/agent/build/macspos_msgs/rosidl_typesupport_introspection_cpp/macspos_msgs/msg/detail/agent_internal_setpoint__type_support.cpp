// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "macspos_msgs/msg/detail/agent_internal_setpoint__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace macspos_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AgentInternalSetpoint_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) macspos_msgs::msg::AgentInternalSetpoint(_init);
}

void AgentInternalSetpoint_fini_function(void * message_memory)
{
  auto typed_message = static_cast<macspos_msgs::msg::AgentInternalSetpoint *>(message_memory);
  typed_message->~AgentInternalSetpoint();
}

size_t size_function__AgentInternalSetpoint__position_setpoint(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__AgentInternalSetpoint__position_setpoint(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__AgentInternalSetpoint__position_setpoint(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__AgentInternalSetpoint__position_setpoint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__AgentInternalSetpoint__position_setpoint(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__AgentInternalSetpoint__position_setpoint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__AgentInternalSetpoint__position_setpoint(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__AgentInternalSetpoint__velocity_setpoint(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__AgentInternalSetpoint__velocity_setpoint(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__AgentInternalSetpoint__velocity_setpoint(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__AgentInternalSetpoint__velocity_setpoint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__AgentInternalSetpoint__velocity_setpoint(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__AgentInternalSetpoint__velocity_setpoint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__AgentInternalSetpoint__velocity_setpoint(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AgentInternalSetpoint_message_member_array[3] = {
  {
    "control_mode",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs::msg::AgentInternalSetpoint, control_mode),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "position_setpoint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs::msg::AgentInternalSetpoint, position_setpoint),  // bytes offset in struct
    nullptr,  // default value
    size_function__AgentInternalSetpoint__position_setpoint,  // size() function pointer
    get_const_function__AgentInternalSetpoint__position_setpoint,  // get_const(index) function pointer
    get_function__AgentInternalSetpoint__position_setpoint,  // get(index) function pointer
    fetch_function__AgentInternalSetpoint__position_setpoint,  // fetch(index, &value) function pointer
    assign_function__AgentInternalSetpoint__position_setpoint,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "velocity_setpoint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs::msg::AgentInternalSetpoint, velocity_setpoint),  // bytes offset in struct
    nullptr,  // default value
    size_function__AgentInternalSetpoint__velocity_setpoint,  // size() function pointer
    get_const_function__AgentInternalSetpoint__velocity_setpoint,  // get_const(index) function pointer
    get_function__AgentInternalSetpoint__velocity_setpoint,  // get(index) function pointer
    fetch_function__AgentInternalSetpoint__velocity_setpoint,  // fetch(index, &value) function pointer
    assign_function__AgentInternalSetpoint__velocity_setpoint,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AgentInternalSetpoint_message_members = {
  "macspos_msgs::msg",  // message namespace
  "AgentInternalSetpoint",  // message name
  3,  // number of fields
  sizeof(macspos_msgs::msg::AgentInternalSetpoint),
  AgentInternalSetpoint_message_member_array,  // message members
  AgentInternalSetpoint_init_function,  // function to initialize message memory (memory has to be allocated)
  AgentInternalSetpoint_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AgentInternalSetpoint_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AgentInternalSetpoint_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace macspos_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<macspos_msgs::msg::AgentInternalSetpoint>()
{
  return &::macspos_msgs::msg::rosidl_typesupport_introspection_cpp::AgentInternalSetpoint_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, macspos_msgs, msg, AgentInternalSetpoint)() {
  return &::macspos_msgs::msg::rosidl_typesupport_introspection_cpp::AgentInternalSetpoint_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
