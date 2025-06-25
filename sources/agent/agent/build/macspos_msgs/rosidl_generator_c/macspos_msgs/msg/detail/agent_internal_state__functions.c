// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from macspos_msgs:msg/AgentInternalState.idl
// generated code does not contain a copyright notice
#include "macspos_msgs/msg/detail/agent_internal_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
macspos_msgs__msg__AgentInternalState__init(macspos_msgs__msg__AgentInternalState * msg)
{
  if (!msg) {
    return false;
  }
  // position
  // velocity
  return true;
}

void
macspos_msgs__msg__AgentInternalState__fini(macspos_msgs__msg__AgentInternalState * msg)
{
  if (!msg) {
    return;
  }
  // position
  // velocity
}

bool
macspos_msgs__msg__AgentInternalState__are_equal(const macspos_msgs__msg__AgentInternalState * lhs, const macspos_msgs__msg__AgentInternalState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->position[i] != rhs->position[i]) {
      return false;
    }
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->velocity[i] != rhs->velocity[i]) {
      return false;
    }
  }
  return true;
}

bool
macspos_msgs__msg__AgentInternalState__copy(
  const macspos_msgs__msg__AgentInternalState * input,
  macspos_msgs__msg__AgentInternalState * output)
{
  if (!input || !output) {
    return false;
  }
  // position
  for (size_t i = 0; i < 3; ++i) {
    output->position[i] = input->position[i];
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    output->velocity[i] = input->velocity[i];
  }
  return true;
}

macspos_msgs__msg__AgentInternalState *
macspos_msgs__msg__AgentInternalState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalState * msg = (macspos_msgs__msg__AgentInternalState *)allocator.allocate(sizeof(macspos_msgs__msg__AgentInternalState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(macspos_msgs__msg__AgentInternalState));
  bool success = macspos_msgs__msg__AgentInternalState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
macspos_msgs__msg__AgentInternalState__destroy(macspos_msgs__msg__AgentInternalState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    macspos_msgs__msg__AgentInternalState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
macspos_msgs__msg__AgentInternalState__Sequence__init(macspos_msgs__msg__AgentInternalState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalState * data = NULL;

  if (size) {
    data = (macspos_msgs__msg__AgentInternalState *)allocator.zero_allocate(size, sizeof(macspos_msgs__msg__AgentInternalState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = macspos_msgs__msg__AgentInternalState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        macspos_msgs__msg__AgentInternalState__fini(&data[i - 1]);
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
macspos_msgs__msg__AgentInternalState__Sequence__fini(macspos_msgs__msg__AgentInternalState__Sequence * array)
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
      macspos_msgs__msg__AgentInternalState__fini(&array->data[i]);
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

macspos_msgs__msg__AgentInternalState__Sequence *
macspos_msgs__msg__AgentInternalState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentInternalState__Sequence * array = (macspos_msgs__msg__AgentInternalState__Sequence *)allocator.allocate(sizeof(macspos_msgs__msg__AgentInternalState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = macspos_msgs__msg__AgentInternalState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
macspos_msgs__msg__AgentInternalState__Sequence__destroy(macspos_msgs__msg__AgentInternalState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    macspos_msgs__msg__AgentInternalState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
macspos_msgs__msg__AgentInternalState__Sequence__are_equal(const macspos_msgs__msg__AgentInternalState__Sequence * lhs, const macspos_msgs__msg__AgentInternalState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!macspos_msgs__msg__AgentInternalState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
macspos_msgs__msg__AgentInternalState__Sequence__copy(
  const macspos_msgs__msg__AgentInternalState__Sequence * input,
  macspos_msgs__msg__AgentInternalState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(macspos_msgs__msg__AgentInternalState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    macspos_msgs__msg__AgentInternalState * data =
      (macspos_msgs__msg__AgentInternalState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!macspos_msgs__msg__AgentInternalState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          macspos_msgs__msg__AgentInternalState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!macspos_msgs__msg__AgentInternalState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
