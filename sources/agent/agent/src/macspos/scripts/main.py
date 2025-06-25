#!/usr/bin/env python3
import json
import sys
sys.dont_write_bytecode = True
from   lib_macspos import MACSPOS


def _arg_parser_whoami():
    _args = sys.argv[1:]
    if "-id" in _args: return int(_args[_args.index("-id") +1])

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
    macspos = MACSPOS(_arg_parser_whoami(), _load_params(), _load_config())
    sys.exit(0)
