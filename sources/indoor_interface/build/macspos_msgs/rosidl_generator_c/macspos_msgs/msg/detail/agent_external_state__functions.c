// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from macspos_msgs:msg/AgentExternalState.idl
// generated code does not contain a copyright notice
#include "macspos_msgs/msg/detail/agent_external_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
macspos_msgs__msg__AgentExternalState__init(macspos_msgs__msg__AgentExternalState * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // position
  // velocity
  // ongoing
  // timestamp
  return true;
}

void
macspos_msgs__msg__AgentExternalState__fini(macspos_msgs__msg__AgentExternalState * msg)
{
  if (!msg) {
    return;
  }
  // id
  // position
  // velocity
  // ongoing
  // timestamp
}

bool
macspos_msgs__msg__AgentExternalState__are_equal(const macspos_msgs__msg__AgentExternalState * lhs, const macspos_msgs__msg__AgentExternalState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
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
  // ongoing
  if (lhs->ongoing != rhs->ongoing) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  return true;
}

bool
macspos_msgs__msg__AgentExternalState__copy(
  const macspos_msgs__msg__AgentExternalState * input,
  macspos_msgs__msg__AgentExternalState * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // position
  for (size_t i = 0; i < 3; ++i) {
    output->position[i] = input->position[i];
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    output->velocity[i] = input->velocity[i];
  }
  // ongoing
  output->ongoing = input->ongoing;
  // timestamp
  output->timestamp = input->timestamp;
  return true;
}

macspos_msgs__msg__AgentExternalState *
macspos_msgs__msg__AgentExternalState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentExternalState * msg = (macspos_msgs__msg__AgentExternalState *)allocator.allocate(sizeof(macspos_msgs__msg__AgentExternalState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(macspos_msgs__msg__AgentExternalState));
  bool success = macspos_msgs__msg__AgentExternalState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
macspos_msgs__msg__AgentExternalState__destroy(macspos_msgs__msg__AgentExternalState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    macspos_msgs__msg__AgentExternalState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
macspos_msgs__msg__AgentExternalState__Sequence__init(macspos_msgs__msg__AgentExternalState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentExternalState * data = NULL;

  if (size) {
    data = (macspos_msgs__msg__AgentExternalState *)allocator.zero_allocate(size, sizeof(macspos_msgs__msg__AgentExternalState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = macspos_msgs__msg__AgentExternalState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        macspos_msgs__msg__AgentExternalState__fini(&data[i - 1]);
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
macspos_msgs__msg__AgentExternalState__Sequence__fini(macspos_msgs__msg__AgentExternalState__Sequence * array)
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
      macspos_msgs__msg__AgentExternalState__fini(&array->data[i]);
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

macspos_msgs__msg__AgentExternalState__Sequence *
macspos_msgs__msg__AgentExternalState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  macspos_msgs__msg__AgentExternalState__Sequence * array = (macspos_msgs__msg__AgentExternalState__Sequence *)allocator.allocate(sizeof(macspos_msgs__msg__AgentExternalState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = macspos_msgs__msg__AgentExternalState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
macspos_msgs__msg__AgentExternalState__Sequence__destroy(macspos_msgs__msg__AgentExternalState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    macspos_msgs__msg__AgentExternalState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
macspos_msgs__msg__AgentExternalState__Sequence__are_equal(const macspos_msgs__msg__AgentExternalState__Sequence * lhs, const macspos_msgs__msg__AgentExternalState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!macspos_msgs__msg__AgentExternalState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
macspos_msgs__msg__AgentExternalState__Sequence__copy(
  const macspos_msgs__msg__AgentExternalState__Sequence * input,
  macspos_msgs__msg__AgentExternalState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(macspos_msgs__msg__AgentExternalState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    macspos_msgs__msg__AgentExternalState * data =
      (macspos_msgs__msg__AgentExternalState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!macspos_msgs__msg__AgentExternalState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          macspos_msgs__msg__AgentExternalState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!macspos_msgs__msg__AgentExternalState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
