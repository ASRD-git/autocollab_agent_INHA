// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice

#ifndef MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_HPP_
#define MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__macspos_msgs__msg__AgentExternalState __attribute__((deprecated))
#else
# define DEPRECATED__macspos_msgs__msg__AgentExternalState __declspec(deprecated)
#endif

namespace macspos_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentExternalState_
{
  using Type = AgentExternalState_<ContainerAllocator>;

  explicit AgentExternalState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      std::fill<typename std::array<float, 3>::iterator, float>(this->position.begin(), this->position.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->velocity.begin(), this->velocity.end(), 0.0f);
      this->ongoing = 0;
      this->timestamp = 0.0f;
    }
  }

  explicit AgentExternalState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc),
    velocity(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      std::fill<typename std::array<float, 3>::iterator, float>(this->position.begin(), this->position.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->velocity.begin(), this->velocity.end(), 0.0f);
      this->ongoing = 0;
      this->timestamp = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    int16_t;
  _id_type id;
  using _position_type =
    std::array<float, 3>;
  _position_type position;
  using _velocity_type =
    std::array<float, 3>;
  _velocity_type velocity;
  using _ongoing_type =
    int16_t;
  _ongoing_type ongoing;
  using _timestamp_type =
    float;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__id(
    const int16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<float, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const std::array<float, 3> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__ongoing(
    const int16_t & _arg)
  {
    this->ongoing = _arg;
    return *this;
  }
  Type & set__timestamp(
    const float & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    macspos_msgs::msg::AgentExternalState_<ContainerAllocator> *;
  using ConstRawPtr =
    const macspos_msgs::msg::AgentExternalState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      macspos_msgs::msg::AgentExternalState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      macspos_msgs::msg::AgentExternalState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__macspos_msgs__msg__AgentExternalState
    std::shared_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__macspos_msgs__msg__AgentExternalState
    std::shared_ptr<macspos_msgs::msg::AgentExternalState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentExternalState_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->ongoing != other.ongoing) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentExternalState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentExternalState_

// alias to use template instance with default allocator
using AgentExternalState =
  macspos_msgs::msg::AgentExternalState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace macspos_msgs

#endif  // MACSPOS_MSGS__MSG__DETAIL__AGENT_EXTERNAL_STATE__STRUCT_HPP_
