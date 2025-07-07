#!/usr/bin/env python3
import json
import sys
sys.dont_write_bytecode = True
from   lib_gzros2 import *


def _arg_parser_config():
    _args = sys.argv[1:]
    if "-config" in _args: return _args[_args.index("-config") +1]

def _arg_parser_params():
    _args = sys.argv[1:]
    if "-params" in _args: return _args[_args.index("-params") +1]

def _load_params():
    with open(_arg_parser_params()) as _params: return json.load(_params)

def _load_config():
    with open(_arg_parser_config()) as _config: return json.load(_config) 


if __name__ == '__main__':
    gzros2 = GZROS2(_load_params(), _load_config())
    sys.exit(0)
