// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice
#include "macspos_msgs/msg/detail/agent_internal_setpoint__rosidl_typesupport_fastrtps_cpp.hpp"
#include "macspos_msgs/msg/detail/agent_internal_setpoint__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace macspos_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_macspos_msgs
cdr_serialize(
  const macspos_msgs::msg::AgentInternalSetpoint & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: control_mode
  cdr << ros_message.control_mode;
  // Member: position_setpoint
  {
    cdr << ros_message.position_setpoint;
  }
  // Member: velocity_setpoint
  {
    cdr << ros_message.velocity_setpoint;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_macspos_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  macspos_msgs::msg::AgentInternalSetpoint & ros_message)
{
  // Member: control_mode
  cdr >> ros_message.control_mode;

  // Member: position_setpoint
  {
    cdr >> ros_message.position_setpoint;
  }

  // Member: velocity_setpoint
  {
    cdr >> ros_message.velocity_setpoint;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_macspos_msgs
get_serialized_size(
  const macspos_msgs::msg::AgentInternalSetpoint & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: control_mode
  {
    size_t item_size = sizeof(ros_message.control_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: position_setpoint
  {
    size_t array_size = 3;
    size_t item_size = sizeof(ros_message.position_setpoint[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: velocity_setpoint
  {
    size_t array_size = 3;
    size_t item_size = sizeof(ros_message.velocity_setpoint[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_macspos_msgs
max_serialized_size_AgentInternalSetpoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: control_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: position_setpoint
  {
    size_t array_size = 3;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: velocity_setpoint
  {
    size_t array_size = 3;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = macspos_msgs::msg::AgentInternalSetpoint;
    is_plain =
      (
      offsetof(DataType, velocity_setpoint) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _AgentInternalSetpoint__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const macspos_msgs::msg::AgentInternalSetpoint *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AgentInternalSetpoint__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<macspos_msgs::msg::AgentInternalSetpoint *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AgentInternalSetpoint__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const macspos_msgs::msg::AgentInternalSetpoint *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AgentInternalSetpoint__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_AgentInternalSetpoint(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _AgentInternalSetpoint__callbacks = {
  "macspos_msgs::msg",
  "AgentInternalSetpoint",
  _AgentInternalSetpoint__cdr_serialize,
  _AgentInternalSetpoint__cdr_deserialize,
  _AgentInternalSetpoint__get_serialized_size,
  _AgentInternalSetpoint__max_serialized_size
};

static rosidl_message_type_support_t _AgentInternalSetpoint__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AgentInternalSetpoint__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace macspos_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_macspos_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<macspos_msgs::msg::AgentInternalSetpoint>()
{
  return &macspos_msgs::msg::typesupport_fastrtps_cpp::_AgentInternalSetpoint__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, macspos_msgs, msg, AgentInternalSetpoint)() {
  return &macspos_msgs::msg::typesupport_fastrtps_cpp::_AgentInternalSetpoint__handle;
}

#ifdef __cplusplus
}
#endif
