project('qrl-cpp',
  ['cpp'],
  version : '0.1',
  default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++23'])

include = include_directories('./include')

executable('rock-paper-scissor', [
    'examples/rock-paper-scissor.cc'
  ], dependencies: [],
  include_directories: include)

executable('tris', [
    'examples/tris.cc'
  ], dependencies: [],
  include_directories: include)
