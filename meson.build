project(
  'hsplua',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++14'],
)

dependencies = [
	'lua'
]

sources = [
  'chkstat.cpp',
  'chktype.cpp',
  'commands.cpp',
  'dim.cpp',
  'gc.cpp',
  'hsplua.cpp',
  'labelfunc.cpp',
  'pushpop.cpp',
  'readval.cpp',
]

exe = executable(
  'hsplua',
  sources,
  install : true,
  dependencies : dependencies,
)

test('basic', exe)
