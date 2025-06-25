// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__TRAITS_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "macspos_msgs/msg/detail/agent_external_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace macspos_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgentExternalState & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: position
  {
    if (msg.position.size() == 0) {
      out << "position: []";
    } else {
      out << "position: [";
      size_t pending_items = msg.position.size();
      for (auto item : msg.position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocity
  {
    if (msg.velocity.size() == 0) {
      out << "velocity: []";
    } else {
      out << "velocity: [";
      size_t pending_items = msg.velocity.size();
      for (auto item : msg.velocity) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ongoing
  {
    out << "ongoing: ";
    rosidl_generator_traits::value_to_yaml(msg.ongoing, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgentExternalState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocity.size() == 0) {
      out << "velocity: []\n";
    } else {
      out << "velocity:\n";
      for (auto item : msg.velocity) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: ongoing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ongoing: ";
    rosidl_generator_traits::value_to_yaml(msg.ongoing, out);
    out << "\n";
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgentExternalState & msg, bool use_flow_style = false)
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
  const macspos_msgs::msg::AgentExternalState & msg,
  std::ostream & out, size_t indentation = 0)
{
  macspos_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use macspos_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const macspos_msgs::msg::AgentExternalState & msg)
{
  return macspos_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<macspos_msgs::msg::AgentExternalState>()
{
  return "macspos_msgs::msg::AgentExternalState";
}

template<>
inline const char * name<macspos_msgs::msg::AgentExternalState>()
{
  return "macspos_msgs/msg/AgentExternalState";
}

template<>
struct has_fixed_size<macspos_msgs::msg::AgentExternalState>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<macspos_msgs::msg::AgentExternalState>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<macspos_msgs::msg::AgentExternalState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__TRAITS_HPP_
