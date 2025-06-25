# generated from rosidl_generator_py/resource/_idl.py.em
# with input from macspos_msgs:msg/AgentInternalSetpoint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'position_setpoint'
# Member 'velocity_setpoint'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AgentInternalSetpoint(type):
    """Metaclass of message 'AgentInternalSetpoint'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('macspos_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'macspos_msgs.msg.AgentInternalSetpoint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__agent_internal_setpoint
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__agent_internal_setpoint
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__agent_internal_setpoint
            cls._TYPE_SUPPORT = module.type_support_msg__msg__agent_internal_setpoint
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__agent_internal_setpoint

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AgentInternalSetpoint(metaclass=Metaclass_AgentInternalSetpoint):
    """Message class 'AgentInternalSetpoint'."""

    __slots__ = [
        '_control_mode',
        '_position_setpoint',
        '_velocity_setpoint',
    ]

    _fields_and_field_types = {
        'control_mode': 'int16',
        'position_setpoint': 'float[3]',
        'velocity_setpoint': 'float[3]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.control_mode = kwargs.get('control_mode', int())
        if 'position_setpoint' not in kwargs:
            self.position_setpoint = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.position_setpoint = numpy.array(kwargs.get('position_setpoint'), dtype=numpy.float32)
            assert self.position_setpoint.shape == (3, )
        if 'velocity_setpoint' not in kwargs:
            self.velocity_setpoint = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.velocity_setpoint = numpy.array(kwargs.get('velocity_setpoint'), dtype=numpy.float32)
            assert self.velocity_setpoint.shape == (3, )

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.control_mode != other.control_mode:
            return False
        if all(self.position_setpoint != other.position_setpoint):
            return False
        if all(self.velocity_setpoint != other.velocity_setpoint):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def control_mode(self):
        """Message field 'control_mode'."""
        return self._control_mode

    @control_mode.setter
    def control_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'control_mode' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'control_mode' field must be an integer in [-32768, 32767]"
        self._control_mode = value

    @builtins.property
    def position_setpoint(self):
        """Message field 'position_setpoint'."""
        return self._position_setpoint

    @position_setpoint.setter
    def position_setpoint(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'position_setpoint' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'position_setpoint' numpy.ndarray() must have a size of 3"
            self._position_setpoint = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'position_setpoint' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._position_setpoint = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def velocity_setpoint(self):
        """Message field 'velocity_setpoint'."""
        return self._velocity_setpoint

    @velocity_setpoint.setter
    def velocity_setpoint(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'velocity_setpoint' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'velocity_setpoint' numpy.ndarray() must have a size of 3"
            self._velocity_setpoint = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'velocity_setpoint' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._velocity_setpoint = numpy.array(value, dtype=numpy.float32)
