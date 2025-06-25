// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__macspos_msgs__msg__AgentInternalSetpoint __attribute__((deprecated))
#else
# define DEPRECATED__macspos_msgs__msg__AgentInternalSetpoint __declspec(deprecated)
#endif

namespace macspos_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentInternalSetpoint_
{
  using Type = AgentInternalSetpoint_<ContainerAllocator>;

  explicit AgentInternalSetpoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_mode = 0;
      std::fill<typename std::array<float, 3>::iterator, float>(this->position_setpoint.begin(), this->position_setpoint.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->velocity_setpoint.begin(), this->velocity_setpoint.end(), 0.0f);
    }
  }

  explicit AgentInternalSetpoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position_setpoint(_alloc),
    velocity_setpoint(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_mode = 0;
      std::fill<typename std::array<float, 3>::iterator, float>(this->position_setpoint.begin(), this->position_setpoint.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->velocity_setpoint.begin(), this->velocity_setpoint.end(), 0.0f);
    }
  }

  // field types and members
  using _control_mode_type =
    int16_t;
  _control_mode_type control_mode;
  using _position_setpoint_type =
    std::array<float, 3>;
  _position_setpoint_type position_setpoint;
  using _velocity_setpoint_type =
    std::array<float, 3>;
  _velocity_setpoint_type velocity_setpoint;

  // setters for named parameter idiom
  Type & set__control_mode(
    const int16_t & _arg)
  {
    this->control_mode = _arg;
    return *this;
  }
  Type & set__position_setpoint(
    const std::array<float, 3> & _arg)
  {
    this->position_setpoint = _arg;
    return *this;
  }
  Type & set__velocity_setpoint(
    const std::array<float, 3> & _arg)
  {
    this->velocity_setpoint = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__macspos_msgs__msg__AgentInternalSetpoint
    std::shared_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__macspos_msgs__msg__AgentInternalSetpoint
    std::shared_ptr<macspos_msgs::msg::AgentInternalSetpoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentInternalSetpoint_ & other) const
  {
    if (this->control_mode != other.control_mode) {
      return false;
    }
    if (this->position_setpoint != other.position_setpoint) {
      return false;
    }
    if (this->velocity_setpoint != other.velocity_setpoint) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentInternalSetpoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentInternalSetpoint_

// alias to use template instance with default allocator
using AgentInternalSetpoint =
  macspos_msgs::msg::AgentInternalSetpoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace macspos_msgs

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_INTERNAL_SETPOINT__STRUCT_HPP_
