// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__BUILDER_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "macspos_msgs/msg/detail/agent_internal_setpoint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace macspos_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentInternalSetpoint_velocity_setpoint
{
public:
  explicit Init_AgentInternalSetpoint_velocity_setpoint(::macspos_msgs::msg::AgentInternalSetpoint & msg)
  : msg_(msg)
  {}
  ::macspos_msgs::msg::AgentInternalSetpoint velocity_setpoint(::macspos_msgs::msg::AgentInternalSetpoint::_velocity_setpoint_type arg)
  {
    msg_.velocity_setpoint = std::move(arg);
    return std::move(msg_);
  }

private:
  ::macspos_msgs::msg::AgentInternalSetpoint msg_;
};

class Init_AgentInternalSetpoint_position_setpoint
{
public:
  explicit Init_AgentInternalSetpoint_position_setpoint(::macspos_msgs::msg::AgentInternalSetpoint & msg)
  : msg_(msg)
  {}
  Init_AgentInternalSetpoint_velocity_setpoint position_setpoint(::macspos_msgs::msg::AgentInternalSetpoint::_position_setpoint_type arg)
  {
    msg_.position_setpoint = std::move(arg);
    return Init_AgentInternalSetpoint_velocity_setpoint(msg_);
  }

private:
  ::macspos_msgs::msg::AgentInternalSetpoint msg_;
};

class Init_AgentInternalSetpoint_control_mode
{
public:
  Init_AgentInternalSetpoint_control_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgentInternalSetpoint_position_setpoint control_mode(::macspos_msgs::msg::AgentInternalSetpoint::_control_mode_type arg)
  {
    msg_.control_mode = std::move(arg);
    return Init_AgentInternalSetpoint_position_setpoint(msg_);
  }

private:
  ::macspos_msgs::msg::AgentInternalSetpoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::macspos_msgs::msg::AgentInternalSetpoint>()
{
  return macspos_msgs::msg::builder::Init_AgentInternalSetpoint_control_mode();
}

}  // namespace macspos_msgs

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__BUILDER_HPP_
