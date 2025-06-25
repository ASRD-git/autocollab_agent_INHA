// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from macspos_msgs:msg/AgentInternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__BUILDER_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "macspos_msgs/msg/detail/agent_internal_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace macspos_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentInternalState_velocity
{
public:
  explicit Init_AgentInternalState_velocity(::macspos_msgs::msg::AgentInternalState & msg)
  : msg_(msg)
  {}
  ::macspos_msgs::msg::AgentInternalState velocity(::macspos_msgs::msg::AgentInternalState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::macspos_msgs::msg::AgentInternalState msg_;
};

class Init_AgentInternalState_position
{
public:
  Init_AgentInternalState_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgentInternalState_velocity position(::macspos_msgs::msg::AgentInternalState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_AgentInternalState_velocity(msg_);
  }

private:
  ::macspos_msgs::msg::AgentInternalState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::macspos_msgs::msg::AgentInternalState>()
{
  return macspos_msgs::msg::builder::Init_AgentInternalState_position();
}

}  // namespace macspos_msgs

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_STATE__BUILDER_HPP_
