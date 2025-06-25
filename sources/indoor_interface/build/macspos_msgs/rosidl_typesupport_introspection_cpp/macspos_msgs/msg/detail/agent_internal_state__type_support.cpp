// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from macspos_msgs:msg/AgentInternalState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "macspos_msgs/msg/detail/agent_internal_state__struct.hpp"
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

void AgentInternalState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) macspos_msgs::msg::AgentInternalState(_init);
}

void AgentInternalState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<macspos_msgs::msg::AgentInternalState *>(message_memory);
  typed_message->~AgentInternalState();
}

size_t size_function__AgentInternalState__position(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__AgentInternalState__position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__AgentInternalState__position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__AgentInternalState__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__AgentInternalState__position(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__AgentInternalState__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__AgentInternalState__position(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__AgentInternalState__velocity(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__AgentInternalState__velocity(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__AgentInternalState__velocity(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__AgentInternalState__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__AgentInternalState__velocity(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__AgentInternalState__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__AgentInternalState__velocity(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AgentInternalState_message_member_array[2] = {
  {
    "position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs::msg::AgentInternalState, position),  // bytes offset in struct
    nullptr,  // default value
    size_function__AgentInternalState__position,  // size() function pointer
    get_const_function__AgentInternalState__position,  // get_const(index) function pointer
    get_function__AgentInternalState__position,  // get(index) function pointer
    fetch_function__AgentInternalState__position,  // fetch(index, &value) function pointer
    assign_function__AgentInternalState__position,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "velocity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(macspos_msgs::msg::AgentInternalState, velocity),  // bytes offset in struct
    nullptr,  // default value
    size_function__AgentInternalState__velocity,  // size() function pointer
    get_const_function__AgentInternalState__velocity,  // get_const(index) function pointer
    get_function__AgentInternalState__velocity,  // get(index) function pointer
    fetch_function__AgentInternalState__velocity,  // fetch(index, &value) function pointer
    assign_function__AgentInternalState__velocity,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AgentInternalState_message_members = {
  "macspos_msgs::msg",  // message namespace
  "AgentInternalState",  // message name
  2,  // number of fields
  sizeof(macspos_msgs::msg::AgentInternalState),
  AgentInternalState_message_member_array,  // message members
  AgentInternalState_init_function,  // function to initialize message memory (memory has to be allocated)
  AgentInternalState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AgentInternalState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AgentInternalState_message_members,
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
get_message_type_support_handle<macspos_msgs::msg::AgentInternalState>()
{
  return &::macspos_msgs::msg::rosidl_typesupport_introspection_cpp::AgentInternalState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, macspos_msgs, msg, AgentInternalState)() {
  return &::macspos_msgs::msg::rosidl_typesupport_introspection_cpp::AgentInternalState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
