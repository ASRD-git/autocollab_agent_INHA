// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__BUILDER_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "macspos_msgs/msg/detail/agent_external_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace macspos_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentExternalState_timestamp
{
public:
  explicit Init_AgentExternalState_timestamp(::macspos_msgs::msg::AgentExternalState & msg)
  : msg_(msg)
  {}
  ::macspos_msgs::msg::AgentExternalState timestamp(::macspos_msgs::msg::AgentExternalState::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::macspos_msgs::msg::AgentExternalState msg_;
};

class Init_AgentExternalState_ongoing
{
public:
  explicit Init_AgentExternalState_ongoing(::macspos_msgs::msg::AgentExternalState & msg)
  : msg_(msg)
  {}
  Init_AgentExternalState_timestamp ongoing(::macspos_msgs::msg::AgentExternalState::_ongoing_type arg)
  {
    msg_.ongoing = std::move(arg);
    return Init_AgentExternalState_timestamp(msg_);
  }

private:
  ::macspos_msgs::msg::AgentExternalState msg_;
};

class Init_AgentExternalState_velocity
{
public:
  explicit Init_AgentExternalState_velocity(::macspos_msgs::msg::AgentExternalState & msg)
  : msg_(msg)
  {}
  Init_AgentExternalState_ongoing velocity(::macspos_msgs::msg::AgentExternalState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_AgentExternalState_ongoing(msg_);
  }

private:
  ::macspos_msgs::msg::AgentExternalState msg_;
};

class Init_AgentExternalState_position
{
public:
  explicit Init_AgentExternalState_position(::macspos_msgs::msg::AgentExternalState & msg)
  : msg_(msg)
  {}
  Init_AgentExternalState_velocity position(::macspos_msgs::msg::AgentExternalState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_AgentExternalState_velocity(msg_);
  }

private:
  ::macspos_msgs::msg::AgentExternalState msg_;
};

class Init_AgentExternalState_id
{
public:
  Init_AgentExternalState_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgentExternalState_position id(::macspos_msgs::msg::AgentExternalState::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_AgentExternalState_position(msg_);
  }

private:
  ::macspos_msgs::msg::AgentExternalState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::macspos_msgs::msg::AgentExternalState>()
{
  return macspos_msgs::msg::builder::Init_AgentExternalState_id();
}

}  // namespace macspos_msgs

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__BUILDER_HPP_
