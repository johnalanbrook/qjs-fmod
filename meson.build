project('qjs-soundplug', 'c')

fmod_inc = include_directories('fmod/api/core/inc')

libtype = get_option('default_library')
if libtype == 'shared'
  add_project_arguments('-DJS_SHARED_LIBRARY', language:'c')
endif

deps = []
quickjs = dependency('quickjs', fallback:['quickjs', 'quickjs_dep'], static:true)

fmod_lib = declare_dependency(
  include_directories: 'fmod/api/core/inc',
  link_args: ['-Lfmod/api/core/lib', '-lfmod']
)

cc = meson.get_compiler('c')
fmod_lib = cc.find_library('fmod', dirs: meson.source_root())

qjs_fmod_lib = library('fmod',
  sources: 'qjs_fmod.c',
  include_directories: [fmod_inc],
  dependencies: [quickjs] + fmod_lib,
  name_suffix: 'so',
  name_prefix: '',
)

qjs_fmod_dep = declare_dependency(
  link_with: qjs_fmod_lib,
  include_directories : fmod_inc
)

