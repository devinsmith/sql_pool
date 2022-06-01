# Basic Meson build for sql_pool

project('sql_pool', 'c', 'cpp', version : '1.0.0')

src = ['src/SqlClient.cpp', 'src/SqlConnection.cpp',
  'src/SqlConnectionFactory.cpp', 'src/SqlParams.cpp']

# Sadly freetds provides no pkg-config files.
#freetds_dep = dependency('freetds')
cc = meson.get_compiler('c')
freetds_dep = cc.find_library('sybdb', has_headers: ['sqldb.h', 'sqlfront.h'])

public_headers = include_directories('include')

project_target = static_library(
  meson.project_name(),
  src,
  dependencies: [freetds_dep],
  include_directories: public_headers,
)

project_dep = declare_dependency(include_directories: public_headers,
  link_with: project_target)
set_variable(meson.project_name() + '_dep', project_dep)
