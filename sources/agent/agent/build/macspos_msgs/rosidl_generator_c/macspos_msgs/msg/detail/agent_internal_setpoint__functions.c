// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from macspos_msgs:msg/AgentInternalSetpoint.idl
// generated code does not contain a copyright notice
#include "macspos_msgs/msg/detail/agent_internal_setpoint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
macspos_msgs__msg__AgentInternalSetpoint__init(macspos_msgs__msg__AgentInternalSetpoint * msg)
{
  if (!msg) {
    return false;
  }
  // control_mode
  // position_setpoint
  // velocity_setpoint
  return true;
}

void
macspos_msgs__msg__AgentInternalSetpoint__fini(macspos_msgs__msg__AgentInternalSetpoint * msg)
{
  if (!msg) {
    return;
  }
  // control_mode
  // position_setpoint
  // velocity_setpoint
}

bool
macspos_msgs__msg__AgentInternalSetpoint__are_equal(const macspos_msgs__msg__AgentInternalSetpoint * lhs, const macspos_msgs__msg__AgentInternalSetpoint * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // control_mode
  if (lhs->control_mode != rhs->control_mode) {
    return false;
  }
  // position_setpoint
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->position_setpoint[i] != rhs->position_setpoint[i]) {
      return false;
    }
  }
  // velocity_setpoint
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->velocity_setpoint[i] != rhs->velocity_setpoint[i]) {
      return false;
    }
  }
  return true;
}

bool
macspos_msgs__msg__AgentInternalSetpoint__copy(
  const macspos_msgs__msg__AgentInternalSetpoint * input,
  macspos_msgs__msg__AgentInternalSetpoint * output)
{
  if (!input || !output) {
    return false;
  }
  // control_mode
  output->control_mode = input->control_mode;
  // position_setpoint
  for (size_t i = 0; i < 3; ++i) {
    output->position_setpoint[i] = input->position_setpoint[i];
  }
  // velocity_setpoint
  for (size_t i = 0; i < 3; ++i) {
    output->velocity_setpoint[i] = input->velocity_setpoint[i];
  }
  return true;
}

macspos_msgs__msg__AgentInternalSetpoint *
macspos_msgs__msg__AgentInternalSetpoint__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalSetpoint * msg = (macspos_msgs__msg__AgentInternalSetpoint *)allocator.allocate(sizeof(macspos_msgs__msg__AgentInternalSetpoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(macspos_msgs__msg__AgentInternalSetpoint));
  bool success = macspos_msgs__msg__AgentInternalSetpoint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
macspos_msgs__msg__AgentInternalSetpoint__destroy(macspos_msgs__msg__AgentInternalSetpoint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    macspos_msgs__msg__AgentInternalSetpoint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
macspos_msgs__msg__AgentInternalSetpoint__Sequence__init(macspos_msgs__msg__AgentInternalSetpoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalSetpoint * data = NULL;

  if (size) {
    data = (macspos_msgs__msg__AgentInternalSetpoint *)allocator.zero_allocate(size, sizeof(macspos_msgs__msg__AgentInternalSetpoint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = macspos_msgs__msg__AgentInternalSetpoint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        macspos_msgs__msg__AgentInternalSetpoint__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
macspos_msgs__msg__AgentInternalSetpoint__Sequence__fini(macspos_msgs__msg__AgentInternalSetpoint__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      macspos_msgs__msg__AgentInternalSetpoint__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

macspos_msgs__msg__AgentInternalSetpoint__Sequence *
macspos_msgs__msg__AgentInternalSetpoint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalSetpoint__Sequence * array = (macspos_msgs__msg__AgentInternalSetpoint__Sequence *)allocator.allocate(sizeof(macspos_msgs__msg__AgentInternalSetpoint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = macspos_msgs__msg__AgentInternalSetpoint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
macspos_msgs__msg__AgentInternalSetpoint__Sequence__destroy(macspos_msgs__msg__AgentInternalSetpoint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    macspos_msgs__msg__AgentInternalSetpoint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
macspos_msgs__msg__AgentInternalSetpoint__Sequence__are_equal(const macspos_msgs__msg__AgentInternalSetpoint__Sequence * lhs, const macspos_msgs__msg__AgentInternalSetpoint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!macspos_msgs__msg__AgentInternalSetpoint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
macspos_msgs__msg__AgentInternalSetpoint__Sequence__copy(
  const macspos_msgs__msg__AgentInternalSetpoint__Sequence * input,
  macspos_msgs__msg__AgentInternalSetpoint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(macspos_msgs__msg__AgentInternalSetpoint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    macspos_msgs__msg__AgentInternalSetpoint * data =
      (macspos_msgs__msg__AgentInternalSetpoint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!macspos_msgs__msg__AgentInternalSetpoint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          macspos_msgs__msg__AgentInternalSetpoint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!macspos_msgs__msg__AgentInternalSetpoint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
