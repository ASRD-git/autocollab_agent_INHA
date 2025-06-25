// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__TRAITS_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "macspos_msgs/msg/detail/agent_internal_setpoint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace macspos_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgentInternalSetpoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: control_mode
  {
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << ", ";
  }

  // member: position_setpoint
  {
    if (msg.position_setpoint.size() == 0) {
      out << "position_setpoint: []";
    } else {
      out << "position_setpoint: [";
      size_t pending_items = msg.position_setpoint.size();
      for (auto item : msg.position_setpoint) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocity_setpoint
  {
    if (msg.velocity_setpoint.size() == 0) {
      out << "velocity_setpoint: []";
    } else {
      out << "velocity_setpoint: [";
      size_t pending_items = msg.velocity_setpoint.size();
      for (auto item : msg.velocity_setpoint) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgentInternalSetpoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: control_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << "\n";
  }

  // member: position_setpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position_setpoint.size() == 0) {
      out << "position_setpoint: []\n";
    } else {
      out << "position_setpoint:\n";
      for (auto item : msg.position_setpoint) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: velocity_setpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocity_setpoint.size() == 0) {
      out << "velocity_setpoint: []\n";
    } else {
      out << "velocity_setpoint:\n";
      for (auto item : msg.velocity_setpoint) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgentInternalSetpoint & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace macspos_msgs

namespace rosidl_generator_traits
{

[[deprecated("use macspos_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const macspos_msgs::msg::AgentInternalSetpoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  macspos_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use macspos_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const macspos_msgs::msg::AgentInternalSetpoint & msg)
{
  return macspos_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<macspos_msgs::msg::AgentInternalSetpoint>()
{
  return "macspos_msgs::msg::AgentInternalSetpoint";
}

template<>
inline const char * name<macspos_msgs::msg::AgentInternalSetpoint>()
{
  return "macspos_msgs/msg/AgentInternalSetpoint";
}

template<>
struct has_fixed_size<macspos_msgs::msg::AgentInternalSetpoint>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<macspos_msgs::msg::AgentInternalSetpoint>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<macspos_msgs::msg::AgentInternalSetpoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__TRAITS_HPP_
